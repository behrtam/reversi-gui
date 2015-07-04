// Copyright 2015 Tammo Behrends

#ifndef REVERSI_CONNECT_H
#define REVERSI_CONNECT_H


#include <QSqlDatabase>
#include <QSqlQuery>


static bool createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("highscore.sqlite");

    if (!db.open()) {
        qDebug("Not able to establish a DB connection!");
        return false;
    }

    QSqlQuery query;
    //query.exec("drop table if exists scores");
    query.exec("CREATE TABLE IF NOT EXISTS scores (start DATETIME, end DATETIME,"
                                                   "boardsize INTEGER, moves INTEGER,"
                                                   "blackname TEXT, blackstones INTEGER,"
                                                   "whitename TEXT, whitestones INTEGER)");
    return true;
}


#endif  // REVERSI_CONNECT_H
