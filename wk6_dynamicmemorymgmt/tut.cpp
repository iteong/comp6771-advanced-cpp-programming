#include "School.hpp"

int main() {

	School s(100u);
	s.addCourse("CS1917");
	s.addCourse("CS2911");
	s.addCourse("CS6771");
	
	if (s.addCourse("CS1917") == false) {
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
	try {
		s.addStudentToCourse(tomStudentId,"CS1917");
		s.addStudentToCourse(jerryStudentId,"CS1917");
		s.addStudentToCourse(homerStudentId,"CS1917");
		s.addStudentToCourse(1234u,"CS1917");
	} catch( const std::exception & ex ) {
		std::cerr << ex.what() << std::endl;
	}

	// try to enroll homer twice:
	try {
		s.addStudentToCourse(homerStudentId,"CS2911");
		s.addStudentToCourse(homerStudentId,"CS1917");
	} catch( const std::exception & ex ) {
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
