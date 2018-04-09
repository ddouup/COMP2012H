#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include<stdexcept> 
using namespace std;

template <class T> 
class Deque
{
private:
	//use doubly linked list to implement Deque
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};
	typedef Node* NodePtr;
	
	int length;
	NodePtr first; //pointer that points to the first Node
	NodePtr last;  //pointer that points to the last Node
public:
	Deque();             // construct an empty deque
	~Deque();			 // delete the deque
	bool isEmpty();      // is the deque empty?
	int size();             // return the number of items on the deque
	void addFirst(T item);  // insert the item at the front of the queue
	void addLast(T item);  // insert the item at the end of the queue
	T removeFirst();  // delete and return the first item in queue
	T removeLast();   // delete and return the last item in queue
	
	//define new type Iterator
	struct Iterator {
		NodePtr itr;
		void operator++() {
			itr = itr->next; //overload operator++
		}
		T operator*() {
			return itr->data; //overload operator*
		}
	};
	Iterator iterator();  // return an iterator that examines the items in order from front to back
};

template <class T>
Deque<T>::Deque() :first(NULL), last(NULL), length(0) {}

template <class T>
Deque<T>::~Deque() 
{
	//delete each Node
	NodePtr cur;
	while (first != NULL) {
		cur = first;
		first = first->next;
		delete cur;
	}
	last = NULL;
}

template <class T>
bool Deque<T>::isEmpty() {
	return length == 0;
}

template <class T>
int Deque<T>::size(){
	return length;
}

template <class T>
void Deque<T>::addFirst(T item) {
	//creat a new Node to store the item
	NodePtr cur = new Node;
	cur->data = item;
	cur->prev = NULL;

	//put item into the first of the Deque
	if (length == 0) {
		cur->next = NULL;
		first = cur;
		last = first;
	}
	else{
		cur->next = first;
		first->prev = cur;
		first = first->prev;
	}
	length++;
}

template <class T>
void Deque<T>::addLast(T item) {
	//creat a new Node to store the item
	NodePtr cur = new Node;
	cur->data = item;
	cur->next = NULL;

	//put item into the last of the Deque
	if (length == 0) {
		cur->prev = NULL;
		last = cur;
		first = last;
	}
	else {
		cur->prev = last;
		last->next = cur;
		last = last->next;
	}
	length++;
}

template <class T>
T Deque<T>::removeFirst() {
	NodePtr cur;
	//see if the Deque is empty
	if (length == 0) {
		throw runtime_error("The deque is already empty.");
	}
	//see if the Deque has only one item
	else if (length == 1) {
		cur = first;
		T a = cur->data;
		first = NULL;
		last = NULL;
		delete cur;
		length--;
		return a;
	}
	//remove the first item
	else {
		cur = first;
		T a = cur->data;
		(first->next)->prev = NULL;
		first = first->next;
		delete cur;
		length--;
		return a;
	}
}

template <class T>
T Deque<T>::removeLast() {
	NodePtr cur;
	//see if the Deque is empty
	if (length == 0) {
		throw runtime_error("The deque is already empty.");
	}
	//see if the Deque has only one item
	else if (length == 1) {
		cur = last;
		T a = cur->data;
		first = NULL;
		last = NULL;
		delete cur;
		length--;
		return a;
	}
	//remove the last item
	else {
		cur = last;
		T a = cur->data;
		(last->prev)->next = NULL;
		last = last->prev;
		delete cur;
		length--;
		return a;
	}
}

//define the initialization function of Iterator
template <class T>
typename Deque<T>::Iterator Deque<T>::iterator() {
	Iterator it;
	it.itr = first;
	return it;
}
#endif