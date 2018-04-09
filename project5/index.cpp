#include "index.h"

IDIndex::IDIndex() {}
IDIndex::~IDIndex() {}
IDIndex::IDIndex(string str, CourseSelection* s):
	key(str),selection(s){}

string IDIndex::getkey() const {
	return key;
}
CourseSelection* IDIndex::getselection() const {
	return selection;
}
bool IDIndex::operator>(const IDIndex& index) const {
	return key > index.key;
}

bool IDIndex::operator==(const IDIndex& index) const {
	return key == index.key;
}

bool IDIndex::operator<(const IDIndex& index) const {
	return key < index.key;
}
/*
CourseSelection& Index::operator*() {
	return *(selection);
}*/

CodeIndex::CodeIndex() {}
CodeIndex::~CodeIndex() {}
CodeIndex::CodeIndex(string str, CourseSelection* s) :
	key(str), selection(s) {}

string CodeIndex::getkey() const {
	return key;
}
CourseSelection* CodeIndex::getselection() const {
	return selection;
}
bool CodeIndex::operator>(const CodeIndex& index) const {
	return key > index.key;
}

bool CodeIndex::operator==(const CodeIndex& index) const {
	return key == index.key;
}

bool CodeIndex::operator<(const CodeIndex& index) const {
	return key < index.key;
}
/*
CourseSelection& Index::operator*() {
return *(selection);
}*/