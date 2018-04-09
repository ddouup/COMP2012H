#ifndef INDEX_H
#define INDEX_H
#include <iostream>
#include <string>
#include <list>
#include "tables.h"
using namespace std;

class IDIndex {
private:
	string key;
	CourseSelection* selection;

public:
	IDIndex();
	~IDIndex();
	IDIndex(string, CourseSelection*);

	string getkey() const;
	CourseSelection* getselection() const;

	bool operator>(const IDIndex& index) const;
	bool operator==(const IDIndex& index) const;
	bool operator<(const IDIndex& index) const;
	//CourseSelection& operator*();
};

class CodeIndex {
private:
	string key;
	CourseSelection* selection;

public:
	CodeIndex();
	~CodeIndex();
	CodeIndex(string, CourseSelection*);

	string getkey() const;
	CourseSelection* getselection() const;

	bool operator>(const CodeIndex& index) const;
	bool operator==(const CodeIndex& index) const;
	bool operator<(const CodeIndex& index) const;
	//CourseSelection& operator*();
};

#endif
