#ifndef RANDOMIZE_DQUEUE_H
#define RANDOMIZE_DQUEUE_H

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include<stdexcept> 
using namespace std;

template <class T>
class RandomizedQueue
{
	//use dynamic array to implement randomized queue
private:
	T *array1;
	T *array2;
	int length;
	int maxsize;

public:
	RandomizedQueue();   // construct an empty randomized queue
	~RandomizedQueue(); // delete the randomized queue
	bool isEmpty();          // is the queue empty?
	int size();                 // return the number of items on the queue
	void enqueue(T item);    // add the item
	T dequeue();             // delete and return a random item
	T sample();				// return (but do not delete) a random item
	//define new type Iterator
	struct Iterator {
		T content;
		T *array3;
		int lengthi;
		//overload operator++
		void operator++() {
			if (lengthi != 0) {
				int a = rand() % lengthi;
				content = array3[a];
				array3[a] = array3[lengthi - 1];
				lengthi--;
			}
		}
		//overload operator*
		T operator*() {  
			return content;
		}
	};
	Iterator iterator();  // return an iterator that examines the items in order from front to back
}; 

template <class T>
RandomizedQueue<T>::RandomizedQueue():maxsize(1),length(0) {
	array1 = new T[maxsize]; //initailize the array1
	srand(time(NULL));
}

template <class T>
RandomizedQueue<T>::~RandomizedQueue() {
	delete[]array1;
}

template <class T>
bool RandomizedQueue<T>::isEmpty() {
	return length == 0;
}

template <class T>
int RandomizedQueue<T>::size() {
	return length;
}

template <class T>
void RandomizedQueue<T>::enqueue(T item) {
	length++;
	if (length <= maxsize) {
		array1[length-1] = item;
	}
	else {
		//double the size of the array1 if it's full
		maxsize = 2*maxsize;
		//create a new array2 with double size and copy the data in array1 to array2
		array2 = new T[maxsize];
		for (int a = 0; a < length-1; a++) {
			array2[a] = array1[a];
		}
		array2[length - 1] = item;
		//change the name back to array1
		T *temp = array1;
		array1 = array2;
		delete[]temp;
	}
}

template <class T>
T RandomizedQueue<T>::dequeue() {
	//see if the randomized deque is empty
	if (length == 0) {
		throw runtime_error("The randomized queue is already empty.");
	}
	//randomly remove an item
	else {
		int a = rand() % length;
		T temp = array1[a];
		array1[a] = array1[length-1];
		length--;
		return temp;
	}
}

template <class T>
T RandomizedQueue<T>::sample() {
	//see if the randomized deque is empty
	if (length == 0) {
		throw runtime_error("The randomized queue is already empty.");
	}
	//randomly sample an item
	else{
		int a = rand() % length;
		return array1[a];
	}
}

//define the initialization function of Iterator
template <class T>
typename RandomizedQueue<T>::Iterator RandomizedQueue<T>::iterator() {
	Iterator it;
	//see if the randomized deque is empty
	if (length == 0) {
		throw runtime_error("The randomized queue is already empty.");
	}
	else {
		it.lengthi = length;
		int a = rand() % length;
		//create a new array3 to store the data in array1
		//in order to avoid the iterator to point to the same data
		it.array3 = new T[length];
		for (int i = 0; i < length; i++) {
			it.array3[i] = array1[i];
		}
		it.content = it.array3[a];
		it.array3[a] = it.array3[length - 1];
		it.lengthi--;
		return it;
	}
}
#endif