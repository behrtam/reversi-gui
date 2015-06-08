// Copyright 2015 Tammo Behrends

#include <QApplication>
#include <QMainWindow>

#include "./reversi_game.h"
#include "./mainwindow.h"

ReversiGame game;


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.resize(800, 600);
    mainWin.show();
    return app.exec();
}