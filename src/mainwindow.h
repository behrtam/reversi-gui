// Copyright 2015 Tammo Behrends

#ifndef QTHALLOWORLD_MAINWINDOW_H
#define QTHALLOWORLD_MAINWINDOW_H


#include <QMainWindow>
#include <QWidget>

#include "./reversi_game.h"
#include "./clickablelabel.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

 private:
    QWidget* center;
    std::unique_ptr<ReversiGame> game;
    QPixmap* pixmap_black;
    QPixmap* pixmap_white;

 public:
    explicit MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

 private:
    void createGameGrid();
    void clickedGamePiece(int x, int y, ClickableLabel* label);
};


#endif  // QTHALLOWORLD_MAINWINDOW_H
