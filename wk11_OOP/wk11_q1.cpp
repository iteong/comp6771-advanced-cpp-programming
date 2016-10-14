// week11.cpp
// Callum Howard, 2016

#include <iostream>

class Base {
protected: // changed to protected from private
  int i;
};

// can't access protected member i through Base, needs to do it through Derived class (they are similar to private members)
// search access specifiers (substitution principle)
class Derived : public Base {
public:
	void foo(Derived &o) {
		j = o.i + o.j;
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
