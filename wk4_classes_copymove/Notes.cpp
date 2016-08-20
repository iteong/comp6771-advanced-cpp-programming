// Every C++ expression is either an lvalue or an rvalue. An lvalue refers to an object that persists beyond a single expression.
// You can think of an lvalue as an object that has a name. All variables, including nonmodifiable (const) variables, are lvalues.
// An rvalue is a temporary value that does not persist beyond the expression that uses it.

int a, b;
// Lvalue (address) and Rvalue (value)
a = 42; // can &a to get Lvalue coz it has assigned memory and address after this assignment
// variable, a is an Lvalue coz it persists beyond the expression that defines it

(a * b) = 64; // error coz LHS is Rvalue/expression, cannot &(a * b) to find the address to assign the value of 64
(a + 1) = 5; // error, LHS must be Lvalue, also cannot &(a + 1) to get address to assign it the value of 5
7 = a // error, LHS must be Lvalue

a = 6 = 5; // won't work coz whole thing is Rvalue
(a=6) = 5; // will work and give result of 5 for a, coz as long as can & the whole thing it is Lvalue

// uniform initializer

// call constructor
std::string manufacture("toyota"); // this is not good for initializing coz it can be function prototype or variable construction

auto manufacture = std::string("toyota"); // preferred

// this is without member initialization list, have 2 calls so less function calls for member initializer list as only 1 call
Car::Car(std::string value1, unsigned int value2) {
        manufacture_ = value1;
        numSeats = value2;
}
// another advantage for member initializer list is that it can work with const for the private variables
    const std::string manufacturer;
    unsigned int numSeats;

// Big 5, copy constructors, move constructors etc.

std::string manufacture {"Totoya"};
std::string a{manufacture}; // copy constructor, copy manufacture into a

// move constructor
std::vector<int> b = {1,2,3,4,5};
std::vector<int> c{std::move(b)};

// e.g. b --> linked list header
// when use move constructor, c ---> to linked list header of b
// so both b and c points to same original linked list, but when use move to get c to point to b, then don't use b anymore coz it is undefined
// std::move makes b into a temporary R-value reference, &&b so it is ready to be destroyed unless it is reassigned to another data