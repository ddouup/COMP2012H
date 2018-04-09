#ifndef FAST_H
#define FAST_H

#include "point.h"
#include <iostream>
#include <vector>
using namespace std;

struct Slope {
	Slope(point x) : x(x) {}
	double operator()(point y, point z) const { return y.getSlope(x) < z.getSlope(x); }
private:
	point x;
};

class fast {
public:
	fast();
	fast(const vector<point>);
	~fast();
	
	void print(vector<vector<point> > );
	vector<vector<point> > searchColinearPoints();
private:
	vector<point> points;
};

#endif