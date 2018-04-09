#include "RegistrationManager.h"
#include <iterator>
#include <algorithm>
#include <list>
#include <stdexcept>
using namespace std;


RegistrationManager::RegistrationManager(): 
	Students(StudentID_M, 1),Courses(CourseCode_M, 2),IDIndexs(StudentID_M, 3),CodeIndexs(CourseCode_M, 4){
	/*
	Students(StudentID_M, 1);
	Courses(CourseCode_M, 2);
	IDIndexs(StudentID_M, 3);
	CodeIndexs(CourseCode_M, 4);*/
}

RegistrationManager::~RegistrationManager() {}

void RegistrationManager::add(const Student& student) {
	Students.Insert(student);
}

void RegistrationManager::add(const Course& course) {
	Courses.Insert(course);
}

void RegistrationManager::add(const CourseSelection& selection) {
	CourseSelection* address;

	/*
	arr[index].push_back(item);
	arr[index].sort();
	*/
	
	if (Selections.empty()) { 
		Selections.push_back(selection); 
		list<CourseSelection>::iterator itr = Selections.begin();
		address = &(*itr);
	}
	else {
		list<CourseSelection>::iterator itr = Selections.begin();
		for (int i = 1; i < Selections.size(); i++) {
			if (selection < *itr) {
				Selections.insert(itr, selection);
				break;
			}
			++itr;
		}
		Selections.push_back(selection);
	}

	if (address != NULL) {
		IDIndex id_index(selection.getStudentID(), address);
		CodeIndex code_index(selection.getCourseCode(), address);
		IDIndexs.Insert(id_index);
		CodeIndexs.Insert(code_index);
	}
}

int RegistrationManager::deleteStudent(const string& id) {
	return Students.Delete(id);
}

int RegistrationManager::deleteCourse(const string& code) {
	return Courses.Delete(code);
}

int RegistrationManager::deleteSelection(const string& id, const string& code) {
	list<CourseSelection>::iterator itr;
	CourseSelection* selection = NULL;
	for (itr = Selections.begin(); itr != Selections.end(); itr++) {
		if (itr->getStudentID() == id && itr->getCourseCode() == code) {
			selection = &(*itr);
			IDIndex id_index(selection->getStudentID(), selection);
			CodeIndex code_index(selection->getCourseCode(), selection);
			
			int i;
			i = IDIndexs.Delete(id_index.getkey());
			if (i < 0) return -1;
			i = CodeIndexs.Delete(code_index.getkey());
			if (i < 0) return -1;
			Selections.erase(itr);
			return 0;
		}
	}
	return -1;
}

Student* RegistrationManager::queryStudent(const string& id) {
	return Students.Query(id);
}

Course* RegistrationManager::queryCourse(const string& code) {
	return Courses.Query(code);
}

CourseSelection* RegistrationManager::querySelection(const string& id, const string& code) {
	list<CourseSelection>::iterator itr;
	for (itr = Selections.begin(); itr != Selections.end(); itr++) {
		if (itr->getStudentID() == id && itr->getCourseCode() == code) {
			return &(*itr);
		}
	}
	return NULL;
}