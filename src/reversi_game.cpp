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

Piece ReversiGame::getPiece(int x, int y) const {
    return board_.at(x + y * size_);
}

void ReversiGame::set_possible_moves() {
    if (!possible_moves_.empty()) {
        possible_moves_.clear();
    }
}
