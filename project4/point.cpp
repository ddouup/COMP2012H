#include "point.h"
using namespace std;

point::point(){}
point::~point(){}
point::point(int a, int b) :x(a), y(b) {}

void point::setX(int a) { x = a; }
void point::setY(int b) { y = b; }
int point::getX() const { return x; }
int point::getY() const { return y; }

void point::draw(QPainter* painter, int left_x, int bottom_y, double scale_x, double scale_y) const {
	painter->setBrush(Qt::black);
	painter->setPen(Qt::black);
	painter->drawEllipse(QPointF(left_x + scale_x * x, bottom_y - scale_y * y), 2, 2);
}

void point::drawTo(const point& p, QPainter* painter, int left_x, int bottom_y, double scale_x, double scale_y) const {
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(QColor(0, 0, 0));
	painter->drawLine(QPointF(left_x + scale_x * x, bottom_y - scale_y * y), QPointF(left_x + scale_x * p.x, bottom_y - scale_y * p.y));
}

double point::getSlope(const point& p){
	if (x == p.getX()) {
		return 1e10;
	}
	
	double slope = ((double)y - (double)p.getY()) / ((double)x - (double)p.getX());
	
	return slope;
}

bool point::operator==(const point& p) const {
	return x == p.getX() && y == p.getY();
}

bool point::operator!=(const point& p) const {
	return !(*this == p);
}

bool point::operator<(const point& p) const {
	if (*this == p) {
		return false;
	}
	else if (x == p.getX()) {
		return y < p.getY();
	}
	else {
		return x < p.getX();
	}
}

bool point::operator>(const point& p) const {
	if (*this == p) {
		return false;
	}
	else if (x == p.getX()) {
		return y > p.getY();
	}
	else {
		return x > p.getX();
	}
}

ostream& operator<<(ostream& out, const point& p){
	out << " (" << p.x << ", " << p.y << ") ";
	return out;
}