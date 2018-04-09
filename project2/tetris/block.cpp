#include <iostream>
#include "block.h"
#include "mainwindow.h"

using namespace std;
typedef pair<int,int> Loc;


Block::Block(int tp) : type(tp), block_loc(new vector<Loc>(4)),cenLoc(getStartLoc(tp)), r_state(0) {
  setLoc(block_loc, r_state);
  dropping = true;
}


 vector<int>* Block::calDistri(int type, int r_state) {
	switch(type) {
		case 1 :
		{
			switch(r_state) {
				case 0 :
					return new vector<int>({0,-2,0,-1,0,1});
        case 1 :
          return new vector<int>({-1,0,1,0,2,0});
        case 3 :
          return new vector<int>({-2,0,-1,0,1,0});
        case 2 :
          return new vector<int>({0,-1,0,1,0,2});
        default:
          cerr << "type out of range" << r_state << endl;
          return  new vector<int>({0,-2,0,-1,0,1});;
      }
    }
    case 2 :
    {
      switch(r_state) {
        case 0 :
          return new vector<int>({-1,0,-1,1,0,1});
        case 1 :
          return new vector<int>({-1,-1,0,-1,-1,0});
        case 3 :
          return new vector<int>({1,0,0,1,1,1});
        case 2 :
          return new vector<int>({0,-1,1,-1,1,0});
        default:
          cerr << "type out of range" << r_state << endl;
          return new vector<int>({-1,0,-1,1,0,1});
      }
    }
    case 3 :
    {
      switch(r_state) {
        case 0 :
          return new vector<int>({0,-1,1,0,1,1});
        case 1 :
          return new vector<int>({1,0,-1,1,0,1});
        case 3 :
          return new vector<int>({0,-1,1,-1,-1,0});
        case 2 :
          return new vector<int>({-1,-1,-1,0,0,1});
        default:
          cerr << "type out of range" << r_state << endl;
          return new vector<int>({0,-1,1,0,1,1});
      }
    }
    case 4 :
    {
      switch(r_state) {
        case 0 :
          return new vector<int>({1,-1,1,0,0,1});
        case 1 :
          return new vector<int>({-1,0,0,1,1,1});
        case 3 :
          return new vector<int>({-1,-1,0,-1,1,0});
        case 2 :
          return new vector<int>({0,-1,-1,0,-1,1});
        default:
          cerr << "type out of range" << r_state << endl;
          return new vector<int>({1,-1,1,0,0,1});
      }
    }
    case 5 :
    {
      switch(r_state) {
        case 0 :
          return new vector<int>({0,-1,0,1,1,1});
        case 1 :
          return new vector<int>({-1,0,1,0,-1,1});
        case 3 :
          return new vector<int>({1,-1,-1,0,1,0});
        case 2 :
          return new vector<int>({-1,-1,0,-1,0,1});
        default:
          cerr << "type out of range"<< r_state << endl;
          return new vector<int>({0,-1,0,1,1,1});
      }
    }
    case 6 :
    {
      switch(r_state) {
        case 0 :
          return new vector<int>({0,-1,-1,1,0,1});
        case 1 :
          return new vector<int>({-1,-1,-1,0,1,0});
        case 3 :
          return new vector<int>({-1,0,1,0,1,1});
        case 2 :
          return new vector<int>({0,-1,1,-1,0,1});
        default:
          cerr << "type out of range" << r_state<< endl;
          return new vector<int>({0,-1,-1,1,0,1});
      }
    }      
    case 7 :
    {
      switch(r_state) {
        case 0 :
          return new vector<int>({0,-1,-1,0,1,0});
        case 1 :
          return new vector<int>({0,-1,1,0,0,1});
        case 3 :
          return new vector<int>({0,-1,-1,0,0,1});
        case 2 :
          return new vector<int>({-1,0,1,0,0,1});
        default:
          cerr << "type out of range"<< r_state << endl;
          return new vector<int>({0,-1,-1,0,1,0});
      }
    }
    default:
      cerr << "typecase out of range" << endl;
      return nullptr;
      break;
  }
}


Loc Block::getStartLoc(int type) {
  switch(type) {
    case 1 : return make_pair(4,2);
    case 2 : return make_pair(5,0);
    case 3 : return make_pair(4,1);
    case 4 : return make_pair(4,1);
    case 5 : return make_pair(4,1);
    case 6 : return make_pair(5,1);
    case 7 : return make_pair(4,1);
    default : return make_pair(4,4);
  }
}

void Block::setLoc(vector<Loc> *block_loc, int r_state) {
   vector<int>* distri = calDistri(type, r_state);
  (*block_loc)[0] = cenLoc;
  for(int i = 1; i < 4; i++) 
    (*block_loc)[i] = make_pair((*distri)[2*i-2]+cenLoc.first, (*distri)[2*i-1]+cenLoc.second);
}

//after move centre, renew loc
void Block::moveBlock(int x, int y) {
  cenLoc.first += x;
  cenLoc.second += y;
  setLoc(block_loc, r_state);
}

//after move centre, renew loc
void Block::change_state(bool clock) {
  if (clock)
    r_state = (r_state + 1 + 4)%4;
  else 
    r_state = (r_state - 1 + 4)%4;
  setLoc(block_loc, r_state);
}


