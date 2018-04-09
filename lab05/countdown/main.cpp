#include <QtGui>
#include <QLabel>
#include <unistd.h>
#include "countdown.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QWidget* w = new MyMainWindow(atoi(argv[1]));
	w->show();
	return a.exec();
};