// Copyright 2015 Tammo Behrends

#include "./clickablelabel.h"


ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags flags) : QLabel(parent, flags) {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
