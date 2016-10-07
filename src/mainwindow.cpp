// Copyright 2015 Tammo Behrends

#include "./mainwindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QSound>
#include <QStatusBar>
#include <QString>
#include <QWidget>
#include <QWidgetItem>
#include <QSqlRecord>
#include <QSqlQuery>

#include <QApplication>

#include <memory>
#include <sstream>

#include "./clickablelabel.h"
#include "./piece.h"
#include "./random_reversi_player.h"
#include "./reversi_game.h"
#include "./fixed_ratio_widget.h"
#include "./highscore_columns.h"
#include "./utils.h"
#include "./highscore_dialog.h"


MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
        : QMainWindow(parent, flags),
          game(std::make_unique<ReversiGame>()),
          playername_white_("Ms. White"),
          playername_black_("Mr. Black") {
    setObjectName("MainWindow");

    createActions();
    createMenus();
    createMsgBox();

    loadImages();
    loadSounds();

    createSidebar();
    createGameGrid();
    updateGameGrid();

    black = nullptr;

    readSettings();

    createHighscoreModel();

    translator = new QTranslator();
    if (!translator->load("test_de", ":/resources")) {
        qWarning("Failed to load de language");
    }

    retranslateUi();

    statusBar()->showMessage(tr("Status Bar"));
}

void MainWindow::playSound(QSound *sound) {
    if (soundOption->isChecked()) {
        sound->play();
    }
}

void MainWindow::switchLanguage() {
    if (langEN->isChecked()) {
        qApp->removeTranslator(translator);
    } else {
        qApp->installTranslator(translator);
    }
}

void MainWindow::changeEvent(QEvent *e) {
    if (e->type() == QEvent::LanguageChange) {
        retranslateUi();
    } else {
        QMainWindow::changeEvent(e);
    }
}

void MainWindow::retranslateUi() {
    // TODO: all the others
    setWindowTitle(tr("Reversi Main Window"));
    fileMenu->setTitle(tr("&File"));
    settingsMenu->setTitle(tr("&Settings"));
    boardSizeMenu->setTitle(tr("&Board size"));
    blackPlayereMenu->setTitle(tr("&Black player"));
    langMenu->setTitle(tr("&Languages"));
    highScoreMenu->setTitle(tr("&High score"));
    aboutMenu->setTitle(tr("&About"));

    newGameAct->setText(tr("&New game"));
    //exitAct->setText(tr("E&xit"));
    //loadAct->setText(tr("&Load game"));
    //saveAct->setText(tr("&Save game"));

}

void MainWindow::loadSounds() {
    tapped = new QSound(":/resources/tapped.wav");
    if (!QFile::exists(":/resources/tapped.wav"))
        qWarning("Failed to load tapped.wav");

    timber = new QSound(":/resources/timber.wav");
    if (!QFile::exists(":/resources/timber.wav"))
        qWarning("Failed to load timber.wav");

    xylo = new QSound(":/resources/xylo.wav");
    if (!QFile::exists(":/resources/xylo.wav"))
        qWarning("Failed to load xylo.wav");

    cheering = new QSound(":/resources/cheering.wav");
    if (!QFile::exists(":/resources/cheering.wav"))
        qWarning("Failed to load cheering.wav");

    trombone = new QSound(":/resources/trombone.wav");
    if (!QFile::exists(":/resources/trombone.wav"))
        qWarning("Failed to load trombone.wav");
}

void MainWindow::loadImages() {
    pixmap_black = new QPixmap();
    if (!pixmap_black->load(":/resources/black.png" ))
        qWarning("Failed to load black.png");

    pixmap_white = new QPixmap();
    if (!pixmap_white->load(":/resources/white.png" ))
        qWarning("Failed to load white.png");

    pixmap_empty = new QPixmap();
    if (!pixmap_empty->load(":/resources/empty.png" ))
        qWarning("Failed to load empty.png");

    pixmap_white_light = new QPixmap();
    if (!pixmap_white_light->load(":/resources/white_light.png" ))
        qWarning("Failed to load white_light.png");

    pixmap_black_light = new QPixmap();
    if (!pixmap_black_light->load(":/resources/black_light.png" ))
        qWarning("Failed to load black_light.png");
}

