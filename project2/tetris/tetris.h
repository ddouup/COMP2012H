#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include <vector>
using namespace std;
typedef vector<int> Line;

class Block;
class MainWindow;
class TetrisManager;
#include "block.h"
#include "tetrismanager.h"


class Tetris {
 public:
  TetrisManager *myManager;
  Tetris(vector<Line>*,Block*&);
  //old//vector<Line>*  getBoard(); 
  bool notOver; //if the game is over
  bool started; //if the game has started
  bool drop(); //
    void addToBoard(); // add cur_block to tBoard

  vector<Line>* board;
  vector<pair<int,int> >* block_loc;
  
  int nextColor; //cache for the next block's color
  int combo;

private:
  Block **cur_block;
  //old//vector<Line> tBoard;// tetris game board(vector of rows)
  bool dropping;
  int elimLine(); //eliminate full line
    int ranBlock();// ran gen a type (1~7)
  void zero(int); // set line to 0
};

#endif 
