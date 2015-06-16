// Copyright 2015 Tammo Behrends

#ifndef QTHALLOWORLD_MAINWINDOW_H
#define QTHALLOWORLD_MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>

#include "./reversi_game.h"
#include "./clickablelabel.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

 private:
    QWidget* center;
    QGridLayout* grid_layout;
    std::unique_ptr<ReversiGame> game;
    QPixmap* pixmap_black;
    QPixmap* pixmap_white;

 public:
    explicit MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

 private:
    void createGameGrid();

    void clickedGamePiece(unsigned int x, unsigned int y);

    void updateGameGrid();
};


#endif  // QTHALLOWORLD_MAINWINDOW_H
