#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H
#include "tables.h"
#include "index.h"
using namespace std;

int getterm(char a);
int StudentIDHash(string id);
int CourseCodeHash(string course);
int Hash(const Student& student);
int Hash(const Course& course);
int Hash(const IDIndex& index);
int Hash(const CodeIndex& index);
#endif