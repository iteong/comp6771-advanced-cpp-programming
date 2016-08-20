// Car.cpp
// Callum Howard, 2016

#include "Car.hpp"

#include <cstdlib>	
#include <algorithm> 
#include <iostream>



// Create a constructor for the car that takes in the manufacturer name (e.g. Toyota) and the number of seats.
// Ensure that your constructor uses a member initializer list and uniform initialisation. 
Car::Car(std::string manufacturer, unsigned int numSeats) 
        : manufacturer_{manufacturer}, numSeats_{numSeats} {

            ++ count_; // creating a static data member to keep count of number of car objects created

        } // it doesn't have semi-colon here coz semi-colon needs to be at end of class

// Create a default constructor that delegates to the previous constructor using the values of "unknown" and 4
Car::Car() : Car{"unknown", 4} {} // delegator constructor, calls the above contructor with its initializer list
// no need to put increment of count into delegate constructor coz it calls the constructor that has it

// Create const member functions to get the manufacturer and number of seats.
// What does it mean for a class or function to be const correct?


// Create a static data member to keep count of the number of car objects created.
// Modify your constructors to ensure that the count increases when a new object is created.


// Create a static function to return the object count.


// Create a destructor that decreases the object count when an object is destroyed
Car::~Car() {
    --count_;
}

// getter, need to specify type = count is static so getter needs to be static too, but it is already done in Car.hpp for the class Car so no need do here
unsigned int Car::get_count() {
    return count_;
}

// std::string is not const
std::string Car::get_man() const { // non-const methods like this can still call const object like manufacture
    // numSeats_ = 3; // won't be executed coz of the const, cannot modify the variable
    return manufacturer_;
}
// all getters should be return only, so put const into this getter so any code within {} cannot modify the variable inside



// Create a copy constructor, be sure to increase the object count.
// no type coz it is a copy constructor
Car::Car(const Car& car) : 
    manufacturer_{car.manufacturer_}, numSeats_{car.numSeats_} {
    ++count_;
}

// Create a move constructor, should you increase the object count too?

// Create a copy assignment operator, should the object count change?

// Create a move assignment operator, should the object count change?


int main() {

    auto c = Car{};

    return 0;

}