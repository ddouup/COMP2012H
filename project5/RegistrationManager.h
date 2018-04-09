#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H
#include <iterator>
#include <algorithm>
#include <list>
#include "hashtable.h"
#include "tables.h"
#include "ReportGeneration.h"
#include "hashfunction.h"
#include "index.h"

class RegistrationManager {
private:
	HashTable<Student> Students;
	HashTable<Course> Courses;
	list<CourseSelection> Selections;
	HashTable<IDIndex> IDIndexs;
	HashTable<CodeIndex> CodeIndexs;
public:
	RegistrationManager();
	~RegistrationManager();

	void add(const Student&);
	void add(const Course&);
	void add(const CourseSelection&);

	int drop(const string& id, const string& code);

	int deleteStudent(const string& id);
	int deleteCourse(const string& code);
	int deleteSelection(const string& id, const string& code);

	Student* queryStudent(const string& id);
	Course* queryCourse(const string& code);
	CourseSelection* querySelection(const string& id, const string& code);

	void StudentsHTML();
	void CoursesHTML();
	void StudentsOfCourseHTML(Course* cou);
	void CoursesOfStudentHTML(Student* stu);

	/*
	void readDataFile(char* file_name);
	void saveDataFile(char* file_name);*/
};

#endif