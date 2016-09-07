#ifndef SCHOOL_HPP
#define SCHOOL_HPP

#include <string>
#include <vector>
#include <memory>	// for smart pointers
#include <algorithm>
#include <iostream>
#include <exception>
#include <map>

#include "support.hpp"

class School
{
    // forward declarations
    class Course;
	class Student;
    class Locker;

public:

	// Create some lockers.
	School(unsigned int numLockers);

	// create a course object and add it to the list of courses
	bool addCourse(const std::string& courseCode);

	// method to add a new student and return their new student id
	unsigned int addStudent(const std::string& studentName);

	// method to add a student to a course.
	void addStudentToCourse(unsigned int id, const std::string& courseCode);

	// method to print a roll for a course
	void printRoll(const std::string& s) const;

	// method to print a student's timetable.
	void printTimetable(unsigned int id) const;

	// method to transfer ownership of a locker to a student if
	// there are enough lockers available.
	bool assignLocker(unsigned int id);

	// method to test if a student has a locker assigned.
	bool hasLocker(unsigned int id) const;

	// method to remove a student from the school
	// because of shared pointers this is really easy
	void expelStudent(unsigned int id);

	// method to cancel a course at the school
	// again this is really easy with shared ptrs.
	void cancelCourse(const std::string& s);

private:
    // Private data members
	std::map<unsigned int,std::shared_ptr<Student>> students_;
	std::vector<std::unique_ptr<Locker>> lockers_;
	std::vector<std::shared_ptr<Course>> courses_;

	// some private methods:
	// method to find a course object.
	// showcasing a trailing return type, using the type of iterator that courses returns.
	// this is used as trying to determine the type of this iterator is difficult.

	auto findCourse(const std::string& courseCode) const -> decltype(courses_.begin());

// C++11 bug (i.e., missing feature) in libstdc++ for gcc 4.8.x
#ifdef NO_ERASE_CONST_ITERATOR
	auto findCourse(const std::string& courseCode) -> decltype(courses_.begin());
#endif

	// find a student object.
	std::shared_ptr<Student> findStudent(unsigned int id) const;


private:
	// ----------------------------------------------------------------
    // private nested classes
	// ----------------------------------------------------------------

	// ----------------------------------------------------------------
	// Begin: Course (private inner class)

	class Course
    {
	public:
		Course(const std::string &s);

		const std::string& getCourseCode() const;

		// adds a student to the course
		bool addStudent(std::weak_ptr<Student> wp);

		// method to print the students in a course
		void printRoll() const;

	private:
        // Private data members
		std::string courseCode_;
		std::vector<std::weak_ptr<Student>> studentsInCourse_;
	};

	// End: Course Class
	// ----------------------------------------------------------------
	// Begin: Locker (private inner class)

	class Locker
    {
	public:
		Locker(unsigned int id);

        unsigned int getLockerId() const;

	private:
        // Private data members
		const unsigned int lockerId;
	};

	// End: Locker Class
	// ----------------------------------------------------------------
	// Begin: Student (private inner class)

	class Student
    {
	public:
		Student(const std::string &s);

		unsigned int getStudentNumber() const;

		std::string getName() const;

		// method to add a course that this student is taking.
		bool addCourse(std::weak_ptr<Course> wp);

		// method to print a student's timetable
		void printTimetable() const;

		// method to take ownership of a locker object
		void assignLocker(std::unique_ptr<Locker> locker);

		// returns true if the student has ownership over a locker object.
		bool hasLocker() const;
	private:

		std::unique_ptr<Locker> assignedLocker_;
		std::string name_;
		unsigned int studentNumber_;
		std::vector<std::weak_ptr<Course>> coursesEnrolledIn_;
		static unsigned int nextStudentNumber_;
	};

	// End: Student Class
	// ----------------------------------------------------------------
	// Begin: rest of School class

};




#endif // SCHOOL_HPP
