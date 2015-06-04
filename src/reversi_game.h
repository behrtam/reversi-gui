// Copyright 2015 Tammo Behrends

#ifndef REVERSI_REVERSIGAME_H
#define REVERSI_REVERSIGAME_H


#include <vector>
#include <utility>
#include <iostream>

#include "./piece.h"
#include "./square.h"

class ReversiGame {
 private:
    const int size_;
    std::vector<Piece> board_;
    std::vector<std::pair<Square, std::vector<Square>>> possible_moves_;

    Piece active_;

 public:
    ReversiGame() : ReversiGame(8) {}
    explicit ReversiGame(int size) : board_(size * size), size_(size) {
        // throw error if size < 4, size > 16, size % 2 == 1
        set_piece(size_ / 2, size_ / 2, Piece::white);
        set_piece(size_ / 2 - 1, size_ / 2, Piece::black);
        set_piece(size_ / 2, size_ / 2 - 1, Piece::white);
        set_piece(size_ / 2 - 1, size_ / 2 - 1, Piece::black);

        active_ = Piece::white;
        set_all_moves();
    }

    void displayBoard() const;
    Piece get_piece(Square s) const;
    auto get_moves() const { return possible_moves_; }

 private:
    Piece get_piece(int x, int y) const;
    void set_piece(int x, int y, Piece p);
    void set_piece(Square s, Piece p);

    void set_all_moves();
    void set_moves(Square s);
};


#endif  // REVERSI_REVERSIGAME_H
