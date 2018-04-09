#include "mainwindow.h"
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <QTimer>
#include <QMessageBox>
#include <QString>
using namespace std;

MainWindow::MainWindow() :left_x(0), bottom_y(HEIGHT), scale_x(WIDTH / 32768.0), scale_y(HEIGHT / 32768.0) 
{
	bar = this->menuBar();
	menu = bar->addMenu(tr("File"));

	actbrute = new QAction(tr("Load brute algo"), this);
	actfast = new QAction(tr("Load fast algo"), this);
	actexit = new QAction(tr("Exit"), this);

	menu->addAction(actbrute);
	menu->addAction(actfast);
	menu->addSeparator();
	menu->addAction(actexit);

	connect(actexit, SIGNAL(triggered()), this, SLOT(Exit()));
	connect(actfast, SIGNAL(triggered()), this, SLOT(Fast()));
	connect(actbrute, SIGNAL(triggered()), this, SLOT(Brute()));

	board = new QLabel();
	background = new QImage(WIDTH, HEIGHT, QImage::Format_RGB32);
	painter = new QPainter(background);
	
	board->setMinimumSize(50, 50);
	board->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	board->setScaledContents(true);
	board->setPixmap(QPixmap::fromImage(*background));
	board->show();
	repaint();
	setCentralWidget(board);
}

MainWindow::~MainWindow() {
	delete actexit;
	delete actbrute;
	delete actfast;
	delete board;
	delete background;
	delete painter;
}

void MainWindow::loadFile(char * file_name) {
	ifstream fin(file_name);
	assert(fin.is_open());
	int size;
	fin >> size;

	int x, y;

	while (!fin.eof()) {
		fin >> x;
		fin >> y;
		point p(x, y);

		if (points.size() > 1) {
			if (std::find(points.begin(), points.end(), p) != points.end()) {
			}
			else {
				points.push_back(p);
			}
		}
		else {
			points.push_back(p);
		}
	}
	fin.close();
	drawPoints(points);
}

void MainWindow::Exit() {
	this->close();
}

void MainWindow::Brute() {
	QTime t;
	QMessageBox msg_box;
	t.start();
	brute p(points);
	vector<vector<point> > lines = p.searchColinearPoints();
	drawLines(lines);
	msg_box.setText(QString("Time used: %1 ms  ").arg(t.elapsed()));
	msg_box.exec();
}

void MainWindow::Fast() {
	QMessageBox msg_box;
	QTime t;
	t.start();
	fast p(points);
	vector<vector<point> > lines = p.searchColinearPoints();
	drawLines(lines);
	msg_box.setText(QString("Time used: %1 ms  ").arg(t.elapsed()));
	msg_box.exec();
}

void MainWindow::drawPoints(const vector<point>& p) {
	vector<point>::const_iterator itr;
	for (itr = p.begin(); itr != p.end(); itr++) {
		itr->draw(painter, left_x, bottom_y, scale_x, scale_y);
	}
	board->setPixmap(QPixmap::fromImage(*background));
	board->show();
}

void MainWindow::drawLines(const vector<vector<point> >& p) {
	vector<vector<point> >::const_iterator out_itr;
	vector<point>::const_iterator in_itr;
	for (out_itr = p.begin(); out_itr != p.end(); out_itr++) {
		for (in_itr = out_itr->begin(); in_itr + 1 != out_itr->end(); in_itr++) {
			in_itr->drawTo(*(in_itr + 1), painter, left_x, bottom_y, scale_x, scale_y);
		}
	}
	board->setPixmap(QPixmap::fromImage(*background));
	board->show();
}

void MainWindow::repaint() {
	painter->setBrush(Qt::white);
	painter->drawRect(0, 0, WIDTH, HEIGHT);
	board->setPixmap(QPixmap::fromImage(*background));
	board->show();
}