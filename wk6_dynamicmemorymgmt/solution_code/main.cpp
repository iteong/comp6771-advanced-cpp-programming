#include <memory>
#include <iostream>
#include "school.hpp"

void test_tute5();
void test_unique_ptr();
void test_decltype();

// ----------------------------------------------------------------

int main()
{
    test_tute5();
//    test_unique_ptr();
//    test_decltype();
}
// ----------------------------------------------------------------

void test_tute5()
{

	School s(100u);
	s.addCourse("CS1917");
	s.addCourse("CS2911");
	s.addCourse("CS6771");

	if (!s.addCourse("CS1917"))
    {
		std::cout << "can't add a duplicate course" << std::endl;
	}

	// C++14 string literals
	//using namespace std::string_literals;
	//s.addCourse("CS1917"s);
	//s.addCourse("CS2911"s);
	//s.addCourse("CS6771"s);

	// add some students.
	auto tomStudentId = s.addStudent("Tom");
	auto jerryStudentId = s.addStudent("Jerry");
	auto homerStudentId = s.addStudent("Homer");

	// add students to some courses
	try
    {
		s.addStudentToCourse(tomStudentId,"CS1917");
		s.addStudentToCourse(jerryStudentId,"CS1917");
		s.addStudentToCourse(homerStudentId,"CS1917");
		s.addStudentToCourse(1234u,"CS1917");
	}
    catch( const std::exception & ex )
    {
		std::cerr << ex.what() << std::endl;
	}

	// try to enroll homer twice:
	try
    {
		s.addStudentToCourse(homerStudentId,"CS2911");
		s.addStudentToCourse(homerStudentId,"CS1917");
	}
    catch( const std::exception & ex )
    {
		std::cerr << ex.what() << std::endl;
	}

	// print the roll for a course
	s.printRoll("CS1917");

	// print the timetable for a student
	s.printTimetable(homerStudentId);

	// acquire a locker for homer.
	s.assignLocker(homerStudentId);
	std::cout << std::boolalpha << "Homer has a locker: " << s.hasLocker(homerStudentId) << std::endl;
	std::cout << "Tom has a locker: " << s.hasLocker(tomStudentId) << std::endl;

	// delete a student
	s.expelStudent(tomStudentId);
	s.printRoll("CS1917");

	// delete a course.
	s.cancelCourse("CS1917");
	s.printTimetable(homerStudentId);

	// if we delete homer, what happens to the locker he owns?
}

// ----------------------------------------------------------------
// Some examples of using smart pointers
// ----------------------------------------------------------------

class X
{
    unsigned int x_;
public:
    X(unsigned int x) : x_{x}
    {
        std::cout << "X::X(" << x_ << ")" << std::endl;
    }
    ~X()
        { std::cout << "X::~X(): " << x_ << std::endl; }
    unsigned int getX() const { return x_; }
    void incr() { ++x_; }
    void decr() { --x_; }
};

// In what circumstances should you use these function prototypes.
void f1(std::unique_ptr<X> xptr);
void f2(std::unique_ptr<X>& xptr);
void f3(const std::unique_ptr<X>& xptr);
void f4(const X& x);
void f5(const X* xptr);

// Will only work with rvalue-reference (move semantics). Use it when
// you really want to move the object.
void f1(std::unique_ptr<X> xptr)
{
    std::cout << "f1: X = " << xptr->getX() << std::endl;
    // x2ptr will be destroy on exiting the function

    // We can move the unique_ptr
    auto copyptr = std::move(xptr);
}

// Use this if you want to modify what is being pointed to.
void f2(std::unique_ptr<X>& xptr)
{
    std::cout << "f2: X = " << xptr->getX() << std::endl;

    xptr = support::make_unique<X>(22);
}

// Avoid this usage - it doesn't serve much purpose
void f3(const std::unique_ptr<X>& xptr)
{
    xptr->incr(); // can modify
    std::cout << "f3: X = " << xptr->getX() << std::endl;
    xptr->decr(); // can modify

    // Note can't move the pointer
    //std::unique_ptr<X> copyptr = std::move(xptr);
}

// Always prefer to dereference the unique_ptr if the pointer itself
// won't be touched.
void f4(const X& x)
{
    std::cout << "f4: X = " << x.getX() << std::endl;

    // xptr->incr(); // can't modify object

    // Note can't move the pointer
    //std::unique_ptr<X> copyptr = std::move(xptr);
}

// Use this for more flexibility if there is a possiblity that the
// value might be null. Note: if you need to check for null then there
// is a good chance that the design is faulty.
void f5(const X* xptr)
{
    std::cout << "f5: X = " << xptr->getX() << std::endl;
    // xptr->incr(); // can't modify object
}

void test_unique_ptr()
{
    std::unique_ptr<int> p1(new int);
//     std::unique_ptr<int> p2 = p1;      // Compile error - no copy assigment
    std::unique_ptr<int> p2 = std::move(p1);
   
    std::cout << p1.get() << std::endl;

    auto x1ptr = support::make_unique<X>(1);
    auto x2ptr = support::make_unique<X>(2);
    auto x3ptr = support::make_unique<X>(3);
    auto x4ptr = support::make_unique<X>(4);
    auto x5ptr = support::make_unique<X>(5);
    std::cout << std::endl;

    std::cout << "Calling f1" << std::endl;

    f1(std::move(x1ptr)); // x1ptr is captured.
    std::cout << std::endl;

    std::cout << "Calling f2" << std::endl;
    f2(x2ptr);
    std::cout << std::endl;

    std::cout << "Calling f3" << std::endl;
    f3(x3ptr);
    std::cout << std::endl;

    std::cout << "Calling f4" << std::endl;
    f4(*x4ptr);
    std::cout << std::endl;

    std::cout << "Calling f5" << std::endl;
    f4(*x5ptr.get());
    std::cout << std::endl;

    std::cout << "Called f1-f5" << std::endl;
}


// ----------------------------------------------------------------
// Simple example of when using decltype is appropriate.  New C++11
// means that the return type of a template class can be deduced
// automatically without having to specify an extra template
// parameter.
// ----------------------------------------------------------------

template<class Res, class In1, class In2>
Res multiply1(In1 a, In2 b) { return a*b; }

template<class In1, class In2>
auto multiply2(In1 a, In2 b) -> decltype(a*b) { return a*b; }

void test_decltype()
{
//    auto result1 = multiply1(1,2); // Compiler error - can't deduce return type

    auto m1result1 = multiply1<int>(1,2);
    auto m1result2 = multiply1<float>(1,2.5);
    auto m1result3 = multiply1<int>(1,2.5); // Quietly downcasted

    std::cout << "M1: Result1 = " << m1result1 << std::endl;
    std::cout << "M1: Result2 = " << m1result2 << std::endl;
    std::cout << "M1: Result3 = " << m1result3 << std::endl;
    std::cout << std::endl;

    auto m2result1 = multiply2(1,2);
    auto m2result2 = multiply2(1,2.5);

    std::cout << "M2: Result1 = " << m2result1 << std::endl;
    std::cout << "M2: Result2 = " << m2result2 << std::endl;
}





