// week11.cpp e.g. 3
// Callum Howard, 2016

#include <iostream>

class A {          
public:               
        virtual void f(int) {}
        virtual int g() {}
        void a() {}
	virtual ~A() {}
};
class B : public A {   
public:                       
        virtual void f(int) {}        
        virtual int h() {}
};
class C : public B {       
public:                   
	virtual void f(int, int) {}
        virtual void x() {}     
	static void b() {}
};

int main() {

}

// potential exam question: virtual => dynamic binding: opposite of stack binding (which is a function without virtual)
// without virtual = static, static means it is determined at compile time, statically binded at compile time for the function
// adding virtual will allow the compiler to determine which version of function to be run (dynamic binding) => determined at runtime

// Vtables: grab dynamically binded functions
// A  | 
// 0  | &A::f(int)
// 1  | &A::g()
// 2  | &A::~A()

// B  | 
// 0  | &B::f(int) // change from A's f to B's f since it is virtual
// 1  | &A::g()
// 2  | &B::~B() // destructor must be owned by own class (which in this case is a derived class)
// 3  | &B::h()

// C  | 
// 0  | &B::f(int) // change from A's f to B's f since it is virtual
// 1  | &A::g()
// 2  | &C::~C() // destructor must be owned by own class (which in this case is a derived class)
// 3  | &B::h()
// 4  | &C::f(int, int)
// 5  | &C::x()
// // don't include b() for C as it is static

// Rule: destructors owned by its own class, and static members don't go into vtable

// Revision Question:
// A friend function of a class can access privates of the current generation class
// therefore, it can access all data members of the current (derived) class (but not the base/parent class and not its derived/child class)






