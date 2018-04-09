#include <unistd.h>
#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <vector>
#include "block.h"
#include "mainwindow.h"
#include "tetris.h"
#include "tetrismanager.h"
using namespace std;
typedef vector<int> Line;

Tetris::Tetris(vector<Line>* w_board,Block *&w_block)
              : dropping(true) {
  notOver = true;
  started = false;
  board = w_board;
  cur_block = &w_block;
  myManager = new TetrisManager(board);//?
  nextColor = 0;
}

bool Tetris::drop() {
  if (notOver) {
    //if this is the first block of the game
    if (!started) { 
      (*cur_block) = new Block(ranBlock());
      started = true;
    }
    //if the block was still dropping
    //drop if it still can drop
    if (dropping) {
      dropping = myManager->moveDown((*cur_block));
      if(!dropping) (*cur_block)->dropping = false;
    }
    //if the block has stopped dropping
    //add it to board and delete and create a new block
    else {
      addToBoard();
      delete (*cur_block);
      (*cur_block) = new Block(ranBlock());
      dropping = true;
    }
    //check if there is a line to be eliminated
    myManager->addScore(elimLine());
  }
  //check whether the new block can be put on board
  if(myManager->ifOver((*cur_block))) notOver = false;
  //if cant, game is over
  if (!notOver) {
     delete (*cur_block);
     *cur_block = nullptr;
     return true;
  }
  else return false;
}


  void Tetris::addToBoard() {
  for (int i = 0; i < 4; i++) {
    (*board)[((*((*cur_block)->block_loc))[i]).second]
          [((*((*cur_block)->block_loc))[i]).first] = 
          (*cur_block)->type;
  }
}


int Tetris::elimLine() {
  int cnt = 0;
  for (int i = 0; i < 20; i++) 
    if (myManager->ifFull(i)) {
      cnt++;
      zero(i);
      // if it's not line 0, above line fall
      if(i != 0) {
        for (int j = i; j > 0; j--) 
          for (int k = 0; k < 10; k++)
            (*board)[j][k] = (*board)[j-1][k]; 
      }
      zero(0);
    }
  combo = cnt;
  return cnt;
}
 
void Tetris::zero (int lineNo) {
  for (int i = 0; i < 10; i++) {
    (*board)[lineNo][i] = 0;
  }
}

  int Tetris::ranBlock() {
  srand (time(NULL));
  //if this is the first block
  if (nextColor == 0) {
    nextColor = rand()%7 + 1;
  }
  //return cached color and generate next
  int temp = nextColor;
  nextColor = rand()%7 + 1;
  return temp;
}
 
 
