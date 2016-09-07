#include <sstream>
#include "school.hpp"


//--------------------------------------------------------------------------
// Implementation of class School
//--------------------------------------------------------------------------

// Create some lockers.
School::School(unsigned int numLockers)
{
    for (unsigned int i = 0; i < numLockers; ++i)
    {
        // C++14 style
        //lockers.push_back(std::make_unique<Locker>(i));
        // C++11 style
        // std::unique_ptr<Locker> lPtr (new Locker{i});
        // lockers_.push_back(std::move(lPtr));

        lockers_.push_back(support::make_unique<Locker>(i));
    }
}

// method to add a new student and return their new student id
unsigned int School::addStudent(const std::string& studentName)
{
    auto newStudent = std::make_shared<Student>(studentName);
    students_.insert({newStudent->getStudentNumber(),newStudent});
    return newStudent->getStudentNumber();
}

// method to print a roll for a course
void School::printRoll(const std::string& s) const
{
    auto courseObject = findCourse(s);
    (*courseObject)->printRoll();
}

// method to print a student's timetable.
void School::printTimetable(unsigned int id) const
{
    auto studentObject = findStudent(id);
    studentObject->printTimetable();
}

// method to test if a student has a locker assigned.
bool School::hasLocker(unsigned int id) const
{
    auto studentObject = findStudent(id);
    return studentObject->hasLocker();
}

// method to remove a student from the school
// because of shared pointers this is really easy
void School::expelStudent(unsigned int id)
{
    students_.erase(id);
}

// method to cancel a course at the school
// again this is really easy with shared ptrs.
void School::cancelCourse(const std::string& s)
{
    auto courseObject = findCourse(s);
    courses_.erase(courseObject);
}

// private method to find a student object.
std::shared_ptr<School::Student> School::findStudent(unsigned int id) const
{
    auto studentObject = students_.find(id);
    if (studentObject == students_.end())
    {
        throw std::runtime_error("Can't find student " + std::to_string(id));
    }
    return studentObject->second;
}

// create a course object and add it to the list of courses
// return false if the course already exists
bool School::addCourse(const std::string& courseCode)
{
	// TODO: double check that the course doesn't already exist.
	// create a new course object

    // NOTE: need to use find_if and a lambda because we are not
    // trying to find a match to the pointer but rather the pointed
    // object. Note: a std::map may be a better choice for data
    // structure. efficient.

    auto result = std::find_if(courses_.begin(), courses_.end(),
                               [&courseCode](std::shared_ptr<Course> c)
                               {
                                   if (c->getCourseCode() == courseCode) return true;
                                   return false;
                               });
    if (result != courses_.end()) return false;

	courses_.push_back(std::make_shared<Course>(courseCode));
	return true;
}

// method to add a student to a course.
void School::addStudentToCourse(unsigned int id, const std::string& courseCode)
{
	auto courseObject = findCourse(courseCode);	// find the course object
	// find student
	auto studentObject = findStudent(id);

	//TODO: try to add the student to the course.
	// if the student can't be added to the course, e.g. they are already enrolled
	// then return false.
    if (!(*courseObject)->addStudent(studentObject))
    {
        std::stringstream ss;
        ss << "Student " << id << " is already enrolled in course " << courseCode;
        throw std::runtime_error(ss.str());
    }

	// add the course object to a student's object
	studentObject->addCourse(*courseObject);
}

// method to transfer ownership of a locker to a student if
// there are enough lockers available.
bool School::assignLocker(unsigned int id)
{
	auto studentObject = findStudent(id);
	if ( lockers_.size() > 0u) {
		// TODO: assign the locker to the student
        studentObject->assignLocker(std::move(lockers_.back()));

        // NOTE: at this point the last element of lockers_ is
        // technically undefined (but typically nullptr).

		lockers_.pop_back();
		return true;
	}
	return false;
}

