#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include "RegistrationManager.h"
using namespace std;

RegistrationManager Manager;

//input helpers
string StudentIDInput() {
	string str;
	getline(cin, str);
	while (!Student::ValidID(str)) {
		cout << "Invalid input, re-enter again [student ID]: ";
		getline(cin, str);
	}
	return str;
}

string StudentNameInput() {
	string str;
	getline(cin, str);
	while (str.size() < StudentName_Min || str.size() > StudentName_Max) {
		cout << "Invalid input, re-enter again [student name]: ";
		getline(cin, str);
	}
	return str;
}

int StudentYearInput() {
	int number;
	string str;
	getline(cin, str);
	number = atoi(str.c_str());
	while (number < 1 || number > 3) {
		cout << "Invalid input re-enter again [student year]: ";
		getline(cin, str);
		number = atoi(str.c_str());
	}
	return number;
}

int StudentGenderInput() {
	string str;
	getline(cin, str);
	while (str != "M" && str != "m" && str != "F" && str != "f") {
		cout << "Invalid inputm re-enter again [student gender]: ";
		getline(cin, str);
	}
	if (str == "M" || str == "m") {
		return Male;
	}
	else {
		return Female;
	}
}

string CourseCodeInput() {
	string str;
	getline(cin, str);
	while (!Course::ValidCode(str)) {
		cout << "Invalid input, re-enter again [course code]: ";
		getline(cin, str);
	}
	return str;
}

string CourseNameInput() {
	string str;
	getline(cin, str);
	while (str.size() < CourseName_Min || str.size() > CourseName_Max) {
		cout << "Invalid Input, re-enter again [course name]: ";
		getline(cin, str);
	}
	return str;
}

int CourseCreditsInput() {
	string str;
	int number;
	getline(cin, str);
	number = atoi(str.c_str());
	while (number < Credit_Min || number > Credit_Max) {
		cout << "Invalid input, re-enter again [course credit]: ";
		getline(cin, str);
		number = atoi(str.c_str());
	}
	return number;
}

int ExamMarkInput() {
	string str;
	int number;
	getline(cin, str);
	number = atoi(str.c_str());
	while (number < ExamMark_Min || number > ExamMark_Max) {
		cout << "Invalid input, re-enter again [exam mark]: ";
		getline(cin, str);
		number = atoi(str.c_str());
	}
	return number;
}


void end() {
	string str;
	cout << "Hit ENTER to continue..." << endl;
	getline(cin, str);
	return;
}

//menu functions
void StudentMenu(){
	int option;
	string input;
	system("clear");

	cout << "HKUST Course Registration System (Student Menu)" << endl;
	cout << "------------------------------------------------" << endl << endl;
	cout << "1. Insert a new student" << endl;
	cout << "2. Modify the name, year, or gender of an existing student" << endl;
	cout << "3. Delete an existing student" << endl;
	cout << "4. Query an existing student" << endl;
	cout << "5. Back to the main menu" << endl;
	cout << "Enter your choice (1-5): ";

	getline(cin, input);
	option = atoi(input.c_str());
	while (option > 6 || option < 1) {
		cout << "Invalid input, re-enter again (1-5): ";
		getline(cin, input);
		option = atoi(input.c_str());
	}

	if (option == 1) {
		Student student;

		cout << "Enter the student ID: ";
		student.setStudentID(StudentIDInput());

		cout << "Enter the student name: ";
		student.setStudentName(StudentNameInput());

		cout << "Enter the student year [1-3]: ";
		student.setYear(StudentYearInput());

		cout << "Enter the student gender [M,F]: ";
		student.setGender(StudentGenderInput());
		
		Manager.add(student);
		
		cout << "Creation of student record successful" << endl << endl;
		/*
		if (stu.isValid() && Manager.add(stu) == 0) {
			cout << "Creation of student record successful";
		}
		else {
			cout << "Creation of student record fail";
		}
		*/
		end();
		return;
	}
	else if (option == 2) {
		
		string str;
		cout << "Enter the student ID: ";
		Student* stuPtr = Manager.queryStudent(StudentIDInput());

		if (stuPtr == NULL) {
			cout << "Student not exist" << endl << endl;

		}
		else {
			cout << "Enter the student name [" << stuPtr->getStudentName() << "]: ";
			stuPtr->setStudentName(StudentNameInput());

			cout << "Enter the student year[" << stuPtr->getStudentName() << "]: ";
			stuPtr->setYear(StudentYearInput());

			string gender;
			if (stuPtr->getGender() == Male) { gender = "M"; }
			else { gender = "F"; }
			cout << "Enter the student gender [" << gender << "]: ";
			stuPtr->setGender(StudentGenderInput());

			cout << "Modification of student record successful" << endl << endl;
		}

		end();
		return;
	}
	else if (option == 3) {
		int result;
		cout << "Enter the student ID: ";
		result = Manager.deleteStudent(StudentIDInput());
		
		if (result == 0) {
			cout << "Deletion of student record successful" << endl << endl;
		}
		else if (result < 0) {
			cout << "Student not exist" << endl << endl;
		}
		end();
		return;
	}
	else if (option == 4) {
		Student* stuPtr;
		cout << "Enter the student ID: ";
		stuPtr = Manager.queryStudent(StudentIDInput());
		if (stuPtr == NULL) {
			cout << "Student not exist" << endl << endl;
		}
		else {
			cout << endl;
			stuPtr->print();
			cout << endl;
		}


		end();
		return;
	}
	else if (option == 5) {
		return;
	}
}

