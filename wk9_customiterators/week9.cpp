/**
 * Create a templated value-like library class to store books, movies etc
 * Each library item has the data and a set of related works
 * Each related work object has a ptr to the related works item.
 */ 
#include <iostream>
 
#include "Library.hpp"

// class to store the description of an item.
class Description {
public:
	Description(const std::string& d) : desc{d} {}
	friend std::ostream& operator<<(std::ostream&, const Description &);
private:
	std::string desc;
};

// function to print out a description object
std::ostream& operator<<(std::ostream &os, const Description &d) {
	os << d.desc;
	return os;
}

// class to store a Book
class Book {
public:
	Book(const std::string& b) : name{b} {}
	friend bool operator==(const Book&, const Book &);
	friend std::ostream& operator<<(std::ostream&, const Book &);
private:
	std::string name;
};

// method to compare books
bool operator==(const Book& a, const Book & b) {
	return a.name == b.name;
}

// method to print the book details
std::ostream& operator<<(std::ostream &os, const Book &b) {
	os << b.name;
	return os;
}

// TODO: create this class
class Movie {
	
};

int main() {
	
	// create a book library
	Library<Book,Description> bookLibrary;
	
	// add some book objects
	Book harryPotter{"Harry Potter"};
	Book percyJackson{"Percy Jackson"};
	bookLibrary.add(harryPotter);
	bookLibrary.add(percyJackson);
	
	// create a description and add it between the two books
	Description d{"Percy Jackson is a similar childrens book that readers of Harry Potter may like"};
	bookLibrary.addRelated(harryPotter,percyJackson,d);
	
	// print books related to Harry Potter
	bookLibrary.printRelated(harryPotter);
	
	std::cout << std::boolalpha << "confirming that Percy Jackson is in library: " << bookLibrary.inLibrary(percyJackson) << std::endl;
		
	/*auto it = bookLibrary.begin();
	auto itEnd = bookLibrary.end();
	++it;
	std::cout << *it << std::endl;
	
	for (auto books : bookLibrary) {
		std::cout << books << std::endl;
	}
	
	// show that it is a forward iterator by updating the stored value. 
	// and then reprinting the related works. 
	*it = Book("Lord of the Rings");
	bookLibrary.printRelated(harryPotter);
	
	auto ptrTest = it.operator->();
	std::cout << ptrTest << " " << *ptrTest << std::endl;*/
}
