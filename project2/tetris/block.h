#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include <vector>
#include "mainwindow.h"

using namespace std;


typedef pair<int,int> Loc; //relative location to cenLoc

class Block {
 public:
  Block(int type);
  bool dropping;
  int type; //(1~7 according to 12h homepage)
  void setLoc(vector<Loc> *loc, int r_state); //set loc according to cenLoc and distri
  Loc getStartLoc(int type);
  vector<int>* calDistri(int type,int r_state); // calculate rLoc(distri) wrt r_state
  vector<Loc>* block_loc; //relative location of all 4 bricks
  int get_state() {return r_state;};
  void moveBlock(int,int);
  void change_state(bool); 
 private:
  Loc cenLoc; //location of centre
  int r_state; //state(direction) of rotate //NEWS 0123
  
};

#endif
