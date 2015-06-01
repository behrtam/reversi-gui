// Copyright 2015 Tammo Behrends

#include "./reversi_game.h"

void ReversiGame::displayBoard() const {
    for (int x = 0; x < size_; ++x) {
        for (int y = 0; y < size_; ++y) {
            std::cout << getPiece(x, y);
        }
        std::cout << std::endl;
    }
}

ReversiPiece ReversiGame::getPiece(int x, int y) const {
    return board_.at(x + y * size_);
}

std::ostream& operator << (std::ostream& os, const ReversiPiece& piece) {
    os << " ";
    switch (piece) {
        case ReversiPiece::none:
            os << "_";
            break;
        case ReversiPiece::black:
            os << "O";
            break;
        case ReversiPiece::white:
            os << "X";
            break;
    }
    return os;
}
