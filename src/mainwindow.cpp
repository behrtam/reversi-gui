// Copyright 2015 Tammo Behrends

#include "./mainwindow.h"

#include <QWidget>
#include <QWidgetItem>
#include <QStatusBar>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include <QPushButton>
#include <QAbstractButton>

#include <sstream>
#include <memory>

#include "./clickablelabel.h"
#include "./reversi_game.h"
#include "./piece.h"
#include "./random_reversi_player.h"


MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
        : QMainWindow(parent, flags), game(std::make_unique<ReversiGame>()) {
    setObjectName("MainWindow");
    setWindowTitle("Reversi Main Window");
    resize(700, 700);

    pixmap_black = new QPixmap();
    if (!pixmap_black->load(":/resources/black.png" ))
        qWarning("Failed to load black.png");

    pixmap_white = new QPixmap();
    if (!pixmap_white->load(":/resources/white.png" ))
        qWarning("Failed to load white.png");

    pixmap_empty = new QPixmap();
    if (!pixmap_empty->load(":/resources/empty.png" ))
        qWarning("Failed to load empty.png");

    createGameGrid();
    updateGameGrid();

    statusBar()->showMessage(tr("Status Bar"));
}

void MainWindow::createGameGrid() {
    grid_layout = new QGridLayout;
    grid_layout->setSpacing(0);
    grid_layout->setMargin(0);

    for (int x = game->board_size(); x-- > 0; ) {
        for (int y = game->board_size(); y-- > 0; ) {
            ClickableLabel* label = new ClickableLabel(this);
            label->setMinimumSize(50, 50);
            label->setFrameStyle(QFrame::Panel + QFrame::Sunken);
            label->setAlignment(Qt::AlignCenter);
            label->setPixmap(*pixmap_empty);
            label->setScaledContents(true);

            connect(label, &ClickableLabel::clicked,
                    [this, x, y, label]{ clickedGamePiece(x, y); });

            grid_layout->addWidget(label, y, x);
        }
    }

    center = new QWidget(this);  // dummy wrapper widget
    center->setLayout(grid_layout);
    setCentralWidget(center);
}

void MainWindow::clearGameGrid() {
    for (unsigned int x = 0; x < grid_layout->columnCount(); ++x) {
        for (unsigned int y = 0; y < grid_layout->rowCount(); ++y) {
            QLayoutItem *item = grid_layout->itemAtPosition(y, x);
            auto label = dynamic_cast<ClickableLabel*>(item->widget());
            label->setPixmap(*pixmap_empty);
        }
    }
}

void MainWindow::clickedGamePiece(unsigned int x, unsigned int y) {
    if (game->is_valid_move({x, game->board_size() - y - 1})) {
        std::stringstream ss((game->is_active() == Piece::black ? "Black" : "White"));
        ss << " played on [" << x << "|" << y << "]. Now it's ";
        game->make_move({x, game->board_size() - y - 1});
        ss << (game->is_active() == Piece::black ? "Blacks" : "Whites") << " turn.";
        statusBar()->showMessage(QString::fromStdString(ss.str()));

        if (game->get_moves().size() > 0) {
            RandomReversiPlayer player;
            game->make_move(player.think(*game));
        }

        updateGameGrid();
    }

    if (game->get_moves().size() == 0) {
        statusBar()->showMessage("The Game is over!");

        QMessageBox msgBox;
        msgBox.setWindowTitle("Game is over!");
        msgBox.setText("This game of reversi is over. Close or restart?");
        QPushButton *connectButton = msgBox.addButton(tr("Restart"), QMessageBox::ActionRole);
        QPushButton *closeButton = msgBox.addButton(QMessageBox::Close);

        msgBox.exec();

        if (qobject_cast<QPushButton *>(msgBox.clickedButton()) == connectButton) {
            game = std::make_unique<ReversiGame>(game->board_size());
            clearGameGrid();
            updateGameGrid();
        } else if (qobject_cast<QPushButton *>(msgBox.clickedButton()) == closeButton) {
            this->close();
        }
    }
}

void MainWindow::updateGameGrid() {
    for (unsigned int x = 0; x < grid_layout->columnCount(); ++x) {
        for (unsigned int y = 0; y < grid_layout->rowCount(); ++y) {
            QLayoutItem *item = grid_layout->itemAtPosition(y, x);
            auto label = dynamic_cast<ClickableLabel*>(item->widget());

            Piece p = game->get_piece({x, game->board_size() - y - 1});
            if (p == Piece::black) label->setPixmap(*pixmap_black);
            else if (p == Piece::white) label->setPixmap(*pixmap_white);
            label->setScaledContents(true);
        }
    }
}