void CourseMenu(){
	int option;
	string input;
	system("clear");

	cout << "HKUST Course Registration System (Course Menu)" << endl;
	cout << "------------------------------------------------" << endl << endl;
	cout << "1. Insert a new course" << endl;
	cout << "2. Modify the name or credit of an existing course" << endl;
	cout << "3. Delete an existing course" << endl;
	cout << "4. Query an existing course" << endl;
	cout << "5. Back to the main menu" << endl;
	cout << "Enter your choice (1-5): ";

	getline(cin, input);
	option = atoi(input.c_str());
	while (option > 6 || option < 1) {
		cout << "Invalid input, re-enter again (1-5): ";
		getline(cin, input);
		option = atoi(input.c_str());
	}

	if (option == 1) {
		Course course;

		cout << "Enter the course code: ";
		course.setCourseCode(CourseCodeInput());

		cout << "Enter the course name: ";
		course.setCourseName(CourseNameInput());

		cout << "Enter the course credits [0-5]: ";
		course.setCredit(CourseCreditsInput());
		cout << "Creation of course record successful" << endl << endl;

		Manager.add(course);
		/*
		if (cou.isValid() && rm.add(cou) == 0) {
			cout << "Creation of course record successful" << endl << endl;
		}
		else {
			cout << "Creation of course record fail" << endl << endl;
		}*/

		end();
		return;
	}
	else if (option == 2) {
		Course* couPtr;
		cout << "Enter the course code: ";
		couPtr = Manager.queryCourse(CourseCodeInput());

		if (couPtr == NULL) {
			cout << "Course not exist" << endl << endl;
		}
		else {
			cout << "Enter the course name[" << couPtr->getCourseName() << "]: ";
			couPtr->setCourseName(CourseNameInput());

			cout << "Enter the course credit[" << couPtr->getCredit() << "]: ";
			couPtr->setCredit(CourseCreditsInput());

			cout << "Modification of course record successful" << endl << endl;
		}
		end();
		return;
	}
	else if (option == 3) {
		int result;
		cout << "Enter the course code: ";
		result = Manager.deleteCourse(CourseCodeInput());
		cout << "Deletion of course record successful" << endl << endl;
		
		if (result == 0) {
			cout << "Deletion of course record successful" << endl << endl;
		}
		else if (result < 0) {
			cout << "Course not exist" << endl << endl;
		}
		end();
		return;
	}
	else if (option == 4) {
		Course* couPtr;
		cout << "Enter the course code: ";
		couPtr = Manager.queryCourse(CourseCodeInput());
		if (couPtr == NULL) {
			cout << "Course not exist" << endl << endl;
		}
		else {
			cout << endl;
			couPtr->print();
			cout << endl;
		}
		end();
		return;
	}
	else if (option == 5) {
		return;
	}
}

