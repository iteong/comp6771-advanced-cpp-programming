// week11.cpp e.g. 2
// Callum Howard, 2016

#include <iostream>

class B {
public:
  virtual void f() { 
    std::cout << "B "; 
  }
};

class D : public B {
public:
  virtual void f() { 
    std::cout << "D "; 
  }
};

class A {
	int a, b, c;
};

class B: public A {
	int x, y, c;
};

int main() {
  B b;
  D d;
  b = d; // object slicing: all the stuff that isn't d sliced off
  B &pb = b;
  b.f(); // print B, overwritten virtual f sliced off derived class's extra stuff for D, left only stuff for base class
  pb.f(); // print B

  B b{};
  A a = b;
  // a now contains only the objects that:
  // - contained a, b and c
  // - are in B class and also in A class: c
  // extra stuff in B (x and y) are "sliced off" (coz base class called to construct derived class, before the modification of derived method)
}

// potential exam question: what will be the output?