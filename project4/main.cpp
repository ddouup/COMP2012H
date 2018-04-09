#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cout << "Please input a file." << endl;
		exit(0);
	}

	QApplication a(argc, argv);
	MainWindow* w = new MainWindow();
	w->loadFile(argv[1]);
	w->show();
	return a.exec();
}