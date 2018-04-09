/**********************************************************************
 *  Pattern Recognition readme.txt template
 **********************************************************************/

Name: DOU Daihui     
Login: ddou 
Hours to complete assignment (optional):



/**********************************************************************
 *  Step 1.  Explain briefly how you implemented brute force.
 *           What method(s) did you add to the Point data type?
 **********************************************************************/
Obtain every combination of four points and check whether they are colinear.
They are colinear if the slope of each two points are equal.

I add a getSlope() function in point to calculate the slope of two points.

/**********************************************************************
 *  Step 2.  Explain briefly how you implemented the sorting solution.
 *           Did you sort by angle, slope, or something else?
 *           What method(s) did you add to the Point data type?
 *           What steps did you do to print a minimal representation?
 **********************************************************************/
I just used getSlope() but no other methods.

Select every point as origin in sequence. Sort other points by the slope with this origin.
The points are colinear if there are more than 3 equal slops. 
Check if the line has already been printed and decide to print it or not.



/**********************************************************************
 *  Empirical    Fill in the table below with actual running times in
 *  Analysis     seconds when reasonable (say 180 seconds or less).
 *               You can round to the nearest tenth of a second.
 **********************************************************************/

      N       brute       sorting
---------------------------------
     10		1ms		1ms
     20		1ms		1ms
     40		5ms		2ms
     80		36ms		3ms
    100		90ms		4ms
    150		460ms		8ms
    200		1424ms		20ms
    400		23145ms		39ms
   1000		***		283ms
   2000		***		1230ms
   4000		***		5350ms
  10000		***		36666ms


/**********************************************************************
 *  Estimate how long it would take to solve an instance of size
 *  N = 1,000,000 for each of the two algorithms using your computer.
 **********************************************************************/
Brute:28489266 year
Sorting:10000 hour



/**********************************************************************
 *  Theoretical   Give the worst-case running time of your programs
 *  Analysis      as a function of N. Justify your answer briefly.
 **********************************************************************/
Brute: It uses 4 nested loops to find colinear points, which takes O(N^4).
Sorting: It takes O(N^2) for quicksort in worst-case. And it takes O(N^3) in total for N points.



/**********************************************************************
 *  Known bugs / limitations. For example, if your program prints
 *  out different representations of the same line segment when there
 *  are 5 or more points on a line segment, indicate that here.
 **********************************************************************/



/**********************************************************************
 *  List whatever help (if any) that you received. Be specific with
 *  the names of lab TAs, classmates, or course staff members.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/




/**********************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on how much you learned from doing the assignment, and whether    
 *  you enjoyed doing it.                                             
 **********************************************************************/


