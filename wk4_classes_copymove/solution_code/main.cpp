#include <iostream>
#include <vector>
#include <array>
#include "car.hpp"

void main_tute3();
void test_cars();
void vexing_parse_stuff();


int main() {
   main_tute3();

//    test_cars();

//    vexing_parse_stuff();
}

/********************************************************************
 * The main tutorial question.
 *
 * Note: the use of std::move() in this context is not how you would
 * normally it. It would normally be called in situations where the
 * object is temporary, such as in a move constructor or a swap
 * function. After a move constructor/operator action the state of the
 * moved from object is "unspecified but valid". So assigning to
 * this object is fine but querying the state will be ill-defined.
 ********************************************************************/

void main_tute3()
{
	Car one;
	Car two{"Toyota",5};

	std::cout << Car::getObjectCount() << std::endl;

	Car* three = new Car{};
	std::cout << Car::getObjectCount() << std::endl;
	delete three;
	std::cout << Car::getObjectCount() << std::endl;

	Car four{two};
	std::cout << Car::getObjectCount() << std::endl;

	Car five = std::move(one);

	std::cout << Car::getObjectCount() << std::endl;

	Car six{std::move(two)};
	std::cout << Car::getObjectCount() << std::endl;

	four = six;
	std::cout << Car::getObjectCount() << std::endl;

	five = std::move(six);
	std::cout << Car::getObjectCount() << std::endl;

}



/********************************************************************
 * Test the difference in performance between having and not having
 * move semantics.
 *
 * Note: on make_cars(). Because the return value is really simple the
 * compiler (both gcc and clang) will perform return value optimisation
 ********************************************************************/

Cars make_cars()
{
    Cars cars{Car{"Toyota", 4}, Car{"Hyundai",3}};
    return cars;
}

void test_cars()
{
    std::cout << "Creating cars" << std::endl;

    // Note: if the compiler performs return value optimisation the
    // following will do copying of the object. If it is disable then
    // the call will perform at least one call to Cars move constructor.
    Cars cars1 = make_cars();

    std::cout << std::endl;
    std::cout << "Moving cars1 to cars2 should call move constructor" << std::endl;

    Cars cars2{std::move(cars1)};
    std::cout << std::endl;
}


/********************************************************************
 * Most vexing parse.
 ********************************************************************/


int some_function(){ return 44; }

void vexing_parse_stuff()
{
    int test1();   // WARNING: this is a function prototype

    std::cout << "Calling test1 function: " << test1() << std::endl;

    // Note: most-vexing parse problem is not the same as c-style
    // function pointers.
    int (*test2)(void);
    test2 = some_function;
    std::cout << "Calling test2 function: " << test2() << std::endl;

    test2 = test1;
    std::cout << "Calling test2 function: " << test2() << std::endl;

}

int test1() { return 33; }
