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
    // query.exec("INSERT INTO scores VALUES('2015-06-30 10:30:00', '2015-06-30 11:00:00', 8, 63,"
    //            "'Mr. Black', 34, 'Ms. White', 30)");
    // query.exec("INSERT INTO scores VALUES('2015-06-28 19:30:00', '2015-06-29 01:02:03', 8, 82,"
    //            "'Tammo', 44, 'Tim', 18)");
    return true;
}


#endif  // REVERSI_CONNECT_H
