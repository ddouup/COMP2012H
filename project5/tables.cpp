#include "tables.h"
#include <stdio.h>
#include <iostream>
using namespace std;

//Student Class
Student::Student() {};

Student::~Student() {};

Student::Student(const Student& student) {
	setStudentID(student.getStudentID());
	setStudentName(student.getStudentName());
	setYear(student.getYear());
	setGender(student.getYear());
}

string Student::getStudentID() const {
	return StudentID;
}
string Student::getStudentName() const {
	return StudentName;
}
int Student::getYear() const {
	return Year;
}
int Student::getGender() const {
	return Gender;
}
string Student::getkey() const {
	return StudentID;
}

void Student::setStudentID(const string& id) {
	if (ValidID(id)) {
		StudentID = id;
	}
	//else cerr << "Please enter a valid id." << endl;
}
void Student::setStudentName(const string& name) {
	if (name.size() >= StudentName_Min && name.size() <= StudentName_Max) {
		StudentName = name;
	}
	//else cerr << "Please enter a valid name." << endl;
}
void Student::setYear(int year) {
	if (year >= 1 && year <= 3) {
		Year = year;
	}
	//else cerr << "Please enter a valid year." << endl;
}
void Student::setGender(int gender) {
	if (gender == Male || gender == Female) {
		Gender = gender;
	}
	//else cerr << "Please enter a valid gender." << endl;
}

Student& Student::operator=(const Student& student) {
	setStudentID(student.getStudentID());
	setStudentName(student.getStudentName());
	setYear(student.getYear());
	setGender(student.getYear());
	return *this;
}
bool Student::operator<(const Student& student) const {
	return StudentID < student.getStudentID();
}
bool Student::operator>(const Student& student) const {
	return StudentID > student.getStudentID();
}
bool Student::operator==(const Student& student) const {
	return StudentID == student.getStudentID();
}
bool Student::operator==(const string& id) const {
	return StudentID == id;
}

void Student::print() {
	cout << "Student ID: " << StudentID << endl;
	cout << "Student Name: " << StudentName << endl;
	cout << "Student Year: " << Year << endl;
	cout << "Student Gender: ";
	if (Gender == Male) {
		cout << "Male" << endl;
	}
	if (Gender == Female) {
		cout << "Female" << endl;
	}
}

bool Student::ValidID(const string& id) {
	bool valid = true;
	for (int i = 0; i < id.size(); i++) {
		if (id[i]<'0' || id[i]>'9') {
			valid = false;
			break;
		}
	}
	return id.size() == StudentID_Length && valid;
}


//Course Class
Course::Course() {};

Course::~Course() {};

Course::Course(const Course& course) {
	setCourseCode(course.getCourseCode());
	setCourseName(course.getCourseName());
}

string Course::getCourseCode() const {
	return CourseCode;
}
string Course::getCourseName() const {
	return CourseName;
}
int Course::getCredit() const {
	return Credit;
}
string Course::getkey() const {
	return CourseCode;
}

void Course::setCourseCode(const string& code) {
	if (ValidCode(code)) {
		CourseCode = code;
	}
	//else cerr << "Please enter a valid CourseCode." << endl;
}
void Course::setCourseName(const string& name) {
	if (name.size() >= CourseName_Min && name.size() <= CourseName_Max) {
		CourseName = name;
	}
	//else cerr << "Please enter a valid CourseName." << endl;
}
void Course::setCredit(const int credit) {
	if (credit >= Credit_Min && credit <= Credit_Max) {
		Credit = credit;
	}
	//else cerr << "Please enter a valid credit." << endl;
}

Course& Course::operator=(const Course& course) {
	setCourseCode(course.getCourseCode());
	setCourseName(course.getCourseName());
	return *this;
}
bool Course::operator<(const Course& course)  const {
	return CourseCode < course.getCourseCode();
}
bool Course::operator>(const Course& course)  const {
	return CourseCode > course.getCourseCode();
}
bool Course::operator==(const Course& course)  const {
	return CourseCode == course.getCourseCode();
}
bool Course::operator==(const string& code)  const {
	return CourseCode == code;
}

void Course::print() {
	cout << "Course Code: " << CourseCode << endl;
	cout << "Course Name: " << CourseName << endl;
	cout << "Course Credit: " << Credit << endl;
}

bool Course::ValidCode(const string& code) {
	bool valid = true;
	for (int i = 0; i < code.size(); i++) {
		if (i < 4) {
			if (code[i]<'A' || code[i]>'Z') {
				valid = false;
				break;
			}
		}
		if (code[i] < '0' || (code[i] > '9' && code[i] < 'A') || code[i] > 'Z') {
			valid = false;
			break;
		}
	}
	return code.length() >= CourseCode_Min && code.length() <= CourseCode_Max && valid;
}

//CourseSelection Class
CourseSelection::CourseSelection():student(NULL), course(NULL), ExamMark(Unassigned) {}

CourseSelection::~CourseSelection() {}

CourseSelection::CourseSelection(Student* student, Course* course, int mark)
	: student(student), course(course), ExamMark(mark) {}

string CourseSelection::getStudentID() const {
	return student->getStudentID();
}
string CourseSelection::getCourseCode() const {
	return course->getCourseCode();
}
int CourseSelection::getExamMark() const {
	return ExamMark;
}
Student* CourseSelection::getStudent() const {
	return student;
}
Course* CourseSelection::getCourse() const {
	return course;
}

void CourseSelection::setCourse(Course& course1) {
	course = &course1;
}
void CourseSelection::setCourse(Course* course1) {
	course = course1;
}
void CourseSelection::setStudent(Student& student1) {
	student = &student1;
}
void CourseSelection::setStudent(Student* student1) {
	student = student1;
}
void CourseSelection::setExamMark(const int mark) {
	if (mark >= ExamMark_Min && mark <= ExamMark_Max) {
		ExamMark = mark;
	}
	//else cerr << "Please enter a valid mark." << endl;
}

CourseSelection& CourseSelection::operator=(CourseSelection& courseselection) {
	setCourse(courseselection.getCourse());
	setStudent(courseselection.getStudent());
	setExamMark(courseselection.getExamMark());
	return *this;
}

bool CourseSelection::operator<(const CourseSelection& courseselection) const {
	if (*student == *(courseselection.getStudent())) {
		return *course < *(courseselection.getCourse());
	}
	else {
		return *student < *(courseselection.getStudent());
	}
}
bool CourseSelection::operator>(const CourseSelection& courseselection)  const {
	if (*student == *(courseselection.getStudent())) {
		return *course > *(courseselection.getCourse());
	}
	else {
		return *student > *(courseselection.getStudent());
	}
}
bool CourseSelection::operator==(const CourseSelection& courseselection) const {
	return *course == *(courseselection.getCourse()) 
		&& *student < *(courseselection.getStudent());
}

void CourseSelection::print() {
	cout << "Student ID: " << getStudentID() << endl;
	cout << "CourseCode: " << getCourseCode() << endl;
	char mark[16];
	sprintf(mark, "%d", ExamMark);
	cout << "Exam Mark: " << ((ExamMark == Unassigned) ? "N/A" : mark) << endl;
}