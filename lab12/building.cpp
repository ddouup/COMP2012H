#define MY_NAME "My name"

//building.cpp

#include <iostream>  //Library file so uses <>
#include "building.h"      //User Defined so uses ""

using namespace std;

#define NUM_OF_FLOOR 3
#define NUM_OF_ROOM 5

building::building()
: names(NUM_OF_FLOOR, vector<string>(NUM_OF_ROOM)),
  ids(NUM_OF_FLOOR, vector<string>(NUM_OF_ROOM))
{
}

building::building(const char theName[], const char theID[])
: names(NUM_OF_FLOOR, vector<string>(NUM_OF_ROOM)),
  ids(NUM_OF_FLOOR, vector<string>(NUM_OF_ROOM)) //... initialize names & ids
{
  this -> names[0][0] = theName;
  this -> ids[0][0] = theID;//... at floor 0, room 0, ...
}

void building::Put(const char s[], const char ID[], int f, int n)
{
  if (IsValid(f, n)){//... check if f and n are valid
	this -> names[f][n] = s;
	this -> ids[f][n] = ID;//... update the room info
  }
}

void building::Empty(int f, int r)
{
  names[f][r] = " ";
  ids[f][r] = " ";//... empty the floor f, room r
}

void building::Display(int f, int r)
{
  if (IsValid(f, r)) {
    if (names[f][r] == "")
    {
      cout << "Room " << r << " on floor " << f << " is empty" << endl;
    }
    else 
    {
      cout << "Occupant of Room " << r << " on floor " << f;
      cout << " is " << names[f][r];
      cout << ", Identity number "  << ids[f][r] << endl;
    }
  }
}

void building::Display(int f)
{
  if (IsValidFloor(f)) {
    int nonEmptyRoom = 0;
    
    for(int r = 0; r < NUM_OF_ROOM; r++) {
      if (names[f][r] != "")
      {
        nonEmptyRoom++;
        cout << "Occupant of Room " << r << " on floor " << f;
        cout << " is " << names[f][r];
        cout << ", Identity number "  << ids[f][r] << endl;
      }
    }

    if (nonEmptyRoom == 0)
      cout << "Floor " << f << " is empty" << endl;
  }
}

void building::Display()
{
  int nonEmptyRoom = 0;
  for (int f = 0; f < NUM_OF_FLOOR; f++) {
    for(int r = 0; r < NUM_OF_ROOM; r++) {
      if (names[f][r] != "")
      {
        nonEmptyRoom++;
        cout << "Occupant of Room " << r << " on floor " << f;
        cout << " is " << names[f][r];
        cout << ", Identity number "  << ids[f][r] << endl;
      }
    }
  }
  if (nonEmptyRoom == 0)
    cout << "The building is empty" << endl;
}

int building::Vacancies(int f) const
{
  if (IsValidFloor(f)) {//... check f is valid
	int EmptyRoom = 0;//... count the number of empty rooms at floor f
	for(int r = 0; r < NUM_OF_ROOM; r++) {
		if (names[f][r] == "")
		  EmptyRoom ++;
	}
	return EmptyRoom;
  }  
 }

int building::Vacancies() const
{ 
  int EmptyRoom = 0;
  for (int f = 0; f < NUM_OF_FLOOR; f++){//... count the number of empty rooms in the whole building
	EmptyRoom += Vacancies(f);
  }
  return EmptyRoom;
}

ostream& operator<<(ostream& os, const building& b) 
{
  for (int f = 0; f < NUM_OF_FLOOR; f++) {
	for(int r = 0; r < NUM_OF_ROOM; r++) {
	cout << b.names[f][r] << " ";//... print out the names separated with a space (i.e. ' ')
	}
  }
}

bool operator==(const building& b1, const building& b2)
{
  return b1.Vacancies() == b2.Vacancies();
}

void building::Identify_Writer()
{
  cout << MY_NAME << "\t12345678\t1\t1A" << endl;
}

bool building::IsValidFloor(int f) const {
  bool valid = ((0 <= f) && (f < NUM_OF_FLOOR));
  if (! valid) {
    cerr << "Floor " << f << " is out of range!\n";
  }
  return valid;
};

bool building::IsValidRoom(int r) const {
  bool valid = ((0 <= r) && (r < NUM_OF_ROOM));
  if (! valid) {
    cerr << "Room " << r << " is out of range!\n";
  }
  return valid;
};

bool building::IsValid(int f, int r) const {
  return IsValidFloor(f) && IsValidRoom(r);
};