// method to find a course object.
// showcasing a trailing return type, using the type of iterator that courses returns.
// this is used as trying to determine the type of this iterator is difficult.
auto School::findCourse(const std::string& courseCode) const -> decltype(courses_.begin())
{
	// find course.
    // Can't do this
    //    std::find(courses_.begin(),courses_.end(),value);

	auto courseObject = std::find_if(courses_.begin(),courses_.end(),
                                     [&courseCode] (std::shared_ptr<Course> c)
                                     {
//                                         if (c->getCourseCode() == courseCode)
                                         if (c->getCourseCode().compare(courseCode) == 0)
                                             return true;
                                         return false;
                                     });
	if (courseObject == courses_.end())
        throw std::runtime_error("Can't find course " + courseCode);
	return courseObject;
}

#ifdef NO_ERASE_CONST_ITERATOR
auto School::findCourse(const std::string& courseCode) -> decltype(courses_.begin())
{
	// find course.
	auto courseObject = std::find_if(courses_.begin(),courses_.end(),
                                     [&courseCode] (std::shared_ptr<Course> c)
                                     {
                                         if (c->getCourseCode().compare(courseCode) == 0)
                                             return true;
                                         return false;
                                     });
	if (courseObject == courses_.end())
        throw std::runtime_error("Can't find course " + courseCode);

	return courseObject;
}
#endif

//--------------------------------------------------------------------------
// Implementation of class School::Course
//--------------------------------------------------------------------------



School::Course::Course(const std::string &s) : courseCode_{s} {}

const std::string& School::Course::getCourseCode() const
{
    return courseCode_;
}


// adds a student to the course
// return false if the student is already enrolled in the course
bool School::Course::addStudent(std::weak_ptr<Student> wp)
{
	// check that the student isn't already in the course
	auto result = std::find_if(studentsInCourse_.begin(),
                               studentsInCourse_.end(),
                               [wp] (std::weak_ptr<Student> s)
                               {
                                   if ( wp.lock() == s.lock() ) return true;
                                   return false;
                               });

	if (result != studentsInCourse_.end()) return false;
	// add the student to the course.
	studentsInCourse_.push_back(wp);
	return true;
}

// method to print the students in a course
void School::Course::printRoll() const
{
	std::cout << courseCode_ << " Roll" << std::endl;
	for (auto wp : studentsInCourse_)
    {
		// TODO: print the names of the students in the course
       auto sp = wp.lock(); // Converts to nullptr
        if (sp != nullptr)
            std::cout << sp->getName() << std::endl;
	}
}


//-----------------------------------------------------------------
// Implementation for School::Locker
//-----------------------------------------------------------------

School::Locker::Locker(unsigned int id) : lockerId{id} {}

unsigned int School::Locker::getLockerId() const
{
    return lockerId;
}

//--------------------------------------------------------------------------
// Implementation of class School::Student
//--------------------------------------------------------------------------

School::Student::Student(const std::string &s) :
    name_{s}, studentNumber_{++nextStudentNumber_} {}
unsigned int School::Student::getStudentNumber() const
{
return studentNumber_;
}

std::string School::Student::getName() const
{
    return name_;
}

// method to take ownership of a locker object
void School::Student::assignLocker(std::unique_ptr<School::Locker> locker)
{
    assignedLocker_ = std::move(locker);
}

// returns true if the student has ownership over a locker object.
bool School::Student::hasLocker() const
{
    return (assignedLocker_ != nullptr);
}

// init the student number counter
unsigned int School::Student::nextStudentNumber_ = 9312u;


// method to add a course that this student is taking.
// Pre-Condition: The student has already been enrolled in the course.
// Pre-Condition: The student hasn't already had this course added to their timetable
bool School::Student::addCourse(std::weak_ptr<Course> wp)
{
	coursesEnrolledIn_.push_back(wp);
	return true;
}

// method to print a student's timetable
void School::Student::printTimetable() const
{
	std::cout << "Timetable for " << name_ << " " << studentNumber_ << std::endl;
	for (auto c : coursesEnrolledIn_)
    {
		auto sp = c.lock();	// convert the weak_ptr to a shared_ptr
		if (sp != nullptr)
        {	// if the convert was successful then print the course
			std::cout << sp->getCourseCode() << std::endl;
		}
	}
}

