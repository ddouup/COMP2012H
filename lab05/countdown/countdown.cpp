using namespace std;
#include "countdown.h"
#include <QApplication>
#include <QLabel>

MyMainWindow::MyMainWindow(int t, QWidget* parent): QWidget(parent)
{ 
	countdown = t;
	myLabel = new QLabel("countdown");
	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(myLabel);
	setLayout(mainLayout);
	myLabel->setNum(countdown);
	myLabel->show();
	// create a timer to change the image display position.
	// note: timer should be destroyed automatically here,
	// and MyMainWindow's destructor is not required.
	// reference: http://doc.trolltech.com/3.2/qtimer.html
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(UpdateLabel()));
	// start to generate timer events
	timer->start(1000 /* milliseconds */);
}

MyMainWindow::~MyMainWindow()
{
	delete myLabel;
}

void MyMainWindow::UpdateLabel()
{	
	if (countdown > 0) {
		countdown--;
		myLabel->setNum(countdown);
		myLabel->show();
	}
	
}