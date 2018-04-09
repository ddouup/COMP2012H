#ifndef POINT_H
#define POINT_H

#include <QtGui>
#include <iostream>
using namespace std;

class point {
public:
	point();
	point(int, int);
	~point();

	void setX(int);
	void setY(int);
	int getX() const;
	int getY() const;
	
	void draw(QPainter* painter, int left_x, int bottom_y, double scale_x, double scale_y) const;
	void drawTo(const point& p, QPainter* painter, int left_x, int bottom_y, double scale_x, double scale_y) const;

	double getSlope(const point&);

	bool operator==(const point& ) const;
	bool operator!=(const point& ) const;
	bool operator<(const point& ) const;
	bool operator>(const point& ) const;
	friend ostream& operator<<(ostream& out, const point& p);

private:
	int x;
	int y;
};



#endif