void CourseRegistration(){
	int option;
	string input;
	system("clear");

	cout << "HKUST Course Registration System (Registration Menu)" << endl;
	cout << "------------------------------------------------" << endl << endl;
	cout << "1. Register a course for a student" << endl;
	cout << "2. Drop a course for a student" << endl;
	cout << "3. Modify the exam mark of a course for a student" << endl;
	cout << "4. Query an existing registration record" << endl;
	cout << "5. Back to the main menu" << endl;
	cout << "Enter your choice (1-5): ";

	getline(cin, input);
	option = atoi(input.c_str());
	while (option > 6 || option < 1) {
		cout << "Invalid input, re-enter again (1-5): ";
		getline(cin, input);
		option = atoi(input.c_str());
	}

	if (option == 1) {
		cout << "Enter the student ID: ";
		Student* student = Manager.queryStudent(StudentIDInput());
		if (student == NULL) {
			cout << "Student not exist" << endl << endl;
			end();
			return;
		}

		cout << "Enter the course code: ";
		Course* course = Manager.queryCourse(CourseCodeInput());
		if (course == NULL) {
			cout << "Course not exist" << endl << endl;
			end();
			return;
		}

		CourseSelection selection(student, course, Unassigned);
		Manager.add(selection);
		cout << "Add course successful" << endl << endl;
		/*
		if (result < 0) {
			cout << "The student already registered the course" << endl << endl;
		}
		else {
			cout << "Add course successful" << endl << endl;
		}*/

		end();
		return;
	}
	else if (option == 2) {
		cout << "Enter the student ID: ";
		Student* student = Manager.queryStudent(StudentIDInput());
		if (student == NULL) {
			cout << "Student not exist" << endl << endl;
			end();
			return;
		}

		cout << "Enter the course code: ";
		Course* course = Manager.queryCourse(CourseCodeInput());
		if (course == NULL) {
			cout << "Course not exist" << endl << endl;
			end();
			return;
		}

		int result = Manager.deleteSelection(student->getStudentID(), course->getCourseCode());
		cout << "Drop course successful" << endl << endl;
		
		if (result == 0) {
			cout << "Drop course successful" << endl << endl;
		}
		else {
			cout << "The registration record not exist" << endl << endl;
		}
		end();
		return;
	}
	else if (option == 3) {
		cout << "Enter the student ID: ";
		Student* student = Manager.queryStudent(StudentIDInput());
		if (student == NULL) {
			cout << "Student not exist" << endl << endl;
			end();
			return;
		}

		cout << "Enter the course code: ";
		Course* course = Manager.queryCourse(CourseCodeInput());
		if (course == NULL) {
			cout << "Course not exist" << endl << endl;
			end();
			return;
		}

		CourseSelection* selection = Manager.querySelection(student->getStudentID(), course->getCourseCode());
		if (selection == NULL) {
			cout << "Registration record not exist" << endl << endl;
		}
		else {
			cout << "Enter the exam mark [" << selection->getExamMark() << "]: ";
			selection->setExamMark(ExamMarkInput());
			cout << "Modification of the exam mark successful" << endl << endl;
		}

		end();
		return;
	}
	else if (option == 4) {
		cout << "Enter the student ID: ";
		Student* student = Manager.queryStudent(StudentIDInput());
		if (student == NULL) {
			cout << "Student not exist" << endl << endl;
			end();
			return;
		}

		cout << "Enter the course code: ";
		Course* course = Manager.queryCourse(CourseCodeInput());
		if (course == NULL) {
			cout << "Course not exist" << endl << endl;
			end();
			return;
		}

		CourseSelection* selection = Manager.querySelection(student->getStudentID(), course->getCourseCode());
		if (selection == NULL) {
			cout << "Registration record not exist" << endl << endl;
		}
		else {
			cout << endl;
			selection->print();
			cout << endl;
		}

		end();
		return;
	}
	else if (option == 5) {
		return;
	}
}

/*
void ReportMenu(){
	int option;
	string input;
	system("clear");

	cout << "HKUST Course Registration System (Report Generation Menu)" << endl;
	cout << "------------------------------------------------" << endl << endl;
	cout << "1. List all student information" << endl;
	cout << "2. List all course information" << endl;
	cout << "3. List all the courses of a student" << endl;
	cout << "4. List all the students of a course" << endl;
	cout << "5. Back to the main menu" << endl;
	cout << "Enter your choice (1-5): ";
	
	getline(cin, input);
	option = atoi(input.c_str());
	while (option > 6 || option < 1) {
		cout << "Invalid input, re-enter again (1-5): ";
		getline(cin, input);
		option = atoi(input.c_str());
	}

	if (option == 1) {
		StudentMenu();
	}
	else if (option == 2) {
		CourseMenu();
	}
	else if (option == 3) {
		CourseRegistration();
	}
	else if (option == 4) {
		ReportMenu();
	}
	else if (option == 5) {
		FileMenu();
	}
}

void FileMenu(){
	int option;
	string input;
	system("clear");

	cout << "HKUST Course Registration System (File Menu)" << endl;
	cout << "------------------------------------------------" << endl << endl;
	cout << "1. Save the data" << endl;
	cout << "2. Load the data" << endl;
	cout << "3. Back to the main menu" << endl << endl;
	cout << "Enter your choice (1-3): ";

	getline(cin, input);
	option = atoi(input.c_str());
	while (option > 6 || option < 1) {
		cout << "Invalid input, re-enter again (1-3): ";
		getline(cin, input);
		option = atoi(input.c_str());
	}

	if (option == 1) {
		StudentMenu();
	}
	else if (option == 2) {
		CourseMenu();
	}
	else if (option == 3) {
		CourseRegistration();
	}
}
*/

int main(){
	while (true) 
	{
		int option;
		string input;
		system("clear");

		cout << "HKUST Course Registration System" << endl;
		cout << "--------------------------------" << endl << endl;
		cout << "1. Student Management" << endl;
		cout << "2. Course Management" << endl;
		cout << "3. Course Registration" << endl;
		cout << "4. Report Management" << endl;
		cout << "5. File Management" << endl;
		cout << "6. Exit" << endl << endl;
		cout << "Enter your choice (1-6): ";

		getline(cin, input);
		option = atoi(input.c_str());
		while (option > 6 || option < 1) {
			cout << "Invalid input, re-enter again (1-6): ";
			getline(cin, input);
			option = atoi(input.c_str());
		}

		if (option == 1) {
			StudentMenu();
		}
		else if (option == 2) {
			CourseMenu();
		}
		else if (option == 3) {
			CourseRegistration();
		}
		else if (option == 4) {
			cout << "ReportMenu" << endl;
			//ReportMenu();
		}
		else if (option == 5) {
			cout << "FileMenu" << endl;
			//FileMenu();
		}
		else if (option == 6) {
			exit(0);
		}
	}
}