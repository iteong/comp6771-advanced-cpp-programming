#include <iostream>
#include <vector>
#include <algorithm>
#include "book.hpp"

//int main() { }

void print(const std::string& title, const std::vector<Book>& books);

void tute_question();
void test_overload();
void test_mystring();
void test_lambda();

/********************************************************************
 * The main tutorial question.
 *
 ********************************************************************/

int main()
{
    tute_question();
//    test_overload();
//    test_mystring();
//    test_lambda();
    return 0;
}

/********************************************************************
 * The basic of the tute question
 ********************************************************************/

void tute_question()
{
    std::vector<Book> books1 =
        { Book{"Book1", "Author1", 2222, 12.2},
          Book{"Book2", "Author2", 1111, 11.50},
          Book{"Book3", "Author3", 3333, 10.50}};

    std::vector<Book> books2 =
        { Book{"Book1", "Author1", 2222, 12.2},
          Book{"Book2", "Author2", 1111, 11.50},
          Book{"Book3", "Author3", 3333, 10.50}};

    print("Books:", books1);

    // For fun call the std::vector<Book> operator==() overload which in
    // turn calls Book operator==() overload.
    std::cout << "Vector of books are equal: "
              << "books1 " << (books1 == books2 ? "==" : "!=")
              << " books2" << std::endl << std::endl;

    std::sort(books1.begin(), books1.end());
    print("Default (ISBN) sorted books:", books1);

    std::sort(books1.begin(), books1.end(),

              [](const Book& a, const Book& b) -> bool
              {
                  return a.getPrice() < b.getPrice();
              }
        );

    print("Price sorted books:", books1);
}


/********************************************************************
 * Highlighting the problems you can cause yourself when abusing
 * overload operator.
 ********************************************************************/

void test_overload()
{
    Book book{"Book1", "Author1", 2222, 12.2};

    std::string bookstr = book;
    std::cout << "Auto conversion: " << bookstr << std::endl;
    std::cout << std::endl;

    // But be careful with type conversion overloading

    // uses operator<<() for Book
    std::cout << "Using operator<<() => " << book << std::endl;
    std::cout << std::endl;

    // uses Book std::string conversion and then operator<<() for
    // std::string.
    std::cout << "Using operator std::string() => "
              << static_cast<std::string>(book) << std::endl;
    std::cout << std::endl;
}



/********************************************************************
 * helper to print a list of books
 ********************************************************************/

void print(const std::string& title, const std::vector<Book>& books)
{
    std::cout << title << std::endl;
    for (const auto& b: books)
    {
        std::cout << "\t";
        std::cout << b << std::endl;
    }
    std::cout << std::endl;
}

 /********************************************************************
 * Test showing the difference between member and non-member
 * comparison overloading.
 ********************************************************************/

struct MyString
{
    std::string s_;
    MyString(const char* s) : s_{s}{};

    // Good
    friend bool operator==(const MyString& a, const MyString& o);

    // Bad
//    bool operator==(const MyString& o) const { return s_ == o.s_; }

};

bool operator==(const MyString& a, const MyString& b)
{
    return a.s_ == b.s_;
}

void test_mystring()
{
    const char* a = "hello";
    const MyString b = "hello";

    // Compiler error with member operator==()
    if (a == b){ std::cout << "a == b" << std::endl; }
    std::cout << std::endl;

    // Ok with either member or non-member operator=()
    if (b == a){ std::cout << "b == a" << std::endl; }
    std::cout << std::endl;

}

 /********************************************************************
 * Test showing the lambda capturing.
 ********************************************************************/

void special_sort(std::vector<Book>& books, const std::string& special)
{
    std::sort(books.begin(), books.end(),
              [&special](const Book& a, const Book& b)
              {
                  if (static_cast<std::string>(a) == special) return true;
                  if (static_cast<std::string>(b) == special) return false;
                  return a.getPrice() < b.getPrice();
              });
}


void test_lambda()
{
    std::vector<Book> books =
        { Book{"Book1", "Author1", 2222, 200.2},
          Book{"Book2", "Author1", 1111, 8.50},
          Book{"Book10", "Author10", 1111, 11.50},
          Book{"Book20", "Author20", 3333, 10.50}};

    print("Pre-sort", books);

    special_sort(books, "Author1,Book1");

    print("Post special sort", books);
}


