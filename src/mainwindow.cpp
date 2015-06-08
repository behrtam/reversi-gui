// Copyright 2015 Tammo Behrends

#include "./mainwindow.h"

#include <QTextEdit>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
        : QMainWindow(parent, flags) {
    setObjectName("MainWindow");
    setWindowTitle("Reversi Main Window");

    center = new QTextEdit(this);
    center->setReadOnly(true);
    center->setMinimumSize(400, 205);
    setCentralWidget(center);

    statusBar()->showMessage(tr("Status Bar"));
}
