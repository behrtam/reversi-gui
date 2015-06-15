// Copyright 2015 Tammo Behrends

#ifndef REVERSI_CLICKABLELABEL_H
#define REVERSI_CLICKABLELABEL_H


#include <QWidget>
#include <QLabel>
#include <QMouseEvent>


class ClickableLabel : public QLabel {
    Q_OBJECT

 public:
    explicit ClickableLabel(QWidget* parent = 0, Qt::WindowFlags flags = 0);

 signals:
    void clicked();

 protected:
    void mousePressEvent (QMouseEvent* event);
};


#endif  // REVERSI_CLICKABLELABEL_H
