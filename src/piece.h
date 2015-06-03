// Copyright 2015 Tammo Behrends

#ifndef REVERSI_PIECE_H
#define REVERSI_PIECE_H

#include "./utils.h"

#include <array>
#include <iostream>

enum class Piece { empty, black, white };

inline std::ostream& operator << (std::ostream& os, const Piece & p) {
    static std::array<std::string, 3> piece_strings {
            "_",
            "O",
            "X"
    };
    return os << piece_strings[as_integer(p)];
}

#endif //REVERSI_PIECE_H
