#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <ostream>

/*********************************************************************
 * The Book class
 *********************************************************************/

class Book {
public:
    Book(const std::string& name, const std::string& author,
         int isbn, double price);

    // getters

    // Defining member functions within the class definition should be
    // avoided as they reduce readability. Single line definitions are
    // (mostly) ok but for anything else use explicit inline defn.
    int getIsbn() const { return isbn_; }
    double getPrice() const;


    // Type conversion operators
    operator std::string () const;

    // Friend comparison operators
    friend bool operator==(const Book& a, const Book& b);
    friend bool operator!=(const Book& a, const Book& b);
    friend bool operator<(const Book& a, const Book& b);

    friend std::ostream& operator<<(std::ostream& out, const Book& b);
private:
  std::string name_;
  std::string author_;
  int isbn_;
  double price_;
};

// Note: this must be declared as inline!!!!
inline double Book::getPrice() const  { return price_; }

bool operator==(const Book& a, const Book& b);
bool operator!=(const Book& a, const Book& b);
bool operator<(const Book& a, const Book& b);

//std::ostream& operator<<(std::ostream& out, const Book& b);


#endif // BOOK_HPP
