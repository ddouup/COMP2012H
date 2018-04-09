#include <iostream>
#include <vector>
#include "block.h"
#include "tetrismanager.h"
using namespace std;
typedef pair<int,int> Loc;

TetrisManager::TetrisManager( vector<Line>* board) {
  tBoard = board;
  score = 0;
  level = 1;
  set_speed();
}

  void TetrisManager::set_level() {
  level = (score < 900) ? (score/100)+1 : 10;
}

  void TetrisManager::set_speed() {
  speed = 1000 - (level - 1)*100;
}

  void TetrisManager::addScore(int incr) {
  score += 10*incr*incr;
  set_level();
  set_speed();
}

  bool TetrisManager::posOK(int x, int y) {
  return (  x < 10 && x >= 0 && y < 20
            && (*tBoard)[y][x] == 0)   ? true : false;
}

bool TetrisManager::ifFull(int lnNo) {
  for (int x = 0; x < 10; x++)
    if ((*tBoard)[lnNo][x] == 0)
      return false;
    
  return true;  
}

bool TetrisManager::ifMove( Block *cur_block, int y_incr, int x_incr) {
  vector<Loc> *loc = cur_block->block_loc;
  for (int i = 0; i < 4; i++) 
    if (!posOK((*loc)[i].first + x_incr, 
               (*loc)[i].second + y_incr))
      return false;
  return true;  
}

  bool TetrisManager::ifOver( Block *cur_block) {
  return (ifMove(cur_block,0,0)) ? false: true;
}

  bool TetrisManager::ifDown(Block *cur_block) {
  return (ifMove(cur_block,1,0)) ? true: false;
}

  bool TetrisManager::ifLeft(Block *cur_block) {
  return (ifMove(cur_block,0,-1)) ? true: false;
}

  bool TetrisManager::ifRight(Block *cur_block) {
  return (ifMove(cur_block,0,1)) ? true: false;
}

  bool TetrisManager::moveDown(Block *cur_block) {
  if(ifDown(cur_block)) {
    cur_block->moveBlock(0,1);
    return true;
  }
  else return false;
}

  void TetrisManager::moveLeft(Block *cur_block) {
  if(ifLeft(cur_block)) cur_block->moveBlock(-1,0);
}

  void TetrisManager::moveRight(Block *cur_block) {
  if(ifRight(cur_block)) cur_block->moveBlock(1,0);
}

bool TetrisManager::ifRotate(Block *cur_block, bool dire) {
  //block loc after changed
  vector<Loc> block_loc(4);
  //rotate dire
  int state_incr((dire)?1:-1);
  cur_block->setLoc(&block_loc, (cur_block->get_state() + state_incr+4)%4);
  for(int i = 0; i < 4; i++) 
    if (!posOK(block_loc[i].first,block_loc[i].second))
      return false;
  return true;  
}

  void TetrisManager::rotate(Block *cur_block, bool dire) {
  if (ifRotate(cur_block,dire)) cur_block->change_state(dire);
}