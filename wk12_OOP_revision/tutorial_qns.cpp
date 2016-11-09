#include <iostream>

1.
class A1 {
public:
  A1() { 
    std::cout << "A1 "; //4. print "A1"
  }						// 8. print "A1"
};	

class A2 {
public:
  A2() {
    std::cout << "A2 "; // 6. print "A2"
    a1 = new A1(); // 7. call A1()
  }
private:
  A1 *a1;
};

class A3 {
public:
  A3() {
    std::cout << "A3 "; // 2. print "A3"
    a1 = new A1(); // 3. call A1()
    a2 = new A2(); // 5. call A2()
  }
private:
  A1 *a1;
  A2 *a2;
};

int main() {
  A3 *a3 = new A3(); // 1. call constructor A3
}

1. A3, A1, A2, A1

2.
class A3  : public A2 { // inheritance => call A2 constructor first before going into A3 => prints A2 first, then A1, then jump to A3
public:
  A3() {
    std::cout << "A3 ";
    a1 = new A1();
    a2 = new A2();
  }
private:
  A1 *a1;
  A2 *a2;
};

2. A2, A1, A3, A1, A2, A1

1.
#include <iostream>

struct X { // 4. X destructor is called by A and prints X
  ~X() { std::cout << "~X() "; }
};

struct Y { 
  ~Y() { std::cout << "~Y() "; }
};

class A { // 3. A's destructor gets called, which prints A, then calls destructor for X
  X x;
public:
  ~A() { std::cout << "~A() "; }
};

class B : public A { // 2. calls B, prints B, calls destructor for Y (which prints Y), then calls A's destructor
  Y y;
public:
  ~B() { std::cout << "~B() "; }
};

int main() { 
  B b; // 1. create B (remember that destructor gets called when you leave scope) => goes to B's destructor when reach end of }
}

1. ~B ~Y ~A ~X
2.
int main() { 
  B* b = new B; 
}

Nothing gets printed due to memory leaks (created in main but never call destructor explicitly as it is allocated on heap)

int main() { 
  B* b = new B;
  delete b;
}

1.
#include <list>
#include <iostream>

class X {
public:
  X() { std::cout << "ctor "; }
  X(const X&) { std::cout << "copy-ctor "; }
  ~X() { std::cout << "dtor "; }
};

int main() {
  std::list<X*> l; // 1. pointer to X, so no constructor is called, no destructor is called
  X *x = new X(); // 2. X's constructor is called (ctor), but destructor not called when leave scope coz need explicit delete for *
  X y; // 3. X's constructor is called (ctor) => destructor for y gets called when leave scope (dtor)
  l.push_back(x); // 4. x is a pointer, so X's constructor is not called coz pointer copied => need to be a copy, destructor is also not called
  l.push_back(&y); // 5. ref to Y, so X's constructor not called, neither is destructor
}
1. ctor ctor dtor

2. 
int main() {
  std::list<X*> l;
  X *x = new X();
  X y;
  l.push_back(x);
  l.push_back(&y);
  std::list<X> l2; // 2nd dtor => when this second list goes out of scope, the destructor for X gets called
  l2.push_back(y); // when pushing back y, which is an X, copying it into the list
}
2. ctor ctor copy-ctor dtor dtor // the 2 destructors are for y and the copy of y

// Revision questions
1. int, *int, &int

int a = 42;
int& b = a;

int is lvalue
int* is lvalue // usage = when doing std::swap, can pass in pointers to swap values || when using ptrs, need to free the memory after using it
int& is rvalue // usage = references can never be null, cannot be changed like ptrs, only refer to same object all the time (although it is pointers under the hood) => safer but less flexible
// pts abd ref is larger in memory size than pure int (coz contains pointers)

2. // read backwards
const int& getValueAtIndex(int i); // get value at int and it is const => cannot change the returned type (it is an lvalue coz stored in memory), if it's double &&, then it is an rvalue
int getValueAtIndex(const int i); // can only pass in unmodifiable i (parameter is const) => always better to make a copy of i and modify that instead
int getValueAtIndex(int i) const; // cannot modify the member variables that the class belongs to





