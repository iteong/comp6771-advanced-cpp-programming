// Callum Howard, 2016

#include <iostream>
#include <vector>
#include <memory> // unique_ptr


template <typename T>
std::unique_ptr<T> make_unique(T t) {
	return std::unique_ptr<T>(new T(t)); // returns unique ptr to given thing
}

template <typename T>
std::unique_ptr<T> make_unique(std::unique_ptr<t>& t) { // pass reference to unique_ptr
	return std::unique_ptr<T>(new T{*up}); // returns unique ptr to given unique_ptr type on heap
}

template <typename T>
T getBase(T t) {
	return t;
}

template <typename T>
auto getBase(T *t) -> decltype(*t) { // a ptr to a ptr => to call it successfully, need to getBase from *t
	return *t;
}

int main() {

	// for literals, anything with dec place is automatically a double for auto, unless it has F behind then it's a float - ics.com
	auto dptr = make_unique(3.14); // makes new double heap object that is pointed to by unique ptr
	std::cout << *dptr << std::endl;

	auto dptr2 = make_unique(dptr); // will try to call above function make_unique(T t) and replace T with unique_ptr, but it will fail coz you cannot copy a unique_ptr
	std::cout << *dptr2 << std::endl; // a unique pointer will not be unique if you can copy it => error!, to resolve it, create another function @ make_unique(std::unique_ptr<t>& t)

	int i = 9;
	int* iptr = &i;
	std::cout << getBase(i) << std::endl;
	std::cout << getBase(iptr) << std::endl; // unique_ptr will not match a template specialisation that is auto getBase(T *t) -> decltype(*t)
	// TO DO!!!: a new template for this

}