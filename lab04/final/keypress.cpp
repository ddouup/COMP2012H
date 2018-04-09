#include "keypress.h"
#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
 
KeyPress::KeyPress(QWidget *parent) :
	QWidget(parent), x(0)
{
	myLabel = new QLabel("Step");
	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(&myLabel1);
	mainLayout->addWidget(myLabel);
	
	setLayout(mainLayout);
	myImage.load("penguin.png");
	myLabel1.setPixmap(QPixmap::fromImage(myImage));
	myLabel1.show();
}
 
void KeyPress::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
		x++;
		QPainter qPainter(&myImage);
		qPainter.setBrush(Qt::NoBrush);
		qPainter.setPen(Qt::red);
		qPainter.drawRect(250 - x, 150, 50, 50);
		myLabel1.setPixmap(QPixmap::fromImage(myImage));
		myLabel1.show();
		myLabel->setNum(x);
		myLabel->show();
    }
}

void KeyPress::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
		myImage.load("penguin.png");
		myLabel1.setPixmap(QPixmap::fromImage(myImage));
		myLabel1.show();
    }
}
