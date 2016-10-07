// Copyright 2015 Tammo Behrends

#include "./highscore_dialog.h"

#include <QtWidgets>
#include <QPushButton>
#include <QString>
#include <QTextStream>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>

#include "./highscore_columns.h"
#include "./utils.h"

HighScoreDialog::HighScoreDialog(QSqlTableModel* model, QWidget* parent) : QDialog(parent) {
    model->setHeaderData(as_integer(Columns::start), Qt::Horizontal, tr("Start date"));
    model->setHeaderData(as_integer(Columns::end), Qt::Horizontal, tr("End date"));
    model->setHeaderData(as_integer(Columns::boardsize), Qt::Horizontal, tr("Board"));
    model->setHeaderData(as_integer(Columns::moves), Qt::Horizontal, tr("Move"));
    model->setHeaderData(as_integer(Columns::blackname), Qt::Horizontal, tr("Black"));
    model->setHeaderData(as_integer(Columns::blackstones), Qt::Horizontal, tr("Stones"));
    model->setHeaderData(as_integer(Columns::whitename), Qt::Horizontal, tr("White"));
    model->setHeaderData(as_integer(Columns::whitestones), Qt::Horizontal, tr("Stones"));

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

    QPushButton *printButton = new QPushButton(tr("Print"));
    connect(printButton, &QPushButton::clicked, this, &HighScoreDialog::printHighscore);
    buttonBox->addButton(printButton, QDialogButtonBox::ActionRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    resize(680, 300);

    setWindowTitle(tr("High Score Dialog"));
}

void HighScoreDialog::printHighscore() {
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = view->model()->rowCount();
    const int columnCount = view->model()->columnCount();

    out <<  "<html>\n<head>\n<meta Content=\"Text/html; charset=Windows-1251\">\n"
            "<title>Highscore</title>\n"
            "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<table border=1 cellspacing=0 cellpadding=2>\n";

    out << "<thead><tr bgcolor=#dbdbdb>";
    for (int column = 0; column < columnCount; column++) {
        if (!view->isColumnHidden(column)) {
            out << QString("<th>%1</th>").arg(
                    view->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!view->isColumnHidden(column)) {
                QString data = view->model()->data(
                        view->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n</body>\n</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}