#include <string>
#include <vector>	
#include <memory>	// for smart pointers
#include <algorithm>
#include <iostream>
#include <exception>
#include <map>

class School {
private: // private above here (not usual) coz got inner classes
	class Student;	// forward declaration of a student class

	// ----------------------------------------------------------------
	// Begin: Course (private inner class)
	class Course {
	public:
		Course(const std::string &s) : courseCode{s} {}
		const std::string& getCourseCode() const { return courseCode; }
		
		// adds a student to the course
		bool addStudent(std::weak_ptr<Student> wp);
		
		// method to print the students in a course
		void printRoll() const;
		
	private:
		std::string courseCode;
		std::vector<std::weak_ptr<Student>> studentsInCourse;
	};
	
	// End: Course Class
	// ----------------------------------------------------------------
	// Begin: Locker (private inner class)
	
	class Locker {
	public:
		Locker(unsigned int id) : lockerId{id} {}
	private:
		const unsigned int lockerId;
	};
	
	// End: Locker Class
	// ----------------------------------------------------------------
	// Begin: Student (private inner class)
	
	class Student {
	public:
		Student(const std::string &s) : name{s}, studentNumber{++nextStudentNumber} {}
		unsigned int getStudentNumber() const { return studentNumber; }
		std::string getName() const { return name; }
		
		// method to add a course that this student is taking. 
		bool addCourse(std::weak_ptr<Course> wp);
		
		// method to print a student's timetable
		void printTimetable() const;
		
		// method to take ownership of a locker object
		void assignLocker(std::unique_ptr<Locker> locker) {
			assignedLocker = std::move(locker);
		}
		
		// returns true if the student has ownership over a locker object.
		bool hasLocker() const { return (assignedLocker != nullptr); }
	private:
		std::unique_ptr<Locker> assignedLocker;
		std::string name;
		unsigned int studentNumber;
		std::vector<std::weak_ptr<Course>> coursesEnrolledIn;
		
		static unsigned int nextStudentNumber;
	};
	
	// End: Student Class
	// ----------------------------------------------------------------
	// Begin: rest of School class

public: // public methods above and private below

	// Create some lockers. 
	School(unsigned int numLockers) {
		for (unsigned int i = 0; i < numLockers; ++i) {
			// C++14 style
			//lockers.push_back(std::make_unique<Locker>(i));
			// C++11 style
			std::unique_ptr<Locker> lPtr (new Locker{i});
			lockers.push_back(std::move(lPtr));
		}
	}

	// create a course object and add it to the list of courses
	bool addCourse(const std::string& courseCode);
	
	// method to add a new student and return their new student id
	unsigned int addStudent(const std::string& studentName) {
		auto newStudent = std::make_shared<Student>(studentName);
		students.insert({newStudent->getStudentNumber(),newStudent});
		return newStudent->getStudentNumber();
	}
	
	// method to add a student to a course. 
	void addStudentToCourse(unsigned int id, const std::string& courseCode);
	
	// method to print a roll for a course
	void printRoll(const std::string& s) const {
		auto courseObject = findCourse(s);
		(*courseObject)->printRoll();
	}
	
	// method to print a student's timetable.
	void printTimetable(unsigned int id) const {
		auto studentObject = findStudent(id);
		studentObject->printTimetable();
	}
	
	// method to transfer ownership of a locker to a student if 
	// there are enough lockers available. 
	bool assignLocker(unsigned int id);
	
	// method to test if a student has a locker assigned.
	bool hasLocker(unsigned int id) const {
		auto studentObject = findStudent(id);
		return studentObject->hasLocker();
	}
	
	// method to remove a student from the school
	// because of shared pointers this is really easy
	void expelStudent(unsigned int id) {
		students.erase(id);
	}
	
	// method to cancel a course at the school
	// again this is really easy with shared ptrs. 
	void cancelCourse(const std::string& s) {
		auto courseObject = findCourse(s);
		courses.erase(courseObject);
	}
private: // member variables
	std::vector<std::shared_ptr<Course>> courses;
	std::map<unsigned int,std::shared_ptr<Student>> students; // mapping student ID number to student objects
	std::vector<std::unique_ptr<Locker>> lockers;
	
	// some private methods:
	// method to find a course object. 
	// showcasing a trailing return type, using the type of iterator that courses returns. 
	// this is used as trying to determine the type of this iterator is difficult. 
	auto findCourse(const std::string& courseCode) const -> decltype(courses.begin());
	
	// find a student object. 
	std::shared_ptr<Student> findStudent(unsigned int id) const {
		auto studentObject = students.find(id);
		if (studentObject == students.end()) throw std::runtime_error("Can't find student " + std::to_string(id));
		return studentObject->second;
	}
};
