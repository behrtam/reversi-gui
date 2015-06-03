// Copyright 2015 Tammo Behrends

#ifndef REVERSI_REVERSIGAME_H
#define REVERSI_REVERSIGAME_H

#include "./piece.h"
#include "./square.h"

#include <vector>
#include <iostream>

class ReversiGame {
 private:
    const int size_;
    std::vector<Piece> board_;
    std::vector<Square> possible_moves_;

 public:
    ReversiGame() : ReversiGame(8) {}
    explicit ReversiGame(int size) : board_(size * size), size_(size) { }

    void displayBoard() const;
    Piece getPiece(int x, int y) const;

 private:
    void set_possible_moves();
};

#endif  // REVERSI_REVERSIGAME_H
