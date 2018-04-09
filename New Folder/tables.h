#ifndef TABLES_H
#define TABLES_H
#include <string>
using namespace std;

const int StudentID_Length = 8;
const int StudentID_M = 29;
const int StudentID_B = 10;

const int StudentName_Max = 32;
const int StudentName_Min = 1;

const int CourseCode_Max = 8;
const int CourseCode_Min = 7;
const int CourseCode_M = 17;
const int CourseCode_B = 36;

const int CourseName_Max = 50;
const int CourseName_Min = 1;

const int Credit_Min = 0;
const int Credit_Max = 5;

const int Male = 0;
const int Female = 1;

const int Unassigned = -1;
const int ExamMark_Max = 100;
const int ExamMark_Min = 0;

const int Year_Max = 3;
const int Year_Min = 1;

class Student {
private:
	string StudentID;
	string StudentName;
	int Year;
	int Gender;
public:
	Student();
	~Student();
	Student(const Student&);

	string getStudentID() const;
	string getStudentName() const;
	int getYear() const;
	int getGender() const;
	string getkey() const;

	void setStudentID(const string&);
	void setStudentName(const string&);
	void setYear(int);
	void setGender(int);

	Student& operator=(const Student&);
	bool operator<(const Student&) const;
	bool operator>(const Student&) const;
	bool operator==(const Student&) const;
	bool operator==(const string& id) const;

	void print();
	static bool ValidID(const string&);
	/*
	bool isValid() const;
	static bool isValidID(const string&);
	static bool isValidName(const String&);
	static bool isValidYear(const int&);
	static bool isValidGender(const int&);*/
};

class Course {
private:
	string CourseCode;
	string CourseName;
	string key;
	int Credit;
public:
	Course();
	~Course();
	Course(const Course&);

	int getCredit() const;
	string getCourseCode() const;
	string getCourseName() const;
	string getkey() const;

	void setCourseCode(const string&);
	void setCourseName(const string&);
	void setCredit(const int);

	Course& operator=(const Course&);
	bool operator<(const Course& cou) const;
	bool operator>(const Course& cou) const;
	bool operator==(const Course& cou) const;
	bool operator==(const string& code) const;

	void print();
	static bool ValidCode(const string&);
	/*
	bool isValid() const;
	static bool isValidCode(const string&);
	static bool isValidName(const string&);
	static bool isValidCredit(const int&);*/
};

class CourseSelection {
private:
	Student* student;
	Course* course;
	int ExamMark;
public:
	CourseSelection();
	~CourseSelection();
	CourseSelection(Student*, Course*, int);

	string getStudentID() const;
	string getCourseCode() const;
	int getExamMark() const;
	Student* getStudent() const;
	Course* getCourse() const;

	void setCourse(Course&);
	void setCourse(Course*);
	void setStudent(Student&);
	void setStudent(Student*);
	void setExamMark(const int);

	CourseSelection& operator=(CourseSelection&);
	bool operator<(const CourseSelection&) const;
	bool operator>(const CourseSelection&) const;
	bool operator==(const CourseSelection&) const;


	void print();
	/*
	bool isValid() const;
	static bool isValidExammark(const int&);*/
};

#endif