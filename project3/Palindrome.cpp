#include <iostream>
#include <stdio.h>
#include"deque.h"
using namespace std;

int main() {
	Deque<char> Palindrome;  //initilize the origin characters
	Deque<char> rPalindrome; //initilize the reverse characters
	Deque<char> cPalindrome; //initilize the characters after change
	char a;
	bool c = true;

	//input the characters
	while ((a = getchar()) != '\n') {
		Palindrome.addLast(a);
		rPalindrome.addFirst(a);
	}

	Deque<char>::Iterator itr = Palindrome.iterator();
	//change the characters in Palindrome
	for (int i = 0; i < Palindrome.size(); i++) {
		if (*itr == 'A') cPalindrome.addLast('T');
		if (*itr == 'C') cPalindrome.addLast('G');
		if (*itr == 'G') cPalindrome.addLast('C');
		if (*itr == 'T') cPalindrome.addLast('A');
		++itr;
	}

	if (cPalindrome.isEmpty()) c = false;
	else{
		// compare the characters one by one using iterators
		Deque<char>::Iterator citr = cPalindrome.iterator();
		Deque<char>::Iterator ritr = rPalindrome.iterator();

		for (int i = 0; i < Palindrome.size(); i++) {
			if (*citr == *ritr) {
				++citr;
				++ritr;
			}
			else {
				c = false;
				break;
			}
		}
	}
	//print the result
	if (c) cout << "true" << endl;
	else cout << "false" << endl;

	return 0;
}