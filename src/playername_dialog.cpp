//
// Created by Tammo Behrends on 07.10.16.
//

#include "playername_dialog.h"

#include <QtWidgets>
#include <QPushButton>
#include <QString>
#include <QGridLayout>
#include <QDialogButtonBox>

PlayerNameDialog::PlayerNameDialog(QWidget* parent) : QDialog(parent) {

    QLabel *nameOneLabel = new QLabel(tr("White Player:"));
    nameOneLineEdit = new QLineEdit;

    QLabel *nameTwoLabel = new QLabel(tr("Black Player:"));
    nameTwoLineEdit = new QLineEdit;

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameOneLabel, 0, 0);
    layout->addWidget(nameOneLineEdit, 0, 1);
    layout->addWidget(nameTwoLabel, 1, 0);
    layout->addWidget(nameTwoLineEdit, 1, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    resize(380, 120);

    setWindowTitle(tr("Player Name Dialog"));
}
