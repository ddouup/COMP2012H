#ifndef TETRIS_TETRISMANAGER_H
#define TETRIS_TETRISMANAGER_H

#include <vector>
#include "block.h"

using namespace std;
typedef vector<int> Line;

class TetrisManager {
 public:
  TetrisManager( vector<Line> *);
  vector<Line> *tBoard;//game board
    bool ifDown(Block *);
    bool moveDown(Block *);
    bool ifLeft(Block *);
    void moveLeft(Block *);
    bool ifRight(Block *);
    void moveRight(Block *);
  bool ifRotate(Block *,bool); // true means clockwise
    void rotate(Block *, bool); // true means clockwise
  bool ifFull(int);// check if line is full
    bool ifOver( Block*);//if no space left for new block
  int get_speed() { return speed; };
  int get_level() { return level; };
  int get_score() { return score; };
    void addScore(int incr);
 private:
  int speed;//unit: ms
  int level;
  int score;
  bool ifMove( Block*,int,int);
    void set_level();
    void set_speed();
    bool posOK(int x,int y); //check whether (x,y) is OK
}; 

#endif
