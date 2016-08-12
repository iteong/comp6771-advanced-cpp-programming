/*
q1.cpp
week 2 tutorial 1
Callum Howard
*/
#include <iostream>
#include <cstdlib>
#include <fstream>

// function prototype
namespace cs6771 {
	void order3(int *a, int *b, int *c);
	//void order3(const int *a, const int *b, const int *c); // a is a pointer to constant int
	//const unsigned int &a // a is a reference to a const unsigned inst
}

int main(int argc, char *argv[]) // you can just be main()
{

	//variables
	int a, b, c;
	
	//output and then input
	std::cout<<"Enter 3 integers: "<<std::endl; 
	// endl = end line and also does fflush similar to c, but you may just want to \n if you don't want to flush buffer	coz it will be faster				
	std::cin >> a >> b >> c;

	// call by value function (a copy of original variables)
	cs6771::order3(&a, &b, &c); // input addresses by &

	std::cout<<"The 3 integers entered in descending order are: \t"<< a <<", "<< b <<" and "<< c << std::endl;

	std::ofstream outputFile;
	outputFile.open("a1.txt");

	outputFile << a << " " << b << " " << c << std::endl;

	outputFile.close();

return EXIT_SUCCESS;
}

namespace cs6771 {
	void order3(int *a, int *b, int *c) {
		if (*a < *c) {
			int t = *a;
			*a = *c;
			*c = t;
		}
		if (*a < *b) {
			int t = *a;
			*a = *b;
			*b = t;
		}
		if (*b < *c) {
			int t = *b;
			*b = *c;
			*c = t;
		}
	}
}

