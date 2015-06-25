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
#include <QMenuBar>
#include <QAction>

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
    resize(800, 700);

    createActions();
    createMenus();
    createMsgBox();

    playername_black_ = "Mr. Black";
    playername_white_ = "Ms. White";

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
    createSidebar();    

    boxLayout = new QHBoxLayout(this);
    boxLayout->addItem(grid_layout);
    boxLayout->addWidget(sidebar);

    center = new QWidget(this);  // dummy wrapper widget
    center->setLayout(boxLayout);
    setCentralWidget(center);

    statusBar()->showMessage(tr("Status Bar"));
}

void MainWindow::createSidebar(){
    sidebar = new QWidget(this);
    sidebar->setStyleSheet("background-color:red;");
    sidebar->setMinimumWidth(200);
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
    if  (game->get_moves().size() == 0) {
        unsigned int score_white, score_black;
        std::tie(score_white, score_black) = game->get_score();

        statusBar()->showMessage("The Game is over!");

        QMessageBox msgBox;
        msgBox.setWindowTitle("Game is over!");

        if (score_white > score_black) {
            msgBox.setText(playername_white_ + " won this round!");
        } else {
            msgBox.setText(playername_black_ + " won this round!");
        }
        msgBox.setInformativeText(QString("%1 has %2 pieces. %3 has %4 pieces. Restart or close?")
                                          .arg(playername_white_).arg(score_white)
                                          .arg(playername_black_).arg(score_black));
        QPushButton *connectButton = msgBox.addButton(tr("Restart"), QMessageBox::ActionRole);
        QPushButton *closeButton = msgBox.addButton(QMessageBox::Close);

        msgBox.exec();

        if (qobject_cast<QPushButton *>(msgBox.clickedButton()) == connectButton) {
            game = std::make_unique<ReversiGame>(game->board_size());
            resetGame();
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

void MainWindow::createActions() {
    newGameAct = new QAction(tr("&New game"), this);
    newGameAct->setShortcuts(QKeySequence::New);
    newGameAct->setStatusTip(tr("Create a new game"));
    connect(newGameAct, &QAction::triggered, [this]{
        if (resetMsgBox->exec() == QMessageBox::Ok) {
            game = std::make_unique<ReversiGame>(game->board_size());
            resetGame();
        }
    });

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    boardSize4 = new QAction(tr("4x4"), this);
    boardSize4->setCheckable(true);
    boardSize4->setStatusTip(tr("Change board size to 4x4"));
    connect(boardSize4, &QAction::triggered, [this]{ changeBoardSize(4); });

    boardSize6 = new QAction(tr("6x6"), this);
    boardSize6->setCheckable(true);
    boardSize6->setStatusTip(tr("Change board size to 6x6"));
    connect(boardSize6, &QAction::triggered, [this]{ changeBoardSize(6); });

    boardSize8 = new QAction(tr("8x8"), this);
    boardSize8->setCheckable(true);
    boardSize8->setStatusTip(tr("Change board size to 8x8"));
    connect(boardSize8, &QAction::triggered, [this]{ changeBoardSize(8); });

    boardSize10 = new QAction(tr("10x10"), this);
    boardSize10->setCheckable(true);
    boardSize10->setStatusTip(tr("Change board size to 10x10"));
    connect(boardSize10, &QAction::triggered, [this]{ changeBoardSize(10); });

    boardSize12 = new QAction(tr("12x12"), this);
    boardSize12->setCheckable(true);
    boardSize12->setStatusTip(tr("Change board size to 12x12"));
    connect(boardSize12, &QAction::triggered, [this]{ changeBoardSize(12); });

    boardSizeGroup = new QActionGroup(this);
    boardSizeGroup->addAction(boardSize4);
    boardSizeGroup->addAction(boardSize6);
    boardSizeGroup->addAction(boardSize8);
    boardSizeGroup->addAction(boardSize10);
    boardSizeGroup->addAction(boardSize12);
    boardSize8->setChecked(true);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newGameAct);
    fileMenu->addAction("Open game");
    fileMenu->addAction("Save game");
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    settingsMenu = menuBar()->addMenu(tr("&Settings"));
    settingsMenu->addAction("Some thing");

    boardSizeMenu = settingsMenu->addMenu(tr("&Board size"));
    boardSizeMenu->addAction(boardSize4);
    boardSizeMenu->addAction(boardSize6);
    boardSizeMenu->addAction(boardSize8);
    boardSizeMenu->addAction(boardSize10);
    boardSizeMenu->addAction(boardSize12);

    aboutMenu = menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutAct);

    // TODO: only use on mac
    menuBar()->setNativeMenuBar(false);
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About Reversi"),
                       tr("The <b>Reversi</b> game demonstrates how to write a simple"
                          " board game in C++14 with a GUI using Qt 5."));
}

void MainWindow::changeBoardSize(unsigned int size) {
    if (!gameIsRunning() || (resetMsgBox->exec() == QMessageBox::Ok)) {
        game = std::make_unique<ReversiGame>(size);
        resetGame();
    }
}

void MainWindow::resetGame() {
    if (grid_layout->columnCount() == game->board_size()) {
        clearGameGrid();
    } else {
        createGameGrid();
    }
    updateGameGrid();
}

bool MainWindow::gameIsRunning() {
    // TODO: check if first move has been done and moves are available
    return true;
}

void MainWindow::createMsgBox() {
    resetMsgBox = new QMessageBox(this);
    resetMsgBox->setText("Reset running game.");
    resetMsgBox->setInformativeText("Do you want to reset your game to apply changes?");
    resetMsgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    resetMsgBox->setDefaultButton(QMessageBox::Ok);
}
