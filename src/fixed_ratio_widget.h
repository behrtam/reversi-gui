// Copyright 2015 Tammo Behrends

#ifndef REVERSI_FIXED_RATIO_WIDGET_H
#define REVERSI_FIXED_RATIO_WIDGET_H


#include <QWidget>


class FixedAspectRationWidget : public QWidget {
 protected:
    void resizeEvent(QResizeEvent * event) {
        if (width() > height()) {
            resize(height(), height());
        } else {
            resize(width(), width());
        }
    }
};

#endif  // REVERSI_FIXED_RATIO_WIDGET_H
