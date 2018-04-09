#include <QtGui>
#include "notepad.h"

int main(int argv, char **args)
{
  // use the identical main program in notepad_1
  QApplication app(argv, args);

    Notepad *textEdit = new Notepad;
    //QPushButton *quitButton = new QPushButton("&Quit");

    //QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    //layout->addWidget(quitButton);

    QWidget window;
    window.setLayout(layout);

    window.show();

    return app.exec();
}

