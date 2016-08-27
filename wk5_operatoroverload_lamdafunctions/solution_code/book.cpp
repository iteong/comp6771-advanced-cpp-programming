#include <sstream>
#include "book.hpp"

/*********************************************************************
 * Book class implementation
 *********************************************************************/

Book::Book(const std::string& name, const std::string& author,
           int isbn, double price) :
    name_{name}, author_{author}, isbn_{isbn}, price_{price}
{ }

//int Book::getIsbn() const { return isbn_; }
//double Book::getPrice() const  { return price_; }

Book::operator std::string () const
{
    // potentially more efficient
    std::string tmp = author_;
    tmp += ",";
    tmp += name_;
    return tmp;

/*
    // more flexible
    std::stringstream ss;
    ss << author_ << "," << name_;
    return ss.str();
*/
}

bool operator==(const Book& a, const Book& b)
{
    return (a.name_ == b.name_) && (a.author_ == b.author_) &&
        (a.isbn_ == b.isbn_) && (a.price_ == b.price_);
}

bool operator!=(const Book& a, const Book& b)
{
    return !(a == b);
}

bool operator<(const Book& a, const Book& b)
{
    return a.isbn_ < b.isbn_;
}


// Note: the use of the C++11 raw string R"( .... )" syntax.
std::ostream& operator<<(std::ostream& out, const Book& b)
{
    return out << "Name: \"" << b.name_ << "\", "
               << R"xxx(Author: ")xxx" << b.author_ << R"(", )"
               << "ISBN: " << b.isbn_ << ", "
               << "Price: " << b.price_;
}









