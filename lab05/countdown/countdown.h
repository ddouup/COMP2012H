#include <QWidget>
#include <QtGui>
#include <unistd.h>
#include <QLabel>
#include <qtimer.h>

#ifndef COUNTDOWN_H
#define COUNTDOWN_H

class MyMainWindow : public QWidget {
	// All classes that contain signals or slots
	// must mention Q_OBJECT in their declaration.
	Q_OBJECT

public:
	MyMainWindow(int t, QWidget* parent = 0);
	~MyMainWindow();

	public slots:
	void UpdateLabel();

private:
	int countdown;
	QLabel *myLabel;
	QVBoxLayout *mainLayout;
	QTimer *timer; // generates timer events
};

#endif