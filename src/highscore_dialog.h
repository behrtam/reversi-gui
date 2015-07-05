// Copyright 2015 Tammo Behrends

#ifndef REVERSI_HIGHSCORE_DIALOG_H
#define REVERSI_HIGHSCORE_DIALOG_H

#include <QWidget>
#include <QDialog>
#include <QTableView>
#include <QDialogButtonBox>
#include <QSqlTableModel>

class HighScoreDialog : public QDialog {
    Q_OBJECT

 public:
    explicit HighScoreDialog(QSqlTableModel* model, QWidget* parent = 0);

 private:
    QTableView *view;
    QDialogButtonBox *buttonBox;
};


#endif  // REVERSI_HIGHSCORE_DIALOG_H
