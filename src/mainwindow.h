// Copyright 2015 Tammo Behrends

#ifndef REVERSI_MAINWINDOW_H
#define REVERSI_MAINWINDOW_H


#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QSound>
#include <QCloseEvent>
#include <QSqlTableModel>
#include <QDateTime>

#include <memory>

#include "./reversi_game.h"
#include "./clickablelabel.h"
#include "./interface_reversi_player.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

 private:
    QWidget* center;
    QGridLayout* grid_layout;

    QWidget *sidebar;
    QHBoxLayout* boxLayout;

    std::unique_ptr<ReversiGame> game;
    IReversiPlayer *black;
    QString playername_black_;
    QString playername_white_;

    QPixmap* pixmap_black;
    QPixmap* pixmap_white;
    QPixmap* pixmap_empty;
    QPixmap* pixmap_white_light;
    QPixmap* pixmap_black_light;

    QMenu *fileMenu;
    QMenu *settingsMenu;
    QMenu *boardSizeMenu;
    QMenu *blackPlayereMenu;
    QMenu *highScoreMenu;
    QMenu *aboutMenu;

    QAction *newGameAct;
    QAction *loadAct;
    QAction *saveAct;
    QAction *clearAct;
    QAction *exitAct;
    QAction *aboutAct;

    QActionGroup *boardSizeGroup;
    QAction *boardSize4;
    QAction *boardSize6;
    QAction *boardSize8;
    QAction *boardSize10;
    QAction *boardSize12;

    QActionGroup *blackPlayerGroup;
    QAction *blackHuman;
    QAction *blackRandom;

    QAction *startingPlayer;

    QAction *scoreClearAct;

    QMessageBox* resetMsgBox;
    QSqlTableModel *model;

    QDateTime game_start;
    QDateTime game_end;

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

 protected:
    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;

 private:
    void createGameGrid();
    void updateGameGrid();
    void clearGameGrid();

    void clickedGamePiece(unsigned int x, unsigned int y);
    bool gameIsRunning();

    void resetGame();
    void changeBoardSize(unsigned int size);

    void createActions();
    // QAction* createBoardSizeAction(unsigned int boardSizeNumber);
    void createMenus();
    void createMsgBox();

    void createSidebar();
    void about();

    void loadImages();
    void loadSounds();

    void readSettings();
    void writeSettings();

    void saveGame();
    void loadGame();
    void clearSaveGame();

    void createHighscoreModel();
    void addHighscore();
};


#endif  // REVERSI_MAINWINDOW_H
