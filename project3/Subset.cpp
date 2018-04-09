#include <iostream>
#include <stdio.h>
#include "randomized_queue.h"
using namespace std;

int main(int argc, char *argv[]){
	//check if the input k is valid
	if (argc == 1) {
		cerr << "Please specify an output number k!" << endl;
		return 0;
	}
	if (atoi(argv[1]) <= 0) {
		cerr << "Invalid output number k!" << endl;
		return 0;
	}

	RandomizedQueue<string> set;
	char a;
	string b = "";
	int size;

	//read the input divided by space
	while ((a = getchar()) != '\n') {
		if (a != ' ') {
			b += a;
		}
		else {
			if (b != "" && b != " ") {
				set.enqueue(b);
				b = "";
			}
		}
	}
	if (b != "" && b != " ") set.enqueue(b);

	RandomizedQueue<string>::Iterator itr = set.iterator();
	//check if the size of the subset is shorter then the set
	if (atoi(argv[1]) > set.size()) {
		size = set.size();
		for (int i = 0; i < size; i++) {
			cout << *itr << endl;
			++itr;
		}
		cerr << "Subset size can not be lager than the set size." << endl;
		return 0;
	}
	//print the result
	else {
		size = atoi(argv[1]);
		for (int i = 0; i < size; i++) {
			cout << *itr << endl;
			++itr;
		}
	}
	return 0;
}