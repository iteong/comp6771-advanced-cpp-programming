/*
book.hpp
week 5 tutorial 4
Ivan Teong
*/

#ifndef BOOK_H
#define BOOK_H

#include <string>

/********************************************************************
 *
 ********************************************************************/

class Book {

// declared inside class as friends as need to access private members of class
friend bool operator== (const Book&, const Book&); // reading so const
friend bool operator!= (const Book &lhs, const Book &rhs);
friend std::cout& operator<< (const Book&);
friend bool operator< (const vector<Book>&);

public:
    Book();
    ~Book();
    Book(const std::string& name, std::string author, int isbn, double price); // why? const and reference for manufacturer only?
    operator std::string() const; // type conversion operator to convert Book class to std::string

  // getters
  std::string getName() const { return name_; }
  std::string getAuthor() const { return author_; }
  int getIsbn() const { return isbn_; }
  double getPrice() const  { return price_; }

private:
  std::string name_;
  std::string author_;
  int isbn_;
  double price_;
};


#endif // CAR_H
