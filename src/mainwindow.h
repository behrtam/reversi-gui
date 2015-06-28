// Copyright 2015 Tammo Behrends

#ifndef QTHALLOWORLD_MAINWINDOW_H
#define QTHALLOWORLD_MAINWINDOW_H


#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QSound>

#include <memory>

#include "./reversi_game.h"
#include "./clickablelabel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

 private:
    QWidget* center;
    QGridLayout* grid_layout;

    QWidget *sidebar;
    QHBoxLayout* boxLayout;

    std::unique_ptr<ReversiGame> game;
    QString playername_black_;
    QString playername_white_;

    QPixmap* pixmap_black;
    QPixmap* pixmap_white;
    QPixmap* pixmap_empty;

    QMenu *fileMenu;
    QMenu *settingsMenu;
    QMenu *boardSizeMenu;
    QMenu *aboutMenu;

    QAction *newGameAct;
    QAction *exitAct;
    QAction *aboutAct;

    QActionGroup *boardSizeGroup;
    QAction *boardSize4;
    QAction *boardSize6;
    QAction *boardSize8;
    QAction *boardSize10;
    QAction *boardSize12;

    QMessageBox* resetMsgBox;

    QSound* tapped;
    QSound* timber;
    QSound* xylo;

 public:
    explicit MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    QString playername_black() const { return playername_black_; }
    void playername_black(const QString& playername) {
        if (playername.isNull() || playername.isEmpty()) return;
        playername_black_ = playername;
    }

    const QString& playername_white() const { return playername_white_; }
    void playername_white(const QString& playername) {
        if (playername.isNull() || playername.isEmpty()) return;
        playername_white_ = playername;
    }

 private:
    void createGameGrid();
    void clickedGamePiece(unsigned int x, unsigned int y);
    void updateGameGrid();
    void clearGameGrid();
    void resetGame();
    bool gameIsRunning();

    void createActions();
    void createMenus();
    void createMsgBox();

    void createSidebar();

    void about();

    void changeBoardSize(unsigned int size);
};


#endif  // QTHALLOWORLD_MAINWINDOW_H
