#include <QtGui>

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad();

private slots:
    void open();
    void save();
    void quit();

private:
    QTextEdit *textEdit;

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QMenu *fileMenu;
};

Notepad::Notepad()
{
    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("E&xit"), this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    setWindowTitle(tr("Notepad"));
}

void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

   if (fileName != "") {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    QTextStream in(&file);
    textEdit->setText(in.readAll());
    file.close();
   }
}

void Notepad::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", 
    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
      QFile file(fileName);
      if (!file.open(QIODevice::WriteOnly)) {
          // error message
      } else {
          QTextStream stream(&file);
          stream << textEdit->toPlainText();
          stream.flush();
          file.close();
      }
    }
}

void Notepad::quit()
{
   QMessageBox messageBox;
   messageBox.setWindowTitle(tr("Notepad"));
   messageBox.setText(tr("Do you really want to quit?"));
   messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
   messageBox.setDefaultButton(QMessageBox::No);
   if (messageBox.exec() == QMessageBox::Yes)
       qApp->quit();
}
