// Copyright 2015 Tammo Behrends

#ifndef REVERSI_PIECE_H
#define REVERSI_PIECE_H


#include <array>
#include <string>
#include <iostream>

#include "./utils.h"


enum class Piece {
    empty, black, white
};

inline std::ostream &operator<<(std::ostream &os, const Piece &p) {
    static std::array<std::string, 3> piece_strings{{"_", "X", "O"}};
    return os << piece_strings[as_integer(p)];
}

inline Piece invert(const Piece p) {
    if (p == Piece::black)
        return Piece::white;
    if (p == Piece::white)
        return Piece::black;
    return Piece::empty;
}

inline Piece operator!(Piece p) {
    return invert(p);
}

#endif  // REVERSI_PIECE_H