void MainWindow::createSidebar() {
    sidebar = new QWidget(this);
    sidebar->setStyleSheet("background-color:gray;");
    sidebar->setMinimumWidth(200);


    QPushButton *restartButton = new QPushButton("Undo", sidebar);
    restartButton->setGeometry(QRect(QPoint(50, 50), QSize(100, 50)));
    restartButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(restartButton, &QPushButton::clicked, this, &MainWindow::undo);

    /*connect(restartButton, &QPushButton::clicked, [this]{
        if (resetMsgBox->exec() == QMessageBox::Ok) {
            game = std::make_unique<ReversiGame>(game->board_size());
            resetGame();
        }
    });*/

    QPushButton *exitButton = new QPushButton("Exit", sidebar);
    exitButton->setGeometry(QRect(QPoint(50, 100), QSize(100, 50)));
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);
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

            // label->setScaledContents(true);

            connect(label, &ClickableLabel::clicked,
                    [this, x, y, label]{ clickedGamePiece(x, y); });

            grid_layout->addWidget(label, y, x);
        }
    }

    // TODO: layout problem needs to be fixed
    // QLayout: Attempting to add QLayout "" to MainWindow "MainWindow",
    // which already has a layout

    boxLayout = new QHBoxLayout();
    FixedAspectRationWidget* dummy = new FixedAspectRationWidget;
    dummy->setLayout(grid_layout);
    boxLayout->addWidget(dummy);
    boxLayout->addWidget(sidebar);

    center = new QWidget(this);  // dummy wrapper widget
    center->setLayout(boxLayout);

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

        if (game->moves() == 0)
            game_start = QDateTime::currentDateTime();

        undoState = game->board2string();
        game->make_move({x, game->board_size() - y - 1});

        if (game->is_active() == Piece::white)
            playSound(tapped);
        else
            playSound(timber);
        ss << (game->is_active() == Piece::black ? "Blacks" : "Whites") << " turn.";
        statusBar()->showMessage(QString::fromStdString(ss.str()));

        if (black != nullptr && game->possible_moves().size() > 0) {
            game->make_move(black->think(*game));
            undoState = "";  // no undo for computer moves
            // timber->play();
        }

        updateGameGrid();
    } else {
        playSound(xylo);
    }
    if  (game->possible_moves().size() == 0) {
        game_end = QDateTime::currentDateTime();
        unsigned int score_white, score_black;
        std::tie(score_white, score_black) = game->get_score();

        statusBar()->showMessage(tr("The Game is over!"));

        addHighscore();

                QMessageBox msgBox;
                msgBox.setWindowTitle(tr("Game is over!"));

                if (score_white > score_black) {
                    msgBox.setText(playername_white_ + " won this round!");
                    playSound(cheering);
                } else if (score_white < score_black) {
                    msgBox.setText(playername_black_ + " won this round!");
                    if (blackHuman->isChecked()) {
                        playSound(cheering);
                    } else {
                        playSound(trombone);
                    }
                } else {
                    msgBox.setText("It's a draw!");
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


                    if (p == Piece::black) {
                        label->setPixmap(*pixmap_black);
                    } else if (p == Piece::white) {
                        label->setPixmap(*pixmap_white);
                    } else {
                        label->setPixmap(*pixmap_empty);
                    }

                    if (game->is_valid_move({x, game->board_size() - y - 1})) {
                        if (game->is_active() == Piece::black)
                            label->setPixmap(*pixmap_black_light);
                        else
                            label->setPixmap(*pixmap_white_light);
            }

            label->setScaledContents(true);
        }
    }
}

