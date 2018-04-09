//IntStackTest.cpp
#include "IntStack.h"
#include <string>
int fibonacci(int);

int main() {
  IntStack<int> is;
  // Add some Fibonacci numbers, for interest:
  for(int i = 0; i < 20; i++)
    is.push(fibonacci(i));
  // Pop & print them:
  for(int k = 0; k < 20; k++)
    cout << is.pop() << endl;
  
  IntStack<string> st;
  // Add some Fibonacci numbers, for interest:
  for(int i = 0; i < 19; i++)
    st.push("1");
  st.push("2");
  // Pop & print them:
  for(int k = 0; k < 20; k++)
    cout << st.pop() << endl;

  return 0;
}