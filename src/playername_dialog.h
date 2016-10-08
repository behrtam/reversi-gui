//
// Created by Tammo Behrends on 07.10.16.
//

#ifndef REVERSI_PLAYERNAME_DIALOG_H
#define REVERSI_PLAYERNAME_DIALOG_H


#include <QDialog>
#include <QString>
#include <QLineEdit>

class PlayerNameDialog : public QDialog {
Q_OBJECT

public:
    explicit PlayerNameDialog(QWidget* parent = 0);

public:
    QLineEdit *nameOneLineEdit;
    QLineEdit *nameTwoLineEdit;
};


#endif //REVERSI_PLAYERNAME_DIALOG_H
