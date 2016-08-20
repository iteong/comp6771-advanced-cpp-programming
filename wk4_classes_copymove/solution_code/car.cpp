#include <iostream>
#include "car.hpp"

/*************************************************************************
 * Implementation of Car
 **************************************************************************/

// Note: no need to increment the static count here as the delegated
// constructor will do it.
Car::Car() : Car{"unknown", 4} { }

Car::Car(const std::string& manufacturer, unsigned int nseats) :
    manufacturer_{manufacturer}, nseats_{nseats}
{
//    std::cout << "Car constructor" << std::endl;
    // manufacturer_ = manufacturer; // BAD
    ++ncars_;
}


Car::Car(const Car& car) :
    manufacturer_{car.manufacturer_}, nseats_{car.nseats_}
{
    std::cout << "Car copy constructor" << std::endl;
    ++ncars_;
}

Car::Car(Car&& car) :
    manufacturer_{std::move(car.manufacturer_)}, nseats_{car.nseats_}
{
// Note: if manufacturer was declared as some pointer object
// (eg. std::string*) then special care would need to be taken to null
// the pointer.
//    car.manufacturer_ = nullptr;
//
    std::cout << "Car move constructor" << std::endl;
    ++ncars_;
}

Car::~Car()
{
//    std::cout << "Car destructor" << std::endl;
    --ncars_;
}

Car& Car::operator=(const Car& car)
{
    std::cout << "Car copy operator" << std::endl;

    manufacturer_ = car.manufacturer_;
    nseats_ = car.nseats_;
    return *this;
}

Car& Car::operator=(Car&& car)
{
    std::cout << "Car move operator" << std::endl;
    manufacturer_ = std::move(car.manufacturer_);
    nseats_ = car.nseats_;
    return *this;
}

unsigned int Car::ncars_ = 0;

// NOTE: I think the standard requires the following line but gcc
// doesn't seem to need it because it has been inlined.
const int Car::classid;

const std::string Car::classname= "CAR";


const std::string& Car::getManufacturer() const { return manufacturer_; }

unsigned int Car::getNumSeats() const { return nseats_; }

unsigned int Car::getObjectCount() { return ncars_; }


/*************************************************************************
 * Implementation of Cars
 **************************************************************************/

Cars::Cars(const Car& car1, const Car& car2) : car1_{car1}, car2_{car2} { }

Cars::Cars(const Cars& cars) : car1_{cars.car1_}, car2_{cars.car2_}
{
    std::cout << "Cars copy constructor" << std::endl;
}

/*
Cars::Cars(Cars&& cars) :
    car1_{std::move(cars.car1_)},  car2_{std::move(cars.car2_)}
{
    std::cout << "Good Cars move constructor" << std::endl;

}
*/

// With parameter (const Car&&) this will do the wrong thing and call
// the Car copy constructor for car1_ and car2_. The reason is that
// const means that the cars object can't be modified.

Cars::Cars(const Cars&& cars) :
    car1_{std::move(cars.car1_)},  car2_{std::move(cars.car2_)}
{
    std::cout << "Bad Cars move constructor" << std::endl;

}


Cars::~Cars()
{
//    std::cout << "Cars destructor" << std::endl;
}


Cars& Cars::operator=(const Cars& cars)
{
    std::cout << "Cars copy operator" << std::endl;

    car1_ = cars.car1_;
    car2_ = cars.car2_;
    return *this;
}

Cars& Cars::operator=(Cars&& cars)
{
    std::cout << "Cars move operator" << std::endl;

    car1_ = std::move(cars.car1_);
    car2_ = std::move(cars.car2_);
    return *this;
}
