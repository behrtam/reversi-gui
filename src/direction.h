// Copyright 2015 Tammo Behrends

#ifndef REVERSI_DIRECTION_H
#define REVERSI_DIRECTION_H

#include "./utils.h"
#include "./square.h"

#include <array>
#include <iostream>

enum class Direction { up, up_left, up_right, down, down_right, down_left, left, right };

inline std::ostream &operator<<(std::ostream &os, const Direction &d) {
    static std::array<std::string, 8> directionStrings {
            "UP",
            "UPLEFT",
            "UPRIGHT",
            "DOWN",
            "DOWNRIGHT",
            "DOWNLEFT",
            "LEFT",
            "RIGHT"
    };

    return os << directionStrings[as_integer(d)];
}

inline Direction determine(const Square start, const Square end) {
    int delta_x = start.x - end.x;
    int delta_y = start.y - end.y;

    if (delta_x == 0) {
        return delta_y < 0 ? Direction::up : Direction::down;
    } else if (delta_y == 0) {
        return delta_x < 0 ? Direction::right : Direction::left;
    } else if (delta_x < 0) {
        return delta_y < 0 ? Direction::up_right : Direction::down_right;
    } else {
        return delta_y < 0 ? Direction::up_left : Direction::down_left;
    }
}

#endif //REVERSI_DIRECTION_H
