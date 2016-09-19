/**
 * Create a templated value-like library class to store books, movies etc
 * Each library item has the data and a set of related works
 * Each related work object has a ptr to the related works item.
 */
#include <iostream>

#include "Library.hpp"

// -------------------------------------------------------------------------------
// class to store the description of an item.
// -------------------------------------------------------------------------------
class Description
{
public:
	Description(const std::string& d) : desc{d} {}
	friend std::ostream& operator<<(std::ostream&, const Description &);
private:
	std::string desc;
};

// -------------------------------------------------------------------------------
// function to print out a description object
// -------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream &os, const Description &d)
{
	os << d.desc;
	return os;
}

// -------------------------------------------------------------------------------
// class to store a Book
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// TODO: create this class
//
// simply duplicate the Book class functions
//
// Note: try commenting out the operator==() overload to see the error
// message when instantiating the Library template.
// -------------------------------------------------------------------------------
class Movie
{
public:
	Movie(const std::string& b) : name{b} {}
    friend bool operator==(const Movie&, const Movie &);
	friend std::ostream& operator<<(std::ostream&, const Movie &);
private:
	std::string name;
};


// method to compare movies
bool operator==(const Movie& a, const Movie & b)
{
    if (&a == &b) return true;

	return a.name == b.name;
}

// method to print the book details
std::ostream& operator<<(std::ostream &os, const Movie &b)
{
	os << b.name;
	return os;
}


// -------------------------------------------------------------------------------
// main
// - create a library, add some books, add some relationships.
// - Then print and remove items.
// -------------------------------------------------------------------------------

int tute_main()
{

	// create a book library
	Library<Book,Description> bookLibrary;

	// add some book objects
	Book harryPotter{"Harry Potter"};
	Book percyJackson{"Percy Jackson"};
	bookLibrary.add(harryPotter);
	bookLibrary.add(percyJackson);

    //-------------------------
    // Q9 - Test adding duplicates

    // Note: the Library function relies on the Book::operator==()
    // overload. The code won't compile without it.

//	bookLibrary.add(harryPotter);

//    Book harryPotter2{"Harry Potter"};
//	bookLibrary.add(harryPotter2);


    //-------------------------



	// create a description and add it between the two books
	Description d{"Percy Jackson is a similar childrens book that readers of Harry Potter may like"};
	bookLibrary.addRelated(harryPotter,percyJackson,d);

	// print books related to Harry Potter
	bookLibrary.printRelated(harryPotter);

	std::cout << std::boolalpha << "confirming that Percy Jackson is in library: "
              << bookLibrary.inLibrary(percyJackson) << std::endl;

	// remove Percy Jackson
	std::cout << "number of items in library after removal: "
              << bookLibrary.remove(percyJackson) << std::endl;

	std::cout << std::boolalpha << "confirming that Percy Jackson is in library: "
              << bookLibrary.inLibrary(percyJackson) << std::endl;

	// print books related to Harry Potter
	bookLibrary.printRelated(harryPotter);


	// create a book library
	Library<Movie, std::string> movieLibrary;
    Movie m1{"Blah1"};
    Movie m2{"Blah2"};
    movieLibrary.add(m1);
    movieLibrary.add(m2);
    movieLibrary.addRelated(m1,m2, "Some relation");


    return 1;
}

int main()
{
    try
    {
        tute_main();
        return 1;
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl;
    }
}
