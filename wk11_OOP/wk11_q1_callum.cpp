// week11.cpp
// Callum Howard, 2016

#include <iostream>

class Base {
public: 
	// use getter so that no need to notify client if change the variable name
	// use const as i is not supposed to be modifiable, it is a private member
	virtual const int &getI() const { return i; } // can put virtual to override

private:
	int i;
};

class Derived : public Base {
public:
  void foo(Derived &o) {
    j = o.getI() + o.j;
    // j = o.getI()++ + o.j allowed, if Base clase public is non-const: int &getI() { return i; }
    // virtual can allow you to override method
  }
private:
  int j;
};

// imagine you writing a btree class for client, and intend for client to inherit that class
// fixed header/interface class that will change implementation underneath later
// by making it protected, you need to notify client later if you change it from i to k later
// Solution: by using getters, like &getI() and using that in Derived class, where j = o.getI() + ...,
// don't need to ask client to modify their extended class


int main () {
	std::cout << "hello world" << std::endl;
}
