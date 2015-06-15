// Copyright 2015 Tammo Behrends

#include <QWidget>
#include <QStatusBar>
#include <QGridLayout>
#include <QLabel>

#include "./mainwindow.h"
#include "./clickablelabel.h"
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
            ClickableLabel* label = new ClickableLabel(this);
            label->setFrameStyle(QFrame::Panel + QFrame::Sunken);
            label->setAlignment(Qt::AlignCenter);
            label->setPixmap((i + j) % 2 ? *pixmap_black : *pixmap_white);
            label->setScaledContents(true);

            connect(label, &ClickableLabel::clicked,
                    [this, i, j, label]{ clickedGamePiece(i, j, label); });
            grid_layout->addWidget(label, i, j);
        }
    }

    center = new QWidget(this);  // dummy wrapper widget
    center->setLayout(grid_layout);
    setCentralWidget(center);
}

void MainWindow::clickedGamePiece(int x, int y, ClickableLabel* label) {
    std::cout << "clicked: " << x << "|" << y << std::endl;

    QPixmap pixmap_white;
    if (!pixmap_white.load(":/resources/white.png" )) {
        qWarning("Failed to load black.png");
    }

    label->setPixmap(pixmap_white);
    label->setScaledContents(true);
}
