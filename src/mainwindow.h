// Copyright 2015 Tammo Behrends

#ifndef QTHALLOWORLD_MAINWINDOW_H
#define QTHALLOWORLD_MAINWINDOW_H


#include <QMainWindow>
#include <QWidget>


class MainWindow : public QMainWindow {
 Q_OBJECT

    QWidget* center;

public:
    MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
};


#endif  // QTHALLOWORLD_MAINWINDOW_H
