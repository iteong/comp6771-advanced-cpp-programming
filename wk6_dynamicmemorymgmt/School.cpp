#include "School.hpp"
#include "sstream" // for add student to course

// init the student number counter
unsigned int School::Student::nextStudentNumber = 9312u;

// adds a student to the course
// return false if the student is already enrolled in the course
bool School::Course::addStudent(std::weak_ptr<Student> wp) { 
	// check that the student isn't already in the course
	auto result = std::find_if(studentsInCourse.begin(),studentsInCourse.end(), [wp] (std::weak_ptr<Student> s) {
		if ( wp.lock() == s.lock() ) return true;
		return false;
	});
	if (result != studentsInCourse.end()) return false;
	// add the student to the course. 
	studentsInCourse.push_back(wp); 
	return true;
}

// method to print the students in a course
void School::Course::printRoll() const {
	std::cout << courseCode << " Roll" << std::endl;
	for (auto wp : studentsInCourse) { // weak pointer
		// TODO: print the names of the students in the course

		// shared pointer sp equals to wp.lock, checks if object that weak pointer is pointing to is expired, if yes return shared_ptr for that object, if not, return nullptr
		if (auto sp != wp.lock()) { // wp.lock() will return null pointer if the object that weak pointer points to don't exist
			std::cout << sp->getName() << std::endl; // print out if object expired
		}

	}
}

// method to add a course that this student is taking. 
// Pre-Condition: The student has already been enrolled in the course. 
// Pre-Condition: The student hasn't already had this course added to their timetable
bool School::Student::addCourse(std::weak_ptr<Course> wp) { 
	coursesEnrolledIn.push_back(wp);
	return true;
}

// method to print a student's timetable
void School::Student::printTimetable() const {
	std::cout << "Timetable for " << name << " " << studentNumber << std::endl;
	for (auto c : coursesEnrolledIn) {
		auto sp = c.lock();	// convert the weak_ptr to a shared_ptr
		if (sp != nullptr) {	// if the convert was successful then print the course
			std::cout << sp->getCourseCode() << std::endl;
		}
	}
}

// create a course object and add it to the list of courses
// return false if the course already exists
bool School::addCourse(const std::string& courseCode) {
	// TODO: double check that the course doesn't already exist.
	// create a new course object

	auto result = std::find_if(courses.begin(),courses.end(), // find_if: if lambda function returns true, then return iterator to that element
		[&courseCode] (std::shared_ptr<Course> c) { // defining a function (using lambda function) in the argument parameter of find_if => takes []coursecode and find it in context and ports it to coursecode in line below (the function brackets start from find_if till after return false)
		// (auto c) can replace the (std::shared_ptr<Course> c) and it will still work

		// body of lamda function, need to compare objects
		if (c->getCourseCode() == courseCode) return true;
                                   return false;
                               });

		//if (c->getCourseCode().compare(courseCode) == 0) return true;
	if (result != courses.end()) {return false;}


	courses.push_back(std::make_shared<Course>(courseCode));
	return true;
}

// method to add a student to a course. 
void School::addStudentToCourse(unsigned int id, const std::string& courseCode) { // student ID and course code
	auto courseObject = findCourse(courseCode);	// find the course object
	// find student
	auto studentObject = findStudent(id);
	
	//TODO: try to add the student to the course. => from header file, there is a method called addStudent (which returns false if the method call fails)
	// if the student can't be added to the course, e.g. they are already enrolled
	// then return false.
	if (!(*courseObject)->addStudent(studentObject)) { // add student object to course object (which is an iterator that is a pointer) which needs to be dereferenced to call the method successfully
		// need * and -> which is dereferencing twice coz the student object is a shared pointer to an iterator (vector type)
		// student couldn't be added
		std::stringstream ss;
		ss << "Student is already enrolled in course";
		throw std::runtime_error(ss.str()); // throw similar to return, standard command
	}
	

	// add the course object to a student's object
	studentObject->addCourse(*courseObject);
}

// method to transfer ownership of a locker to a student if 
// there are enough lockers available. 
bool School::assignLocker(unsigned int id) {
	auto studentObject = findStudent(id);
	if (not lockers.empty()) { // lockers is a vector, can check if it is empty instead of using size
		// TODO: assign the locker to the student (the default one in hpp file is locker assigned to school, not to student, so use that assign method to assign to student instead)
		// since the pointer is a unique pointer cannot have multiple pointers to it, use std::move to move resources out (cannot use std::copy)
		studentObject->assignLocker(std::move(lockers.back()));
		lockers.pop_back();
		return true;
	}
	return false;
}

// method to find a course object. 
// showcasing a trailing return type, using the type of iterator that courses returns. 
// this is used as trying to determine the type of this iterator is difficult.
// need decltype for auto => why use? If we use decltype, and change shared pointer to weak pointers, vector to list, will still work (makes code more flexible) => only main cannot use decltype = has to be int!
auto School::findCourse(const std::string& courseCode) const 
	-> decltype(courses.begin()) { // declaring function no needs -> arrow is declaration of decltype, which will look at courses.begin() to determine type for auto
	// find course. 
	// find_if: given iterator begin and last, with given value, find it in the last object => if find value goes to that value, if not, go to end, can also be formulaic inside the value
	auto courseObject = std::find_if(courses.begin(),courses.end(), // find_if: if lambda function returns true, then return iterator to that element
		[&courseCode] (std::shared_ptr<Course> c) { // defining a function (using lambda function) in the argument parameter of find_if => takes []coursecode and find it in context and ports it to coursecode in line below (the function brackets start from find_if till after return false)
		// (auto c) can replace the (std::shared_ptr<Course> c) and it will still work
		if (c->getCourseCode().compare(courseCode) == 0) return true;
		return false;
	});
	if (courseObject == courses.end()) throw std::runtime_error("Can't find course " + courseCode);
	return courseObject;
}


