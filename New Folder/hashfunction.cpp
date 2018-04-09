#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <math.h>
#include "hashfunction.h"
using namespace std;


int getterm(char a) {
	int number = (int)a;
	if (number >= 48 && number <= 57) {
		return (number - 48);
	}
	else if (number >= 65 && number <= 90) {
		return (number - 64 + 10);
	}
	else {
		cerr << "Invalid CourseCode." << endl;
		return 0;
	}
}

int StudentIDHash(string id) {
	int value = 0;
	int term;
	for (int i = 0; i < StudentID_Length; i++) {
		term = getterm(id[i]) * pow(StudentID_B, i);
		value += term;
	}
	return value % StudentID_M;
}

int CourseCodeHash(string course) {
	int value = 0;
	int term;
	for (int i = 0; i < course.size(); i++) {
		term = getterm(course[i]) * pow(CourseCode_B, i);
		value += term;
	}
	return value % CourseCode_M;
}
/*
int StudentHash(const Student& student) {
return StudentIDHash(student.getStudentID());
}

int CourseHash(const Course& course) {
return CourseCodeHash(course.getCourseCode());
}

int IDIndexHash(const Index& index) {
return StudentIDHash(index.getkey());
}

int CodeIndexHash(const Index& index) {
return CourseCodeHash(index.getkey());
}
*/
int Hash(const Student& student) {
	return StudentIDHash(student.getStudentID());
}

int Hash(const Course& course) {
	return CourseCodeHash(course.getCourseCode());
}

int Hash(const IDIndex& index) {
	return StudentIDHash(index.getkey());
}

int Hash(const CodeIndex& index) {
	return CourseCodeHash(index.getkey());
}