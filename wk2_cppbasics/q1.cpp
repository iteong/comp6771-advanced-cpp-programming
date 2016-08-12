/*
q1.cpp
week 2 tutorial 1
Ivan Teong
*/
#include <iostream>
#include <fstream>

using namespace std; // may pollute global namespace

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

	void writeToFile(int *a, int *b, int *c)
	{
		ofstream outputFile;
		outputFile.open("out.txt", ios::out); // ios::out - writing out to this file
		outputFile << *a <<" "<< *b <<" "<< *c << endl;
		outputFile.close();

	}

}


int main()
{

	//variables
	int d, e, f;
	
	//output and then input
	cout << "Enter 3 integers: " << endl;								
	cin >> d;
	int* a = &d;
	cin >> e;
	int* b = &e;
	cin >> f;
	int* c = &f;

	// call by value function (a copy of original variables)
	cs6771::order3(a, b, c);

	cout << "The 3 integers entered in descending order are: "<< *a <<", "<< *b <<" and "<< *c << endl;

	cs6771::writeToFile(a, b, c);

return 0;
}

