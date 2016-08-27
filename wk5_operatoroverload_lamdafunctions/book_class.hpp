/*
book.hpp
week 5 tutorial 4
Callum Howard
*/

#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <ostream>

/********************************************************************
 *
 ********************************************************************/

class Book {

// declared inside class as friends as need to access private members of class

public:
  Book();
  // constructors
  // const and & for strings coz dun want to modify the strings, not used for int and double coz int smaller memory size than pointer (reference is pointer under the hood) and double is same memory size as pointer
  // int and double going to have copies as copy by value so doesn't matter
  // Book(const std::string& name, const std::string& author, int isbn, double price); // why? const and reference for manufacturer only?
  Book(std::string name, std::string author, int isbn, double price); // modern way rather than line 29

  // type conversion
  operator std::string() const; // type conversion operator to convert Book class to std::string
  
  ~Book();

    // prototype functions declared as friends to access private members
  friend bool operator== (const Book& lhs, const Book& rhs); // book1 (*.this) == book2, const after ) don't modify the object
  friend bool operator!= (const Book& lhs, const Book& rhs);

  // stream operator
  friend std::ostream& operator<< (std::ostream& os, const Book& item);

  friend bool operator< (const vector<Book>&);

  // getters
  inline int getIsbn() const { return isbn_; }
  inline double getPrice() const  { return price_; }

private:
  std::string name_;
  std::string author_;
  int isbn_;
  double price_;
};

// non-member operators (outside class to handle situation where LHS and RHS objects swapped)
bool operator== (const Book& lhs, const Book& rhs); // book1 (*.this) == book2, const after ) don't modify the object
bool operator!= (const Book& lhs, const Book& rhs);
std::ostream& operator<< (std::ostream& os, const Book& item);
bool operator< (const Book& a, const Book& b);


#endif // CAR_H
