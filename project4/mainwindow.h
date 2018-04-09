#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <vector>
#include "brute.h"
#include "fast.h"
#include "point.h"
using namespace std;

const int WIDTH = 600;
const int HEIGHT = 600;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	//default constructor and destructor.
	MainWindow();
	~MainWindow();

	//load file from the txt and store the point as Point instances in points.
	void loadFile(char *);

	public slots:
	void Exit();
	void Brute();
	void Fast();

	void drawPoints(const vector<point>&);
	void drawLines(const vector<vector<point> >&);

private:
	vector<point> points;
	void repaint();

	int left_x, bottom_y;
	double scale_x, scale_y;

	QMenuBar* bar;
	QMenu* menu;

	QAction* actbrute;
	QAction* actfast;
	QAction* actexit;

	QLabel* board;
	QImage* background;
	QPainter* painter;

};


#endif