#ifndef TETRIS_MAINWINDOW_H
#define TETRIS_MAINWINDOW_H

class Tetris;
#include <unistd.h>
#include <QtGui>
#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include "tetris.h"
#include "block.h"


class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = 0);
  bool gameProcessing;
  vector<vector<int> > *board;
  Block *block;
  void paintAll();

public slots: void timeEndEvent();
   
protected:
  void keyPressEvent(QKeyEvent *);
  
private:
  QImage myImage;
  QImage pvImage;
  QLabel bLabel;//background
  QLabel pLabel;//preview board
  QLabel *lLabel;//level text
  QLabel *sLabel;//score text
  QVBoxLayout mainLayout;
  void setPreview();
  QBrush getColor(int);
  
  Tetris *tetris;
  bool gameStart;
  bool gameOver;
  bool gamePausing;
  void reset();

  QTimer *timer;
  int time_cache;
};

#endif
