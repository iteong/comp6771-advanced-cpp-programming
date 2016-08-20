#ifndef CAR_H
#define CAR_H

/********************************************************************
 *
 * Notes on style:
 *
 * 1) Many modern style guides prefer to have the public stuff at the
 *    top of the header file and private stuff at the end.
 *
 * 2) One common technique to distinguish member variables from function
 *    parameters is to add a "_" to the end of member variables. Also
 *    helps with resolving potential name conflicts.
 *
 * 3) If you want self-generating documentation then doxygen is the
 *    de-facto standard for C++. http://www.stack.nl/~dimitri/doxygen/
 *
 ********************************************************************/

#include <string>
#include <vector>

/********************************************************************
 *
 ********************************************************************/

class Car
{
public:
    Car();
    Car(const Car& car);
    Car(Car&& car);
    Car(const std::string& manufacturer, unsigned int nseats);
    ~Car();

    Car& operator=(const Car& car);


    Car& operator=(Car&& car);

    const std::string& getManufacturer() const;
    unsigned int getNumSeats() const;

    // Note: static member function cannot be declared const because
    // it doesn't have a this pointer.
    static unsigned int getObjectCount();
private:
	std::string manufacturer_;
	unsigned int nseats_;

    static unsigned int ncars_;

    // For interest
    static const int classid = 1;
    static const std::string classname; // Non-integral so no inline initialise
};



/********************************************************************
 * Code to highlight the problem of declaring move
 * constructor/assignment operator parameter as const.
 ********************************************************************/

class Cars
{
public:
    Cars(const Car& car1, const Car& car2);
    Cars(const Cars& cars);

    Cars(const Cars&& cars);  // Bad
    //    Cars(Cars&& cars);  // Good

    ~Cars();

    Cars& operator=(const Cars& cars);
    Cars& operator=(Cars&& cars);

private:
    Car car1_;
    Car car2_;
};

#endif // CAR_H
