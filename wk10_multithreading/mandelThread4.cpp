#include <iostream>
#include <complex>
#include <vector>
#include <chrono>
#include <functional>
#include <thread> // multi threads
#include "window.h"
#include "save_image.h"
#include "utils.h"
// NOTE: need to brew install freeimage
// clang++ -std=c++11 -stdlib=libc++ -O3 save_image.cpp utils.cpp mandel.cpp -lfreeimage// NOTE: need to brew install freeimage
#include <mutex>
// Use an alias to simplify the use of complex type
using Complex = std::complex<double>;

// Convert a pixel coordinate to the complex domain
Complex scale(window<int> &scr, window<double> &fr, Complex c) {
	Complex aux(c.real() / (double)scr.width() * fr.width() + fr.x_min(),
		c.imag() / (double)scr.height() * fr.height() + fr.y_min());
	return aux;
}

// Check if a point is in the set or escapes to infinity, return the number if iterations
int escape(Complex c, int iter_max, const std::function<Complex( Complex, Complex)> &func) {
	Complex z(0);
	int iter = 0;

	while (abs(z) < 200000000.0 && iter < iter_max) {
		z = func(z, c);
		iter++;
	}

	return iter;
}

// Loop over each pixel from our image and check if the points associated with this pixel escape to infinity
void get_number_iterations(window<int> &scr, window<double> &fract, int iter_max, std::vector<int> &colors,
	const std::function<Complex( Complex, Complex)> &func) {	
	
	auto numCores = std::thread::hardware_concurrency();
	
	int rowI = scr.y_max();
	std::mutex mutexRowI;
	
	std::function<void(unsigned int)> calc; // wrap lambda function type inside function to be used below
	calc = [&scr, &fract, &colors, &iter_max, &func, &numCores, &rowI, &mutexRowI, &calc](unsigned int id){
		
		// lock the mutex
		mutexRowI.lock(); // its boolean value turns to true when it is locked
		auto currRow = --rowI;
		mutexRowI.unlock();

		// 1) deadlock is thread A waiting for thread B to unlock => stuck and frozen => no output
		// 2) race condition is 2 threads printing at same time => garbled output
		// 3) lock guard is like a smart_ptr to a raw ptr but for mutexes = with mutexes we need to 
		// remember to unlock them, but lock guard will unlock automatically when out of scope
		// if exception is thrown, explicit unlocking won't happen, so with lock guard won't have this issue
		// there will be a bit of performance impact (overhead) as has to create the lock_guard object. If you
		// want high performance, then go with a pure mutex instead of lock_guard, but must remember to unlock it.
		// create lock_guard at first line of shared code. Can explicitly unlock the lock_guard by putting it in scope
		// on purpose:
		// { std::lock_guard ......}
		
		auto xlength = scr.x_max() - scr.x_min();
		int k = xlength*currRow;
		for(int j = scr.x_min(); j < scr.x_max(); ++j) {
			Complex c((double)j, (double)currRow);
			c = scale(scr, fract, c);
			colors[k] = escape(c, iter_max, func);
			k++;
		}
		
		// recurse until all rows are calculated
		if (rowI >0) calc(id);
		// print out when this thread has completed its section. 
		else std::cout << "done: " << id << std::endl;
	};
	
	// create a container of threads 
	std::vector<std::shared_ptr<std::thread>> containerOfThreads;

	// create threads and add them to the container. 
	for (unsigned int i = 1; i < numCores; ++i) {
		// start the thread. 
		containerOfThreads.push_back(std::make_shared<std::thread>(calc, i));
	}
	
	// do part of the processing on this processor. 
	calc(0);
	
	// join all the threads back together. 
	for (auto t : containerOfThreads) {
		t->join();
	}
}

void fractal(window<int> &scr, window<double> &fract, int iter_max, std::vector<int> &colors,
	const std::function<Complex( Complex, Complex)> &func, const char *fname, bool smooth_color) {
	auto start = std::chrono::steady_clock::now();
	get_number_iterations(scr, fract, iter_max, colors, func);
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time to generate " << fname << " = " << std::chrono::duration <double, std::milli> (end - start).count() << " [ms]" << std::endl;

	// Save (show) the result as an image
	plot(scr, colors, iter_max, fname, smooth_color);
}

void mandelbrot() {
	// Define the size of the image
	window<int> scr(0, 1600, 0, 1200);
	// The domain in which we test for points
	window<double> fract(-2.2, 1.2, -1.14, 1.14);

	// The function used to calculate the fractal
	auto func = [] (Complex z, Complex c) -> Complex {return z * z + c; };

	// int iter_max = 500;
	// bool smooth_color = true;
	
	int iter_max = 5000;
	bool smooth_color = false;
	
	const char *fname = "mandelbrot.png";
	std::vector<int> colors(scr.size());
	
	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}

int main() {

	mandelbrot();

	return 0;
}
