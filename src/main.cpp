// Copyright 2015 Tammo Behrends

#include <QApplication>

#include "./mainwindow.h"
#include "./connect.h"


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    app.setOrganizationName("HTW MM15 QtProject");
    app.setApplicationName("Reversi GUI");

    if (!createConnection())
        return 1;

    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
