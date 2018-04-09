#ifndef BRUTE_H
#define BRUTE_H

#include <vector>
#include <iostream>
#include "point.h"
using namespace std;

class brute {
public:
	brute();
	brute(const vector<point>);
	~brute();
	
	void print(vector<vector<point> > );
	vector<vector<point> > searchColinearPoints();
	
private:
	bool check(int, int, int, int);
	vector<point> points;
};

#endif