#ifndef REPORTGENERATION_H
#define REPORTGENERATION_H
#include <iterator>
#include <algorithm>
#include <list>
#include "tables.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <string>
#include <cstdio>


void reportAllCourses(list<Course>);

void reportAllStudents(list<Student>);

void reportStudentsOfCourse(const Course&, list<CourseSelection>);

void reportCoursesOfStudent(const Student&, list<CourseSelection>);

#endif // !REPORTGENERATION_H
