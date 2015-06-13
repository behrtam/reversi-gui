// Copyright 2015 Tammo Behrends

#include "./mainwindow.h"

#include <QWidget>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    setObjectName("MainWindow");
    setWindowTitle("Reversi Main Window");

    QPixmap pixmap_black;
    if (!pixmap_black.load(":/resources/black.png" ))
        qWarning("Failed to load black.png");
    QLabel* label_black = new QLabel(this);
    label_black->setPixmap(pixmap_black);

    QPixmap pixmap_white;
    if (!pixmap_white.load(":/resources/white.png" ))
        qWarning("Failed to load white.png");
    QLabel* label_white = new QLabel(this);
    label_white->setPixmap(pixmap_white);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(label_black);
    layout->addWidget(label_white);

    center = new QWidget(this);
    center->setLayout(layout);
    setCentralWidget(center);

    statusBar()->showMessage(tr("Status Bar"));
}
