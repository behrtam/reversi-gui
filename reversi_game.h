        // Copyright 2015 Tammo Behrends

#ifndef REVERSI_REVERSIGAME_H
#define REVERSI_REVERSIGAME_H

#include <vector>
#include <iostream>

enum class Piece { empty, black, white };
enum class Direction { up, up_left, up_right, down, down_right, down_left, left, right };
typedef std::pair<int, int> Square;


std::ostream& operator << (std::ostream& os, const Direction & d);
std::ostream& operator << (std::ostream& os, const Piece & p);
Direction determine(const Square start, const Square end);


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
