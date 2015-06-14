// Copyright 2015 Tammo Behrends

#ifndef QTHALLOWORLD_MAINWINDOW_H
#define QTHALLOWORLD_MAINWINDOW_H


#include "./reversi_game.h"

#include <QMainWindow>
#include <QWidget>


class MainWindow : public QMainWindow {
 Q_OBJECT

 private:
    QWidget* center;
    std::unique_ptr<ReversiGame> game;
    QPixmap* pixmap_black;
    QPixmap* pixmap_white;

 public:
    MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

 private:
    void createGameGrid();
};


#endif  // QTHALLOWORLD_MAINWINDOW_H
