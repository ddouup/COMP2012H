#include <cstdlib>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Point{
  Point(int px, int py):x(px), y(py){}
  ~Point(){}
  bool operator==(const Point& p) {
    return (x == p.x && y == p.y);
  }
  int x, y;
};

void generateInput(int number, char* file_name) {
  vector<Point> points;
  int i;
  for (i = 0; i < number; i++) {
    Point p(rand() % 32768, rand() % 32768);
    if(find(points.begin(), points.end(), p) == points.end()){
      points.push_back(p);
    }
  }

  ofstream fout(file_name);
  assert (fout.is_open ());
  fout<<number<<endl;

  vector<Point>::iterator itr;
  for(itr = points.begin(); itr != points.end(); itr++) {
    fout<< itr->x <<" "<< itr->y <<endl;
  }
  fout.close();
}

int main() {
  srand(time(NULL));
  int i;

  int numbers[12]={10, 20, 40, 80, 100, 150, 200, 400, 1000, 2000, 4000, 10000};
  char* file_names[12]={"10.txt", "20.txt", "40.txt", "80.txt", "100.txt", "150.txt", "200.txt", "400.txt", "1000.txt", "2000.txt","4000.txt", "10000.txt"};

  for(i = 0; i < 12; i++) {
    generateInput(numbers[i], file_names[i]);
  }

  return 0;
}
