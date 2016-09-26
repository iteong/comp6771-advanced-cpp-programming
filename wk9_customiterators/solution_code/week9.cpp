/**
 * Create a templated value-like library class to store books, movies etc
 * Each library item has the data and a set of related works
 * Each related work object has a ptr to the related works item.
 */

#include <iostream>
#include <typeinfo>
#include "Library.hpp"

//--------------------------------------------------------------------------
// class to store the description of an item.
//--------------------------------------------------------------------------
class Description
{
public:
	Description(const std::string& d) : desc{d} {}
	friend std::ostream& operator<<(std::ostream&, const Description &);
private:
	std::string desc;
};

// function to print out a description object
std::ostream& operator<<(std::ostream &os, const Description &d)
{
	os << d.desc;
	return os;
}

//--------------------------------------------------------------------------
// class to store a Book
//--------------------------------------------------------------------------
class Book
{
public:
	Book(const std::string& b) : name{b} {}
	friend bool operator==(const Book&, const Book &);
	friend std::ostream& operator<<(std::ostream&, const Book &);
private:
	std::string name;
};

// method to compare books
bool operator==(const Book& a, const Book & b)
{
	return a.name == b.name;
}

// method to print the book details
std::ostream& operator<<(std::ostream &os, const Book &b)
{
	os << b.name;
	return os;
}

//--------------------------------------------------------------------------
// main for week9 tute
//--------------------------------------------------------------------------

void tute_week9()
{
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

	std::cout << std::boolalpha << "confirming that Percy Jackson is in library: "
              << bookLibrary.inLibrary(percyJackson) << std::endl;

    std::cout << std::endl << "----- New for week 9 -----" << std::endl << std::endl;



    //-------------------------------------------------------------------------
    // Testing the iterator
    //-------------------------------------------------------------------------
    // TODO Q12
	auto it = bookLibrary.begin();
    auto itEnd = bookLibrary.end();

    // This typedef will fail if we make a typo in LibraryItemIterator<>::value_type
//    typedef std::iterator_traits<LibraryItemIterator<Book>>::value_type iib_value_type;

    ++it;
    std::cout << "Iterator output: " << *it << std::endl;

    std::cout << "Iterator loop:" << std::endl;
    for (auto book : bookLibrary) {
        std::cout << "\t" << book << std::endl;
    }
    // show that it is a forward iterator by updating the stored value.
    // and then reprinting the related works.
    std::cout << std::endl << "Showing that we can modify a deferenced iterator:" << std::endl;
    *it = Book("Lord of the Rings");
    bookLibrary.printRelated(harryPotter);

    std::cout << std::endl << "Returning a pointer: ";
    auto ptrTest = it.operator->();
    std::cout << ptrTest << " " << *ptrTest << std::endl << std::endl;
}

//--------------------------------------------------------------------------
// main
//--------------------------------------------------------------------------

void extras();

int main()
{
    tute_week9();
//    extras();
}

//--------------------------------------------------------------------------
// Other stuff
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Test1 : Show postfix increment IS provided by STL iterators
//--------------------------------------------------------------------------

void extras()
{
    std::vector<int> v{1,2,3,4,5};

    // Note: explicitly using the postfix increment operator to prove
    // that it is still defined!
    for (auto it = v.begin(); it != v.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;


    // Want to confirm that the value_type trait is the same for
    // iterator and const_iterator

    // Define typedefs for the value_type of a const and non-const iterator
    typedef std::iterator_traits<std::vector<int>::iterator>::value_type nc_value_type;
    typedef std::iterator_traits<std::vector<int>::const_iterator>::value_type c_value_type;

    if (typeid(nc_value_type) == typeid(c_value_type))
        std::cout << "Underlying value_type for const and non-const are the same" << std::endl;
    else
        std::cout << "Underlying value_type for const and non-const are different" << std::endl;
}
