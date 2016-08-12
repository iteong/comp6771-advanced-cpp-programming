/*
q1.cpp
week 2 tutorial 1
Ivan Teong
*/
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

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


int main()
{
	// reading from input file
	ifstream inputFile;
	inputFile.open("out.txt", ios::in); // ios::out - writing out to this file

	// The data in a string
	string data;	
	getline(inputFile, data);
	inputFile.close();

	// variables
	stringstream linestream(data); // data in a stream (this could be a file)
	unsigned int a, b, c;

	linestream >> a >> b >> c;

	cout<< a << b << c <<endl;

	// call by reference so changing values of a, b and c permanently
	cs6771::order3(a, b, c);

	cout << "The 3 integers entered in ascending order are: "<< a <<", "<< b <<" and "<< c << endl;

return 0;
}

