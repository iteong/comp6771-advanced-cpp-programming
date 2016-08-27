/*
book.cpp
week 5 tutorial 4
Callum Howard
*/

#include "book.hpp"

#include <utility> // std::move

#include <limits> // numeric_limits
#include <cmaths> // fabs

#include <sstream> // stringstream

#include <iostream> // std::cout
#include <vector>
#include <algorithm> // std::sort

/*************************************************************************
 * Implementation of Car
 **************************************************************************/

// Write the function definition for a constructor that takes values for name, author, isbn and price and uses a member initializer list to set the value of each data member.
//Book::Book(const std::string& name, const std::string& author, int isbn, double price) :
//    name_{name}, author_{author}, isbn_{isbn}, price_{price} {}
Book::Book(std::string name, std::string author, int isbn, double price) :
    name_{std::move(name)}, author_{std::move(author)}, isbn_{isbn}, price_{price} {} // std::move so don't need const and &
// move resources of copy of name directly into name_ (modern way of C++ without const and &)

// Write the overloaded == operator to compare if two book objects are identical
bool operator== (const Book& lhs, const Book& rhs) { // not Book::operator as not member of class now
    return lhs.name_ == rhs.name_ and // same as &&
           lhs.author_ == rhs.author_ and
           lhs.isbn_ == rhs.isbn_ and
           // precision to be made sure
           std::fabs(lhs.price_ == rhs.price_) < std::numeric_limits<double>::epsilon();
}

// Write the overloaded != operator that calls the already overloaded == operator to return true when two book objects are not identical.
bool operator!= (const Book &lhs, const Book &rhs) {
    return not (lhs == rhs);
}

// Write the overloaded << operator to print out the name, author, isbn and price of a book using std::cout
std::ostream& operator<< (std::ostream& os, const Book& item) {
    return os   << "Name: \t" << item.name << ", " 
                << "Author: " << item.author << ", " 
                << "ISBN: " << item.isbn << ", " 
                << "Price: " << item.price;
} // using std::cout is different from using std::ostream which is default for this operator!


// Write the overloaded type conversion operator to enable the conversion of the Book class to a std::string in the form of "author, name"
operator std::string() const {
    std::stringstream ss;
    ss << "author: \t" << rhs.author_ << "," << rhs.name_;
    return ss.str();
}


// Create a main function that creates a std::vector<book>, add a few Book objects into the vector with different isbn numbers and prices
int main() {

    Book one{"book", "Ivan", 1338338385, 10.0};
    Book two{"book", "Ivan", 2038333333, 13.0};
    Book three{"book", "Ivan", 4438331111, 11.0};

    std::cout << "one " << (one == two ? "==" : "!=") << " two" << std::endl;
    std::cout << one << std::endl;

    std::vector<Book> vec_book;
    vec_book.push_back(one);
    vec_book.push_back(two);
    vec_book.push_back(three);

    return 0;

    std::sort(vec_book.begin(), vec_book.end(), 
        [](const Book& a, const Book& b) -> bool
        { // Call std::sort again with a lamda function as the predicate that sorts the books by price.
            return a.getPrice() < b.getPrice();
        }
        );

}

// Write the overloaded < operator to allow you to sort books by their isbn number. Test this in your main method using std::sort
bool Book::operator <(const Book& a, const Book& b)
{
 return a.isbn_ < b.isbn_;
}




