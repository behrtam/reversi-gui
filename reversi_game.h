// Copyright 2015 Tammo Behrends

#ifndef REVERSI_REVERSIGAME_H
#define REVERSI_REVERSIGAME_H

#include <vector>
#include <iostream>

enum class ReversiPiece { none, black, white };

std::ostream& operator << (std::ostream& os, const ReversiPiece& piece);

class ReversiGame {
 private:
    const int size_;
    std::vector<ReversiPiece> board_;

 public:
    ReversiGame() : ReversiGame(8) {}
    explicit ReversiGame(int size) : board_(size * size), size_(size) { }

    void displayBoard() const;
    ReversiPiece getPiece(int x, int y) const;
};

#endif  // REVERSI_REVERSIGAME_H
