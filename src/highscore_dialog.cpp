// Copyright 2015 Tammo Behrends

#include "./highscore_dialog.h"

#include <QtWidgets>

#include "./highscore_columns.h"
#include "./utils.h"

HighScoreDialog::HighScoreDialog(QSqlTableModel* model, QWidget* parent) : QDialog(parent) {
    model->setHeaderData(as_integer(Columns::start), Qt::Horizontal, tr("Startdatum"));
    model->setHeaderData(as_integer(Columns::end), Qt::Horizontal, tr("Enddatum"));
    model->setHeaderData(as_integer(Columns::boardsize), Qt::Horizontal, tr("Brett"));
    model->setHeaderData(as_integer(Columns::moves), Qt::Horizontal, tr("Züge"));
    model->setHeaderData(as_integer(Columns::blackname), Qt::Horizontal, tr("Schwarz"));
    model->setHeaderData(as_integer(Columns::blackstones), Qt::Horizontal, tr("Steine"));
    model->setHeaderData(as_integer(Columns::whitename), Qt::Horizontal, tr("Weiß"));
    model->setHeaderData(as_integer(Columns::whitestones), Qt::Horizontal, tr("Steine"));

    view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();
    view->verticalHeader()->hide();
    view->setSortingEnabled(true);
    view->sortByColumn(as_integer(Columns::start), Qt::SortOrder::DescendingOrder);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    resize(680, 300);

    setWindowTitle(tr("High Score Dialog"));
}
