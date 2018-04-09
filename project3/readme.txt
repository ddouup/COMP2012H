/**********************************************************************

 *  Randomized Queues and Deques

 **********************************************************************/


Name:
 DOU Daihui
ID:
 20329361
Login: ddou

Hours to complete assignment (optional):



/**********************************************************************

 *  Explain briefly how you implemented the randomized queue and deque.

 *  Which data structure did you choose (array, linked list, etc.)

 *  and why?

 **********************************************************************/

PUT YOUR ANSWER HERE



 1. I choose doubly linked list to implement the deque. Because it's easy to add or remove elements from two ends of the doubly linked list, which precisely meet the requirement of deque.
 2. And I choose dynamic array to implement the ranomized queue. Because it's easy to get the element at a specific position in an array. After generating a random number, it can be used to get a random element in the array.



/**********************************************************************

 *  Briefly describe why any sequence of N randomized queue operations,

 *  starting from an empty randomized queue, takes O(N) time.

 **********************************************************************/

 PUT YOUR ANSWER HERE



 isEmpty(),size(): just return, O(1)
 samle(): just return, O(1)
 enqueue(): 1.double the size of the array: if an array with length N is full and we will create a 2N array and copy the data of N array, then it takes O(N) times. However, if the N array need to doubled,
	      				    there must have been N elements added so by amortized analysis, it takes O(N/N) = O(1) time.
	    2.add the element: put the item into the last position, which takes O(1) time.
 dequeue(): simply remove a random element, move the last element to its position and reduce the length, which takes O(1) time.

 So each operation is O(1) for 1 element, and for any sequence of N randomized queue operations, starting from an empty randomized queue, takes O(N) times.




/**********************************************************************

 *  Briefly describe why each Deque operation takes O(1) time.

 **********************************************************************/

 PUT YOUR ANSWER HERE

 isEmpty(),size(): just return, O(1).
 addFirst(),addLast(): both operations just add one Node to the first or the last, and move the pointers *next, *prev and *first/*last, which are irrelevent with the number of elements in the list, so it takes O(1) time.
 removeFirst(),removeLast(): similar to add operations, both two delete the first or the last Node and move the *first or the *last pointers, which are also irrelevent with the number of elements in the list, so it takes O(1) time.	
 So each Deque operation takes O(1) time.



/**********************************************************************

 *  How much memory (in bytes) does your data type use to store N items.

 *  Use tilde notation to simplify your answer. Use the memory requirements

 *  for a "typical machine" given in Lecture. In your analysis, don't include

 *  the memory for the items themselves (as this memory is allocated by

 *  the client and depends on the item type.
 
 *  For a typical machine, refer to page 11 of 

 *  https://www.cs.princeton.edu/courses/archive/spr10/cos226/lectures/02-14Analysis-2x2.pdf

 **********************************************************************/


RandomizedQueue:


overhead for object: 8 bytes
length int :4 bytes
N int  :4 bytes
q pointer:  4 bytes
totally 20 bytes


Dequeue:
overhead for object: 8 bytes
N int: 4 bytes
head Node*: 4 bytes
last Node*: 4 bytes

totally 20 bytes








/**********************************************************************

 *  Known bugs / limitations.

 **********************************************************************/



 I have fixed all the bugs that I can find.


/**********************************************************************

 *  List whatever help (if any) that you received and from whom,

 *  including help from staff members or lab TAs.

 **********************************************************************/







/**********************************************************************

 *  Describe any serious problems you encountered.                    

 **********************************************************************/
 1. It's difficult to define the Iterator of randomized queue and overload the operators because it needs to point to each one of the data in the queue without repitation. Finally I created a new array to implement the function.
 2. At first, I found it hard to correctly read the input of subset. It needs to identify the space and the elements in randomized queue have different length.







/**********************************************************************

 *  List any other comments here. Feel free to provide any feedback   
 
 *  on how much you learned from doing the assignment, and whether    
 
 *  you enjoyed doing it.                                             

 **********************************************************************/








