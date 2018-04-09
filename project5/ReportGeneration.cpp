#include "ReportGeneration.h"
#include "tables.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <string>
#include <cstdio>

void reportAllCourses(list<Course> courses) {
	FILE* fout = fopen("Courses.html", "w");
	fprintf(fout,
		"<HTML>\n"
		"<HEAD>\n"
		"<HEAD>\n");
	fprintf(fout,
		"<TITLE>All Courses List</TITLE>\n"
		"</HEAD>\n");
	fprintf(fout,
		"<BODY bgColor=#ffffcc>\n"
		"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
		"<H2>All Course List</H2>\n"
		"<P>\n"
		"<TABLE cellSpacing=1 cellPadding=1 border=1>\n\n");
	fprintf(fout,
		"<TB>\n"
		"<TD>Course Code</TD>\n"
		"<TD>Course Name</TD>\n"
		"<TD>Credit</TD>\n"
		"</TR>\n\n");

	list<Course>::iterator itr;

	for (itr = courses.begin(); itr != courses.end(); itr++) {
		fprintf(fout,
			"<TR>\n"
			"<TD>%s</TD>\n"
			"<TD>%s</TD>\n"
			"<TD>%d</TD>\n"
			"</TD>\n\n",
			itr->getCourseCode().c_str(), itr->getCourseName().c_str(), itr->getCredit());
	}

	fprintf(fout,
		"</TABLE>\n"
		"</P>\n"
		"</BODY>\n"
		"</HTML>\n");

	fclose(fout);
}

void reportAllStudents(list<Student> students) {
	FILE* fout = fopen("Students.html", "w");
	fprintf(fout,
		"<HTML>\n"
		"<HEAD>\n"
		"<HEAD>\n");
	fprintf(fout,
		"<TITLE>All Students List</TITLE>\n"
		"</HEAD>\n");
	fprintf(fout,
		"<BODY bgColor=#ffffcc>\n"
		"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
		"<H2>All Students List</H2>\n"
		"<P>\n"
		"<TABLE cellSpacing=1 cellPadding=1 border=1>\n\n");
	fprintf(fout,
		"<TB>\n"
		"<TD>Student ID</TD>\n"
		"<TD>Studnet Name</TD>\n"
		"<TD>Year</TD>\n"
		"<TD>Gender</TD>\n"
		"</TR>\n\n");

	list<Student>::iterator itr;

	for (itr = students.begin(); itr != students.end(); itr++) {
		fprintf(fout,
			"<TR>\n"
			"<TD>%s</TD>\n"
			"<TD>%s</TD>\n"
			"<TD>%d</TD>\n"
			"<TD>%s</TD>\n"
			"</TD>\n\n",
			itr->getStudentID().c_str(), itr->getStudentName().c_str(), itr->getYear(),
			itr->getGender() == Male ? "Male" : "Female");
	}

	fprintf(fout,
		"</TABLE>\n"
		"</P>\n"
		"</BODY>\n"
		"</HTML>\n");

	fclose(fout);
}

void reportStudentsOfCourse(const Course& course, list<CourseSelection> selections) {
	char name[50];
	sprintf(name, "%s.html", course.getCourseCode().c_str());

	FILE* fout = fopen(name, "w");
	fprintf(fout,
		"<HTML>\n"
		"<HEAD>\n"
		"<HEAD>\n");
	fprintf(fout,
		"<TITLE>Student Records for Course %s</TITLE>\n"
		"</HEAD>\n",
		course.getCourseCode().c_str());
	fprintf(fout,
		"<BODY bgColor=#ffffcc>\n"
		"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
		"<H2>Student Records for Course: %s (%s)</H2>\n"
		"<P>\n"
		"<TABLE cellSpacing=1 cellPadding=1 border=1>\n\n",
		course.getCourseName().c_str(), course.getCourseCode().c_str());

	if (selections.begin() == selections.end()) {
		fprintf(fout,
			"<p>No Student took this course.</p>");
	}
	else {
		fprintf(fout,
			"<TB>\n"
			"<TD>Student ID</TD>\n"
			"<TD>Studnet Name</TD>\n"
			"<TD>Year</TD>\n"
			"<TD>Gender</TD>\n"
			"<TD>Exma Mark</TD>\n"
			"</TR>\n\n");

		list<CourseSelection>::iterator itr;

		for (itr = selections.begin(); itr != selections.end(); itr++) {
			char mark_str[16];
			sprintf(mark_str, "%d", itr->getExamMark());

			fprintf(fout,
				"<TR>\n"
				"<TD>%s</TD>\n"
				"<TD>%s</TD>\n"
				"<TD>%d</TD>\n"
				"<TD>%s</TD>\n"
				"<TD>%s</TD>\n"
				"</TD>\n\n",
				itr->getStudent()->getStudentID().c_str(),
				itr->getStudent()->getStudentName().c_str(),
				itr->getStudent()->getYear(),
				itr->getStudent()->getGender() == Male ? "Male" : "Female",
				itr->getExamMark() == Unassigned ? "N/A" : mark_str);
		}
	}

	fprintf(fout,
		"</TABLE>\n"
		"</P>\n"
		"</BODY>\n"
		"</HTML>\n");

	fclose(fout);
}

void reportCoursesOfStudent(const Student& student, list<CourseSelection> selections) {
	char name[50];
	sprintf(name, "%s.html", student.getStudentID().c_str());

	FILE* fout = fopen(name, "w");
	fprintf(fout,
		"<HTML>\n"
		"<HEAD>\n"
		"<HEAD>\n");
	fprintf(fout,
		"<TITLE>Course Records for Student %s</TITLE>\n"
		"</HEAD>\n",
		student.getStudentID().c_str());
	fprintf(fout,
		"<BODY bgColor=#ffffcc>\n"
		"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
		"<H2>Course Records for Student: %s (%s)</H2>\n"
		"<P>\n"
		"<TABLE cellSpacing=1 cellPadding=1 border=1>\n\n",
		student.getStudentName().c_str(), student.getStudentID().c_str());

	if (selections.begin() == selections.end()) {
		fprintf(fout,
			"<p>No course taken.</p>");
	}
	else {
		fprintf(fout,
			"<TB>\n"
			"<TD>Course code</TD>\n"
			"<TD>Course Name</TD>\n"
			"<TD>Credit</TD>\n"
			"<TD>Exam Mark</TD>\n"
			"</TR>\n\n");

		list<CourseSelection>::iterator itr;

		for (itr = selections.begin(); itr != selections.end(); itr++) {
			char mark_str[16];
			sprintf(mark_str, "%d", itr->getExamMark());

			fprintf(fout,
				"<TR>\n"
				"<TD>%s</TD>\n"
				"<TD>%s</TD>\n"
				"<TD>%d</TD>\n"
				"<TD>%s</TD>\n"
				"</TD>\n\n",
				itr->getCourse()->getCourseCode().c_str(),
				itr->getCourse()->getCourseName().c_str(),
				itr->getCourse()->getCredit(),
				itr->getExamMark() == Unassigned ? "N/A" : mark_str);
		}
	}

	fprintf(fout,
		"</TABLE>\n"
		"</P>\n"
		"</BODY>\n"
		"</HTML>\n");

	fclose(fout);
}