void MainWindow::createActions() {
    newGameAct = new QAction(tr("&New game"), this);
    newGameAct->setShortcuts(QKeySequence::New);
    //newGameAct->setStatusTip(tr("Create a new game"));
    connect(newGameAct, &QAction::triggered, [this]{
        if (!gameIsRunning() || (resetMsgBox->exec() == QMessageBox::Ok)) {
            Piece starter = startingPlayer->isChecked() ? Piece::black : Piece::white;
            game = std::make_unique<ReversiGame>(game->board_size(), starter);
            resetGame();
        }
    });

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    // exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    loadAct = new QAction(tr("&Load game"), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Load the saved game"));
    connect(loadAct, &QAction::triggered, this, &MainWindow::loadGame);

    saveAct = new QAction(tr("&Save game"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current game"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveGame);

    clearAct = new QAction(tr("&Clear saved game"), this);
    clearAct->setStatusTip(tr("Clear the saved game"));
    connect(clearAct, &QAction::triggered, this, &MainWindow::clearSaveGame);

    scoreDialogAct = new QAction(tr("&Show high score"), this);
    scoreDialogAct->setStatusTip(tr("Shows the saved scores"));
    connect(scoreDialogAct, &QAction::triggered, [this] {
        HighScoreDialog dialog(model);
        dialog.exec();
    });

    scoreClearAct = new QAction(tr("&Clear high score"), this);
    scoreClearAct->setStatusTip(tr("Delete all the saved scores"));
    connect(scoreClearAct, &QAction::triggered, [this] {
        // model->removeRows(0, 2);
        // model->submit();
        QSqlQuery query;
        query.exec("DELETE FROM scores;");
        model->select();
    });

    /*boardSize4 = createBoardSizeAction(4);
    boardSize6 = createBoardSizeAction(6);
    boardSize8 = createBoardSizeAction(8);
    boardSize10 = createBoardSizeAction(10);
    boardSize12 = createBoardSizeAction(12);*/
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

    blackHuman = new QAction(tr("human"), this);
    blackHuman->setCheckable(true);
    blackHuman->setStatusTip(tr("Change black player to be human"));
    connect(blackHuman, &QAction::triggered, [this]{ black = nullptr; });

    blackRandom = new QAction(tr("random"), this);
    blackRandom->setCheckable(true);
    blackRandom->setStatusTip(tr("Change black player to be random"));
    connect(blackRandom, &QAction::triggered, [this]{ black = new RandomReversiPlayer; });

    blackPlayerGroup = new QActionGroup(this);
    blackPlayerGroup->addAction(blackHuman);
    blackPlayerGroup->addAction(blackRandom);
    blackHuman->setChecked(true);

    langEN = new QAction(tr("en"), this);
    langEN->setCheckable(true);
    langEN->setStatusTip(tr("Change language to EN"));
    connect(langEN, &QAction::triggered, this, &MainWindow::switchLanguage);

    langDE = new QAction(tr("de"), this);
    langDE->setCheckable(true);
    langDE->setStatusTip(tr("Change language to DE"));
    connect(langDE, &QAction::triggered, this, &MainWindow::switchLanguage);

    langGroup = new QActionGroup(this);
    langGroup->addAction(langEN);
    langGroup->addAction(langDE);
    langEN->setChecked(true);

    soundOption = new QAction(tr("Play sounds"), this);
    soundOption->setCheckable(true);
    soundOption->setChecked(true);

    startingPlayer = new QAction(tr("Black starts"), this);
    startingPlayer->setCheckable(true);
    connect(startingPlayer, &QAction::toggled, [this](bool checked){
        if (!gameIsRunning() || (resetMsgBox->exec() == QMessageBox::Ok)) {
            game = std::make_unique<ReversiGame>(game->board_size(),
                                                 checked ? Piece::black : Piece::white);
            resetGame();
        }
    });

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

// Ansatz um Boardsize zu refactorn
/*
    QAction* MainWindow::createBoardSizeAction(unsigned int boardSizeNumber) {
    const char* boardSizeString = boardSizeNumber +"x"+ boardSizeNumber;
    QAction *boardSize = new QAction(tr(boardSizeString), this);
    boardSize->setCheckable(true);
    boardSize->setStatusTip(tr(boardSizeString));
    connect(boardSize, &QAction::triggered, [this]{ changeBoardSize(boardSizeNumber); });
    boardSizeGroup->addAction(boardSize);
    if(boardSizeNumber==8) {
        boardSize->setChecked(true);        
    }
    return boardSize;
}*/

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    //fileMenu = new QMenu(this);
    fileMenu->addAction(newGameAct);
    fileMenu->addAction(loadAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(clearAct);
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

    blackPlayereMenu = settingsMenu->addMenu(tr("&Black player"));
    blackPlayereMenu->addAction(blackHuman);
    blackPlayereMenu->addAction(blackRandom);

    langMenu = settingsMenu->addMenu(tr("&Languages"));
    langMenu->addAction(langEN);
    langMenu->addAction(langDE);

    settingsMenu->addAction(startingPlayer);
    settingsMenu->addAction(soundOption);

    highScoreMenu = menuBar()->addMenu(tr("&High score"));
    highScoreMenu->addAction(scoreDialogAct);
    highScoreMenu->addAction(scoreClearAct);

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
    return game->moves() > 0 && game->moves_possible();
}

void MainWindow::createMsgBox() {
    resetMsgBox = new QMessageBox(this);
    resetMsgBox->setText("Reset running game.");
    resetMsgBox->setInformativeText("Do you want to reset your game to apply changes?");
    resetMsgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    resetMsgBox->setDefaultButton(QMessageBox::Ok);
}

void MainWindow::readSettings() {
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(800, 650)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (gameIsRunning()) {
        QMessageBox msg;
        msg.setText("Save running game.");
        msg.setInformativeText("Do you want to save your running game?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setDefaultButton(QMessageBox::No);
        if (msg.exec() == QMessageBox::Yes)
            saveGame();
    }

    // write cached data from model to the database
    model->submitAll();

    writeSettings();
}



void MainWindow::saveGame() {
    QSettings settings;
    settings.beginGroup("game state");

    settings.setValue("board", QString::fromStdString(game->board2string()));
    settings.setValue("moves", game->moves());
    settings.setValue("active", as_integer(game->is_active()));
    settings.setValue("playernameblack", playername_black_);
    settings.setValue("playernamewhite", playername_white_);
    // TODO: also save black modus (human, random, etc) maybe as enum

    settings.endGroup();
}

void MainWindow::loadGame() {
    QSettings settings;

    if (settings.contains("game state/board")) {
        settings.beginGroup("game state");
        QString board = settings.value("board").toString();
        unsigned int moves = settings.value("moves").toUInt();
        Piece acitve = settings.value("active").toInt() == 1 ? Piece::black : Piece::white;
        game = std::make_unique<ReversiGame>(board.toStdString(), acitve, moves);
        playername_black_ = settings.value("playernameblack", "Mr. Black").toString();
        playername_white_ = settings.value("playernamewhite", "Ms. White").toString();
        settings.endGroup();
        resetGame();
    }
}

void MainWindow::undo() {
    if (undoState.empty()) {
        qWarning("no undo state there");
    } else {
        qWarning("let's undo");
        game = std::make_unique<ReversiGame>(undoState, !game->is_active(),  game->moves() - 1);
        undoState = "";
        resetGame();
    }
}

void MainWindow::clearSaveGame() {
    QSettings settings;
    settings.beginGroup("game state");
    settings.remove("");
    settings.endGroup();
}

void MainWindow::createHighscoreModel() {
    model = new QSqlTableModel(this);
    model->setTable("scores");
    model->select();
}

void MainWindow::addHighscore() {
    const QString DFORMAT = "yyyy-MM-dd HH:mm:ss";
    QSqlRecord record = model->record();
    record.setValue(as_integer(Columns::start), game_start.toString(DFORMAT));
    record.setValue(as_integer(Columns::end), game_end.toString(DFORMAT));
    record.setValue(as_integer(Columns::boardsize), game->board_size());
    record.setValue(as_integer(Columns::moves), game->moves());
    unsigned int score_white, score_black;
    std::tie(score_white, score_black) = game->get_score();
    record.setValue(as_integer(Columns::blackname), playername_black_);
    record.setValue(as_integer(Columns::blackstones), score_black);
    record.setValue(as_integer(Columns::whitename), playername_white_);
    record.setValue(as_integer(Columns::whitestones), score_white);
    model->insertRecord(-1, record);
}
