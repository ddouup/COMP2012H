#ifndef KEYPRESS_H
#define KEYPRESS_H
 
#include <QWidget>
#include <QtGui>
#include <unistd.h>
#include <QLabel>
 
class KeyPress : public QWidget
{
	Q_OBJECT
public:
	KeyPress(QWidget *parent = 0);
    
protected:
	void keyPressEvent(QKeyEvent *);
	void keyReleaseEvent(QKeyEvent *);

private:
	QLabel *myLabel;
	QVBoxLayout *mainLayout;

	QImage myImage;
	QLabel myLabel1;

	int x;
};
 
#endif // KEYPRESS_H
