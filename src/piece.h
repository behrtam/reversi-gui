// Copyright 2015 Tammo Behrends

#ifndef REVERSI_PIECE_H
#define REVERSI_PIECE_H


#include <array>
#include <string>
#include <iostream>

#include "./utils.h"


/**
 *  The enum Piece represents a field on the ReversiGame board, which can be black, white or empty.
 */
enum class Piece {
    empty, ///< Piece empty
    black, ///< Piece black
    white ///< Piece white
};

/**
 *  Writes a textual representation of the given piece to the given stream.
 * \param os   the output stream.
 * \param p     the piece to be written.
 * \return a reference to the used stream.
 */
inline std::ostream &operator<<(std::ostream &os, const Piece &p) {
    static std::array<std::string, 3> piece_strings{{"_", "X", "O"}};
    return os << piece_strings[as_integer(p)];
}

/**
 * Inverts the given Piece (only if it's not empty).
 * @param p the pice.
 * @return the inverted piece.
 */
inline Piece invert(const Piece p) {
    if (p == Piece::black)
        return Piece::white;
    if (p == Piece::white)
        return Piece::black;
    return Piece::empty;
}

/**
 * Inverts the given Piece with the ! operator (only if it's not empty).
 * @param p the pice.
 * @return the inverted piece.
 */
inline Piece operator!(Piece p) {
    return invert(p);
}

#endif  // REVERSI_PIECE_H
