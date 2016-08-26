/*
book.cpp
week 5 tutorial 4
Ivan Teong
*/

#include "book.hpp"

#include <iostream> // std::cout
#include <vector>
#include <algorithm> // std::sort

/*************************************************************************
 * Implementation of Car
 **************************************************************************/

// Write the function definition for a constructor that takes values for name, author, isbn and price and uses a member initializer list to set the value of each data member.
Book::Book(const std::string& name, std::string author, int isbn, double price) :
    name_{name}, author_{author}, isbn_{isbn}, price_{price}
{
}

// Write the overloaded == operator to compare if two book objects are identical
bool Book::operator== (const Book &lhs, const Book &rhs) {
    return (lhs.name_ == rhs.name_ &&
           lhs.author_ == rhs.author_ &&
           lhs.isbn_ == rhs.isbn_ &&
           lhs.price_ == rhs.price_);
}

// Write the overloaded != operator that calls the already overloaded == operator to return true when two book objects are not identical.
bool Book::operator!= (const Book &lhs, const Book &rhs) {
    return !(lhs == rhs);
}

// Write the overloaded << operator to print out the name, author, isbn and price of a book using std::cout
std::cout& Book::operator<< (const Book &item) {
    std::cout  << item.name << " " << item.author << " "
        << item.isbn << " " << item.price << std::endl;
} // using std::cout is different from using std::ostream which is default for this operator!


// Write the overloaded type conversion operator to enable the conversion of the Book class to a std::string in the form of "author, name"
Book(Book books=0)
    {
        m_books = books;
    }
Book::operator std::string() const { return std::string(m_books.author + ", " + m_books.name); }

// Create a main function that creates a std::vector<book>, add a few Book objects into the vector with different isbn numbers and prices
int main() {

    Book one{"book", "Ivan", 1338338385, 10.0};
    Book two{"book", "Ivan", 2038333333, 13.0};
    Book three{"book", "Ivan", 4438331111, 11.0};
    std::vector<Book> vec_book;
    vec_book.push_back(one);
    vec_book.push_back(two);
    vec_book.push_back(three);

    return 0;

    std::sort(vec_book.begin(), vec_book.end(), [](Book one, Book two, Book three) { // Call std::sort again with a lamda function as the predicate that sorts the books by price.
        return (one < two &&
               two < three);  
    });
}

// Write the overloaded < operator to allow you to sort books by their isbn number. Test this in your main method using std::sort
bool Book::operator <(const Book& book)
{
 if(Book.isbn < book.isbn)
 {
    return true;
 }
 return false;
}




