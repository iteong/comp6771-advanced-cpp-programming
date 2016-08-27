// those with # is processed by compiler first
// header guards
#ifndef CAR_HPP
#define CAR_HPP

#include <string>
#include <iostream>


class Car {

public:
	Car(); // empty constructor
	Car(const std::string& manufacturer, unsigned int numSeats);
	~Car(); // destructor

	static unsigned int get_count(); // get count of objects (cars) created, declare static here but don't need in .cpp file (or else double static definition)
	std::string get_man() const; // get manufacturer name

	Car(const Car& car); // copy constructor

private:
    std::string manufacturer_;
    unsigned int numSeats_;

    static unsigned int count_; // static counter: every car has the same count, it's a global variable that only belongs to this class


};            
                


#endif
