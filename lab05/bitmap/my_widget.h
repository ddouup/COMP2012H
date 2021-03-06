#include <q3mainwindow.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <qtimer.h>
//Added by qt3to4:
#include <QPaintEvent>

#ifndef _MY_WIDGET_H
#define _MY_WIDGET_H

class MyMainWindow: public Q3MainWindow {
	// All classes that contain signals or slots
	// must mention Q_OBJECT in their declaration.
	Q_OBJECT

	public:
	MyMainWindow(QWidget* parent = 0, const char* name = 0);
	~MyMainWindow();

	/** paint handler */
	void paintEvent(QPaintEvent *);

	public slots:
	void UpdateImagePosition();

	private:
	QPixmap* image;
	int x;
	int y;
	QTimer *timer; // generates timer events
};

#endif
