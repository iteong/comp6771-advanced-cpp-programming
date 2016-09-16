// Callum Howard, 2016

#include <iostream>
#include <vector>


// general template (will be called if string, double or euclidean vector)
template <typename T>
bool printIfWholeNumber(const T&) {
	return false;
}

// template specialization that will override the general template that caters for int input 
// (must be pure int, unsigned int also will call general template, long won't be cast automatically to int in template too)
template <> 
bool printIfWholeNumber<int>(const int& i) {
	std::cout << i;
	return true;
}


template <typename T>
unsigned int printAndCountWholeNumbers(const T& d) {
	if (printIfWholeNumber(d)) { // if true, return 1, otherwise, return 0
		std::cout << " ";
		return 1;
	}
	return 0;
}


template <typename T, typename... U>
unsigned int printAndCountWholeNumbers(T head, U... tail) { // ... means any number of arguments
	// call a function to work out if the "head" is a whole number, 1st param
	auto count = printAndCountWholeNumbers(head); // it will become an int as defined above, 2nd param = head, the rest is tail ... recursive

	// call a function to process the tail
	// writing a recursive function
	count += printAndCountWholeNumbers(tail...); // will make the first of tail the head, and the rest of numbers the ...


	// return the number of whole numbers in the variadic parameters
	return count;

}

template <typename T>
unsigned int printAndCountWholeNumbers(const std::vector<T>& vd) {
	auto count = 0;
	for (auto d : vd) { // range-based for loop => encourage to use this
		auto dCopy = d;
		// work out if d is a whole number
		dCopy -= static_cast<int>(d);
		if (dCopy == 0) {
			// call: printIfWholeNumber 
			// and add to count.
			count += printAndCountWholeNumber<int>(static_cast<int>(d)); // vector can take in any type, but will have problem if never put static cast a string to int, so need to static cast here


		}
	}
	return count;
}

int main() {


	auto c = printAndCountWholeNumbers(1, 2.5, 3, 4.5, 5.5, 6, 7.0, -5, "2" );
	std::cout << "count = " << c << std::endl;

	printAndCountWholeNumbers<decltype(test_bool)>(test_bool); // decltype can be used for template type parameter, it will find type is bool


	std::vector<double> d = {1.2, 32.0, 3.2, 5.30, 5.4, 6, -5};
	auto dc = printAndCountWholeNumbers(d);
	std::cout << "count = " << dc << std::endl;

	std::vector<unsigned int> vui = {65, 343, 21, 3}; // vector will only work if it is <int> and not <unsigned int>
	dc = printAndCountWholeNumbers(vui);
	std::cout << "count = " << dc << std::endl;



}