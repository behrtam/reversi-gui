// Copyright 2015 Tammo Behrends

#include <QWidget>
#include <QStatusBar>
#include <QGridLayout>
#include <QLabel>

#include "./mainwindow.h"
#include "./reversi_game.h"


MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
        : QMainWindow(parent, flags), game(new ReversiGame(4)) {
    setObjectName("MainWindow");
    setWindowTitle("Reversi Main Window");
    setBaseSize(42, 42);

    pixmap_black = new QPixmap();
    if (!pixmap_black->load(":/resources/black.png" ))
        qWarning("Failed to load black.png");

    pixmap_white = new QPixmap();
    if (!pixmap_white->load(":/resources/white.png" ))
        qWarning("Failed to load white.png");

    createGameGrid();

    statusBar()->showMessage(tr("Status Bar"));
}

void MainWindow::createGameGrid() {
    QGridLayout *grid_layout = new QGridLayout;
    grid_layout->setSpacing(0);
    grid_layout->setMargin(0);

    for (int i = 0; i < game->board_size(); i++) {
        for (int j = 0; j < game->board_size(); j++) {
            QLabel* label = new QLabel(this);
            label->setFrameStyle(QFrame::Panel + QFrame::Sunken);
            label->setAlignment(Qt::AlignCenter);
            label->setPixmap((i + j) % 2 ? *pixmap_black : *pixmap_white);
            label->setScaledContents(true);
            grid_layout->addWidget(label, i, j);
        }
    }

    center = new QWidget(this);  // dummy wrapper widget
    center->setLayout(grid_layout);
    setCentralWidget(center);
}
