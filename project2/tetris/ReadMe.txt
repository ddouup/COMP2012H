Name:Dou, Daihui
Student ID:20329361
Teammate:Fang, Haoyang




There are 4 class in this program.
	1)MainWindow:GUI Part
	2)Block:A piece of tetris
	3)Tetris:Game body
	4)TetrisManager:Functions help to manage the game and store the data for the game

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1.Block: 
Each block have the specific relative location to location of centre if type and r_state(the state of rotate direction) are known. Hence we retrieve the distribution according to the type and r_state, and then use the distribution and cenLoc to calculate block_loc.

Everytime the block moves, we only move cenLoc.

And block_loc is renewed every time the block move or rotate.
----------------------------------------------------------------------------
2.MainWindow:
GUI part is trivial.

There is a 20*10 vector representing gameboard, which stores int value as the type of the block. 0 represents no block. The location of the block means location on this board.
However, the moving block and the board is SEPARATED. The block is added to board only after it stop dropping.
And the GUI part is actually separated. The only reason the DATA of block and board are in GUI class is to make it easier to draw.

Timer: Call the func timeEndEvent every 50ms after game started. Storing the passing time in time_cache to control speed. In timeEndEvent, call drop() in tetris to perform dropping, which return a boolean value to help MainWindow judge whether the game is over. After game over, reset it.

KeyPressEvent: 
	1)press up arrow: set (bool gameStart) to true
	2)call functions in tetris manager to perform

printAll() is called every time the board or block changes to print the game board and renew labels.
----------------------------------------------------------------------------
3.Tetris:
drop() for auto dropping, return a bool value to inform whether the game is over.
elimLine() is implemented to eliminate the lines that is full and move upper lines down, and return total lines eliminated to calculate score.
and some basic functions needed by (related with) game body
----------------------------------------------------------------------------
4.TetrisManager:
PosOk() check whether the given loc in board is empty.
IfMove() Check whether the block can move to given direction.(using PosOk)
IfRotate() Check whether the block can rotate to given direction.(using PosOk, and calculate location method in Block with given centre location)
Others ifFunction using IfMove() to check. 
For moveFunction and rotate, they first check if the action is legal (using ifFunctions), and move or rotate if legal (by calling move or rotate func in class Block). And return a boolean value for success or failure.
It also stores level, speed and score and the relative functions.
