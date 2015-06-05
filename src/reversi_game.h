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
    const unsigned int size_;
    std::vector<Piece> board_;
    std::vector<std::pair<Square, std::vector<Square>>> possible_moves_;
    Piece active_;

 public:
    ReversiGame() : ReversiGame(8) { }

    explicit ReversiGame(int size);

    void display_board() const;

    unsigned int board_size() const {
        return size_;
    }

    Piece get_piece(Square s) const;

    auto get_moves() const { return possible_moves_; }

    bool is_valid_move(Square s) const;

    void make_move(Square s);

    bool moves_possible() const { return !possible_moves_.empty(); }

    Piece is_active() const { return active_; }

 private:
    Piece get_piece(int x, int y) const;

    void set_piece(int x, int y, Piece p);

    void set_piece(Square s, Piece p);

    void set_all_moves();

    void set_moves(Square s);

    void flip_pieces(Square start, Square end);
};


#endif  // REVERSI_REVERSIGAME_H
