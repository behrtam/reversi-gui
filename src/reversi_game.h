// Copyright 2015 Tammo Behrends

#ifndef REVERSI_REVERSIGAME_H
#define REVERSI_REVERSIGAME_H


#include <vector>
#include <utility>
#include <iostream>
#include <string>

#include "./piece.h"
#include "./square.h"

/**
 * The class ReversiGame represents a fraction with a numerator and denominator.
 * It provides functionality to calculate with fractions, to compare fractions
 * and some additional helper functions.
 */
class ReversiGame {
 private:
    /** The board size. */
    const unsigned int size_;

    /** The number of moves. */
    unsigned int moves_;

    /** The board. */
    std::vector<Piece> board_;

    /** All possible moves. */
    std::vector<std::pair<Square, std::vector<Square>>> possible_moves_;

    /** The active player. */
    Piece active_;

 public:
    /**
      * Initializes this ReversiGame instance with the default board size of 8.
      */
    ReversiGame() : ReversiGame(8) { }

    /**
      * Initializes this ReversiGame instance with the given board size
      * and white as starting player. The Size has to be at least 4, at most 16
      * and has to be even.
      * \param size    the board size.
      * \throw out_of_range if the size is incorrect.
      */
    explicit ReversiGame(unsigned int size) : ReversiGame(size, Piece::white) { }

    /**
      * Initializes this ReversiGame instance with the default board size of 8
      * and the given starting player.
      * \param starting_player    the starting player.
      */
    explicit ReversiGame(Piece starting_player) : ReversiGame(8, starting_player) { }

    /**
      * Initializes this ReversiGame instance with the given board size
      * and the given starting player. The Size has to be at least 4, at most 16
      * and has to be even.
      * \param size               the board size.
      * \param starting_player    the starting player.
      * \throw out_of_range if the size is incorrect.
      */
    ReversiGame(unsigned int size, Piece starting_player);

    /**
      * Initializes this ReversiGame instance with a given coded board,
      * the active player and the number of moves.
      * \param board            the string coded board.
      * \param active_player    the active player.
      * \param moves            the number of played moves.
      * \throw out_of_range if the size is incorrect.
      */
    ReversiGame(std::string board, Piece active_player, unsigned int moves);


    /**
     * Displayes the board in the commandline mostly for debuging purposes.
     */
    void display_board() const;

    /**
     * Returns the board size of this ReversiGame instance.
     * \return  the board size.
     */
    unsigned int board_size() const {
        return size_;
    }

    /**
     * Returns a string representing the board of this ReversiGame instance.
     * \return  the string representation.
     */
    std::string board2string() const;

    /**
     * Returns the current score of this ReversiGame instance as a pair.
     * The stone count for black is first in the pair, white second.
     * \return  the score.
     */
    std::pair<unsigned int, unsigned int> get_score() const;

    /**
     * Returns the Piece (black, white, empty) for a given Square.
     * \return  the piece.
     */
    Piece get_piece(Square s) const;

    /**
     * Returns all possible moves as a vector.
     * \return  all possible moves.
     */
    auto possible_moves() const { return possible_moves_; }

    /**
     * Checks whether a move on the given Square is possible.
     * \return  true, if it would be a valid move; otherwise false.
     */
    bool is_valid_move(Square s) const;

    /**
     * Makes a move for the current player on the given Square. Also calls functions
     * to flip all stones and to update the possible moves.
     */
    void make_move(Square s);

    /**
     * Checks if there still are possible moves to be played.
     * \return  true, if there are still moves; otherwise false.
     */
    bool moves_possible() const { return !possible_moves_.empty(); }

    /**
     * Returns the Piece of the active player (white or black).
     * \return  the active player.
     */
    Piece is_active() const { return active_; }

    /**
     * Returns the number of moves that have already been played.
     * \return  the number of moves.
     */
    unsigned int moves() const { return moves_; }

 private:
    /**
      * Returns the Piece for the given x and y coordinate.
      * \return the Pice.
      * \throw out_of_range if the coordinates are incorrect.
      */
    Piece get_piece(unsigned int x, unsigned int y) const;

    /**
      * Sets the given Piece on the board for the given x and y coordinate.
      * \throw out_of_range if the coordinates are incorrect.
      */
    void set_piece(unsigned int x, unsigned int y, Piece p);

    /**
      * Sets the given Piece on the board for the given Square.
      * \throw out_of_range if the coordinates are incorrect.
      */
    void set_piece(Square s, Piece p);

    /**
     * Updates the list of all possible moves.
     */
    void set_all_moves();

    /**
     * Checks all eight directions for possible flips for the given Square.
     * \param s     the square.
     */
    void set_moves(Square s);

    /**
     * Flips all pieces between the given start and end Square.
     * \param start  the starting point.
     * \param end    the end point.
     */
    void flip_pieces(Square start, Square end);
};


#endif  // REVERSI_REVERSIGAME_H
