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
    unsigned int moves_;
    std::vector<Piece> board_;
    std::vector<std::pair<Square, std::vector<Square>>> possible_moves_;
    Piece active_;

 public:
    ReversiGame() : ReversiGame(8) { }

    explicit ReversiGame(unsigned int size);

    void display_board() const;

    unsigned int board_size() const {
        return size_;
    }

    std::pair<unsigned int, unsigned int> get_score() const;

    Piece get_piece(Square s) const;

    auto possible_moves() const { return possible_moves_; }

    bool is_valid_move(Square s) const;

    void make_move(Square s);

    bool moves_possible() const { return !possible_moves_.empty(); }

    Piece is_active() const { return active_; }

    unsigned int moves() const { return moves_; }

 private:
    Piece get_piece(unsigned int x, unsigned int y) const;

    void set_piece(unsigned int x, unsigned int y, Piece p);

    void set_piece(Square s, Piece p);

    void set_all_moves();

    void set_moves(Square s);

    void flip_pieces(Square start, Square end);
};


#endif  // REVERSI_REVERSIGAME_H
