// Copyright 2015 Tammo Behrends

#ifndef QTHALLOWORLD_MAINWINDOW_H
#define QTHALLOWORLD_MAINWINDOW_H


#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QMenu>
#include <QAction>

#include <memory>

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
    QPixmap* pixmap_empty;

    QMenu *fileMenu;
    QMenu *settingsMenu;
    QMenu *aboutMenu;

    QAction *exitAct;
    QAction *aboutAct;

 public:
    explicit MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

 private:
    void createGameGrid();
    void clickedGamePiece(unsigned int x, unsigned int y);
    void updateGameGrid();
    void clearGameGrid();

    void createActions();
    void createMenus();

    void about();
};


#endif  // QTHALLOWORLD_MAINWINDOW_H
