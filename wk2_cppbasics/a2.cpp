/*
q2.cpp
week 2 tutorial 1
Callum Howard
*/
#include <iostream>
#include <cstdlib>
#include <fstream>

// function prototype
namespace cs6771 {
	void order3(unsigned int& a, unsigned int& b, unsigned int& c);
}

int main(int argc, char *argv[]) // you can just be main()
{

	//variables
	unsigned int a, b, c;

	std::ifstream inputFile;
	inputFile.open("a1.txt");

	inputFile >> a >> b >> c ;

	std::cout<<"The 3 integers entered in old order are: \t"<< a <<", "<< b <<" and "<< c << std::endl;

	// call by reference function (modifying originals)
	cs6771::order3(a, b, c);

	std::cout<<"The 3 integers entered in ascending order are: \t"<< a <<", "<< b <<" and "<< c << std::endl;

	inputFile.close();

return EXIT_SUCCESS;
}

namespace cs6771 {
	void order3(unsigned int& a, unsigned int& b, unsigned int& c) {
		if (a > c) {
			int t = a;
			a = c;
			c = t;
		}
		if (b > c) {
			int t = b;
			b = c;
			c = t;
		}
		if (a > b) {
			int t = a;
			a = b;
			b = t;
		}
	}
}
