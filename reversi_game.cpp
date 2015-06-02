// Copyright 2015 Tammo Behrends

#include "./reversi_game.h"

#include <type_traits>
#include <array>

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

std::ostream& operator << (std::ostream& os, const Piece & p) {
    os << " ";
    switch (p) {
        case Piece::empty:
            os << "_";
            break;
        case Piece::black:
            os << "O";
            break;
        case Piece::white:
            os << "X";
            break;
    }
    return os;
}

void ReversiGame::set_possible_moves() {
    if (!possible_moves_.empty()) {
        possible_moves_.clear();
    }
}

Direction determine(const Square start, const Square end) {
    int delta_x = start.first - end.first;
    int delta_y = start.second - end.second;

    if (delta_x == 0) {
        return delta_y < 0 ? Direction::up : Direction::down;
    } else if (delta_y == 0) {
        return delta_x < 0 ? Direction::right : Direction::left;
    } else if (delta_x < 0) {
        return delta_y < 0 ? Direction::up_right : Direction::down_right;
    } else {
        return delta_y < 0 ? Direction::up_left : Direction::down_left;
    }
}


template <typename Enum>
auto as_integer(Enum const value) {
    return static_cast<typename std::underlying_type<Enum>::type>(value);
}

std::ostream &operator<<(std::ostream &os, const Direction &d) {
    static std::array<std::string,8> directionStrings {
            "UP",
            "UPLEFT",
            "UPRIGHT",
            "DOWN",
            "DOWNRIGHT",
            "DOWNLEFT",
            "LEFT",
            "RIGHT"
    };

    return os << directionStrings[as_integer(d)];
}
