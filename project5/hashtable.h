#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hashfunction.h"
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <list>
#include <cstdlib>
using namespace std;

template <typename T>
class HashTable {
	//typedef int(*) (const T&) HashFunction;

private:
	int m, table_size;
	list<T>* arr;
	T sample;
	typename list<T>::iterator Search(const string&);
	//HashFunction Hash;
	int HashType;
public:
	HashTable();
	~HashTable();
	HashTable(const int&, int);

	void Insert(const T&);
	T* Query(const string&);
	int Delete(const string&);
	void clear();
	bool isEmpty() const;
	int size() const;

	list<T> returnAll();
	list<T> returnByKey(string);
	//void printAll();
};

template <typename T> HashTable<T>::HashTable()
:arr(new list<T>),m(1), table_size(0){}

template <typename T> HashTable<T>::~HashTable() {
	delete[] arr;
}

template <typename T> HashTable<T>::HashTable(const int& m, int type)
	:arr(new list<T>[m]), m(m), table_size(0), HashType(type) {}

template <typename T> void HashTable<T>::Insert(const T& item) {
	int index = 0;
	index = Hash(item);
	
	arr[index].push_back(item);
	arr[index].sort();
	/*
	if (arr[index].empty()) arr[index].push_back(item);
	else {
		typename list<T>::iterator itr = arr[index].begin();
		for (int i = 1; i < arr[index].size(); i++) {
			if (item < *itr) {
				arr[index].insert(itr, item);
				table_size++;
				break;
			}
			++itr;
		}
		arr[index].push_back(item);
	}*/
}

template <typename T> T* HashTable<T>::Query(const string& str) {
	int index = 0;
	if (HashType == 1) index = StudentIDHash(str);
	if (HashType == 2) index = CourseCodeHash(str);
	if (HashType == 3) index = StudentIDHash(str);
	if (HashType == 4) index = CourseCodeHash(str);

	if (arr[index].empty()) {
		return NULL;
	}
	else {
		typename list<T>::iterator itr = arr[index].begin();
		for (int i = 0; i < arr[index].size(); i++) {
			if ((*itr).getkey() == str) {
				return &(*itr);
			}
			itr++;
		}
		return NULL;
	}
}
/*
template <typename T> 
typename list<T>::iterator HashTable<T>::Search(const string& str) {
	int index = 0;
	if (HashType == 1) index = StudentIDHash(str);
	if (HashType == 2) index = CourseCodeHash(str);
	if (HashType == 3) index = StudentIDHash(str);
	if (HashType == 4) index = CourseCodeHash(str);
	
	if (arr[index].empty()) {
		cerr << "It's empty" << endl;
		return arr[index].end();
	}
	else {
		typename list<T>::iterator itr = arr[index].begin();
		for (int i = 0; i < arr[index].size(); i++) {
			itr++;
			cout << i << endl;
			if ((*itr).getkey() == str) {
				return itr;
			}
		}
		cout<<"1"<<endl;
		return arr[index].end();
	}
}*/

template <typename T> int HashTable<T>::Delete(const string& str) {
	int index = 0;
	if (HashType == 1) index = StudentIDHash(str);
	if (HashType == 2) index = CourseCodeHash(str);
	if (HashType == 3) index = StudentIDHash(str);
	if (HashType == 4) index = CourseCodeHash(str);
	if (arr[index].empty()) {
		return -1;
	}
	else {
		typename list<T>::iterator itr = arr[index].begin();
		for (int i = 0; i < arr[index].size(); i++) {
			if ((*itr).getkey() == str) {
				arr[index - 1].erase(itr);
				table_size--;
				return 0;
			}
			itr++;
		}
		return -1;
	}
}

template <typename T> void HashTable<T>::clear() {
	for (int i = 0; i < m; i++)
		arr[i].clear();
	table_size = 0;
}

template <typename T> bool HashTable<T>::isEmpty() const {
	return table_size == 0;
}

template <typename T> int HashTable<T>::size() const {
	return table_size;
}

template <typename T>
list<T> HashTable<T>::returnAll(){
	list<T> result;
	int i;
	for (i = 0; i != m; i++) {
		list<T>* List = &(arr[i]);
		if (!(List->empty())) {
			typename list<T>::iterator itr;
			for (itr = List->begin(); itr != List->end(); itr++) {
				result.push_back(*itr);
			}
		}
	}
	return result;
}

template <typename T>
list<T> HashTable<T>::returnByKey(string key){
	list<T> result;
	int hash_number;
	if (HashType == 1) hash_number = StudentIDHash(key);
	if (HashType == 2) hash_number = CourseCodeHash(key);
	if (HashType == 3) hash_number = StudentIDHash(key);
	if (HashType == 4) hash_number = CourseCodeHash(key);
	list<T>* List = &(arr[hash_number]);
	typename list<T>::iterator itr;

	for (itr = List->begin(); itr != List->end(); itr++) {
		if ((*itr) == key) {
			result.push_back(*itr);
		}
	}
	return result;
}

#endif