#include <QFrame>
#include <QLabel>
#include <qpainter.h>
#include <QStatusBar>
#include <QString>
#include <QtGui>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include <sstream>
#include <string>
#include "mainwindow.h"
#include "tetris.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
      : QMainWindow(parent) {
  gameStart = false;
  gameOver = false;
  gamePausing = true; //to disable upper arrow when not applicable
  
  
  //gui settings
  QFrame *frame = new QFrame(this);
  setCentralWidget(frame);
  
  QVBoxLayout *vbox = new QVBoxLayout();
  QHBoxLayout *hbox = new QHBoxLayout(frame);

  lLabel = new QLabel("Level: 1");
  sLabel = new QLabel("Score: 0");
  
  vbox->addStretch(1);
  vbox->addWidget(&pLabel);
  vbox->addSpacing(50);
  vbox->addWidget(lLabel);
  vbox->addWidget(sLabel);
  vbox->addStretch(1);
  
  pvImage.load("preview.bmp");
  pLabel.setPixmap(QPixmap::fromImage(pvImage));
  pLabel.show();
  
  hbox->addWidget(&bLabel);
  hbox->addSpacing(15);
  hbox->addLayout(vbox);
  
  myImage.load("background.bmp");
  bLabel.setPixmap(QPixmap::fromImage(myImage));
  bLabel.show();
  
  //give an empty board i.e. all values 0
  board = new vector<vector<int> >(20);
  for (int i = 0; i < 20; i++) {
    vector<int> l(10,0);
    (*board)[i] = l;
  }
  block = nullptr;
  
  statusBar();
  
  tetris = new Tetris(board,block);
  timer = new QTimer(this);
  QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timeEndEvent()));  
  timer->start(50);
  time_cache = 0;
  
  gamePausing = false;
}

//basic key press event
void MainWindow::keyPressEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_Up) {
      if (!gamePausing) gameStart = true;
      return;
  }
  if(event->key() == Qt::Key_Left) {
    if(block&&gameStart&&block->dropping) {
      tetris->myManager->moveLeft(block);
      paintAll();
    }
    return;
  }
  if(event->key() == Qt::Key_Right) {
    if(block&&gameStart&&block->dropping){
      tetris->myManager->moveRight(block);
      paintAll();
    }
    return;
  }
  if(event->key() == Qt::Key_Down) {
    if(block&&gameStart&&block->dropping) {
      tetris->myManager->moveDown(block);
      paintAll();
    }
    return;
  }
  if(event->key() == Qt::Key_Z) {
    if(block&&gameStart&&block->dropping) {
      tetris->myManager->rotate(block, false);
      paintAll();
    }
    return;
  }
  if(event->key() == Qt::Key_X) {
    if(block&&gameStart&&block->dropping) {
      tetris->myManager->rotate(block, true);
      paintAll();
    }
    return;
  }
  if(event->key() == Qt::Key_C) {
    if(block&&gameStart&&block->dropping) {
      tetris->nextColor = 1;
      paintAll();
      setPreview();
      statusBar()->showMessage("you cheater",1000);
    }
    return;
  }
}

//get block's color according to type
QBrush MainWindow::getColor(int type) {
  switch (type) {
    case 1: return Qt::red; 
    case 2: return Qt::green;
    case 3: return Qt::blue;
    case 4: return Qt::yellow;
    case 5: return Qt::cyan;
    case 6: return Qt::lightGray;
    case 7: return Qt::magenta;
    default: return Qt::red;
  }
}

//paint all except preview window
void MainWindow::paintAll() {
  QImage myImage;
  myImage.load("background.bmp");
  QPainter p(&myImage);
  p.setBrush(Qt::NoBrush);
  QPen pen(Qt::black, 2);
  p.setPen(pen);
  //paint the moving block
  if (block) {
    for (int i = 0; i < 4; i++) {
      QPainterPath path;
      int x = (*(block->block_loc))[i].first;
      int y = (*(block->block_loc))[i].second;
      path.addRect(20*x, 20*y, 20, 20);
      p.fillPath(path, getColor(block->type));
      p.drawPath(path);
    }
  }
  //paint the board
  if (board) {
    for (int ln = 0; ln < 20; ln++) 
      for (int x = 0; x < 10; x++) {
        QPainterPath path;
        int type = (*board)[ln][x];
        if(type == 0) continue;
        path.addRect(20*x, 20*ln, 20, 20);
        p.fillPath(path, getColor(type));
        p.drawPath(path);
      }
  }
  //edit text in labels
  QString level = "Level: ";
  QString temp = QString::number(tetris->myManager->get_level());
  level.append(temp);
  QString score = "Score: ";
  temp = QString::number(tetris->myManager->get_score());
  score.append(temp);
  lLabel->setText(level);
  sLabel->setText(score);
  
  bLabel.setPixmap(QPixmap::fromImage(myImage));
}

//set preview window with corresponding image
void MainWindow::setPreview(){
  int color = tetris->nextColor;
  QImage pImage;
  switch (color) {
    case 1: pImage.load("preview1.bmp"); break;
    case 2: pImage.load("preview2.bmp"); break;
    case 3: pImage.load("preview3.bmp"); break;
    case 4: pImage.load("preview4.bmp"); break;
    case 5: pImage.load("preview5.bmp"); break;
    case 6: pImage.load("preview6.bmp"); break;
    case 7: pImage.load("preview7.bmp"); break;
    default: break;
  }
  pLabel.setPixmap(QPixmap::fromImage(pImage));
  pLabel.show();
}

void MainWindow::timeEndEvent() {
  //check if game has started
  if(gameStart) {
    //if so, increase time cache
    time_cache += 50;
    //and get current speed(time interval)
    int speed = tetris->myManager->get_speed();
    //if reach the interval, auto dropping 1 unit down
    if(time_cache >= speed) {
      time_cache -= speed; //renew time cache
      gameOver = tetris -> drop();
      
      //print combo on statusbar
      if (tetris->combo != 0) {
        QString temp("COMBO: ");
        QString tempi = QString::number(tetris->combo);
        temp.append(tempi);
        statusBar()->showMessage(temp,3000);
        tetris->combo = 0;
      }
      
      //if game is not over, renew GUI
      //else reset game
      if(!gameOver) {
        paintAll();
        setPreview();
      }
      else reset();
      
    }
  }
}

//trivial reset procedure
void MainWindow::reset(){
  gameStart = false;
  gameOver = false;
  
  gamePausing = true;
  statusBar()->showMessage("GAME END",8000);
  
  lLabel->setText("Level: 1");
  sLabel->setText("Score: 0");
  
  pvImage.load("preview.bmp");
  pLabel.setPixmap(QPixmap::fromImage(pvImage));
  
  myImage.load("background.bmp");
  bLabel.setPixmap(QPixmap::fromImage(myImage));
  
  delete board;
  board = new vector<vector<int> >(20);
  for (int i = 0; i < 20; i++) {
    vector<int> l(10,0);
    (*board)[i] = l;
  }
  
  block = nullptr;
  
  delete tetris;
  tetris = new Tetris(board,block);
  
  time_cache = 0;
  
  gamePausing = false;
}
