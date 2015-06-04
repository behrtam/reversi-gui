// Copyright 2015 Tammo Behrends

#include <vector>

#include "./reversi_game.h"

void ReversiGame::displayBoard() const {
    for (int y = size_ - 1; y >= 0; --y) {
        std::cout << y;
        for (int x = 0; x < size_; ++x) {
            std::cout << " " << get_piece(x, y);
        }
        std::cout << std::endl;
    }
    std::cout << " ";
    for (int x = 0; x < size_; ++x) {
        std::cout << " " << x;
    }
    std::cout << std::endl;
}

Piece ReversiGame::get_piece(int x, int y) const {
    return board_.at(x + y * size_);
}


Piece ReversiGame::get_piece(Square s) const {
    return get_piece(s.x, s.y);
}

void ReversiGame::set_piece(Square s, Piece p) {
    set_piece(s.x, s.y, p);
}

void ReversiGame::set_piece(int x, int y, Piece p) {
    board_[x + y * size_] = p;
}

void ReversiGame::set_all_moves() {
    possible_moves_.clear();

    for (int x = 0; x < size_; ++x) {
        for (int y = 0; y < size_; ++y) {
            if (get_piece(x, y) != Piece::empty) continue;
            set_moves({x, y});
        }
    }
}

void ReversiGame::set_moves(Square s) {
    std::vector<Square> destinations;

    // up check
    if ((s.y < (size_ - 2)) && get_piece(s.x, s.y + 1) == invert(active_)) {
        for (int i = s.y + 2; i < size_; ++i) {
            if (get_piece(s.x, i) == Piece::empty) break;
            if (get_piece(s.x, i) == active_) {
                destinations.push_back({s.x, i});
                break;
            }
        }
    }

    // down check
    if ((s.y > 1) && get_piece(s.x, s.y - 1) == invert(active_)) {
        for (int i = s.y - 2; i >= 0; --i) {
            if (get_piece(s.x, i) == Piece::empty) break;
            if (get_piece(s.x, i) == active_) {
                destinations.push_back({s.x, i});
                break;
            }
        }
    }

    // right check
    if ((s.x < (size_ - 2)) && get_piece(s.x + 1, s.y) == invert(active_)) {
        for (int i = s.x + 2; i < size_; ++i) {
            if (get_piece(i, s.y) == Piece::empty) break;
            if (get_piece(i, s.y) == active_) {
                destinations.push_back({i, s.y});
                break;
            }
        }
    }

    // left check
    if ((s.x > 1) && get_piece(s.x - 1, s.y) == invert(active_)) {
        for (int i = s.x - 2; i >= 0; --i) {
            if (get_piece(i, s.y) == Piece::empty) break;
            if (get_piece(i, s.y) == active_) {
                destinations.push_back({i, s.y});
                break;
            }
        }
    }

    // up-right check
    if ((s.y < (size_ - 2)) && (s.x < (size_ - 2))
        && get_piece(s.x + 1, s.y + 1) == invert(active_)) {
        for (int i=0; (s.x + i + 2 < (size_ - 2)) && (s.y + i + 2 < (size_ - 2)); i++) {
            if (get_piece(s.x + i + 2, s.y + i + 2) == Piece::empty) break;
            if (get_piece(s.x + i + 2, s.y + i + 2) == active_) {
                destinations.push_back({s.x + i + 2, s.y + i + 2});
                break;
            }
        }
    }

    // down-right check
    if ((s.y > 1) && (s.x < (size_ - 2)) && get_piece(s.x + 1, s.y - 1) == invert(active_)) {
        for (int i=0; (s.x + i + 2 < (size_ - 2)) && (s.y + i + 2 >= 0); i++) {
            if (get_piece(s.x + i + 2, s.y - i - 2) == Piece::empty) break;
            if (get_piece(s.x + i + 2, s.y - i - 2) == active_) {
                destinations.push_back({s.x + i + 2, s.y - i - 2});
                break;
            }
        }
    }

    // down-left check
    if ((s.y > 1) && (s.x > 1) && get_piece(s.x - 1, s.y - 1) == invert(active_)) {
        for (int i=0; (s.x + i + 2 >= 0) && (s.y + i + 2 >= 0); i++) {
            if (get_piece(s.x - i - 2, s.y - i - 2) == Piece::empty) break;
            if (get_piece(s.x - i - 2, s.y - i - 2) == active_) {
                destinations.push_back({s.x - i - 2, s.y - i - 2});
                break;
            }
        }
    }

    // up-left check
    if ((s.y < (size_ - 2)) && (s.x > 1) && get_piece(s.x - 1, s.y + 1) == invert(active_)) {
        for (int i = 0; (s.x - i - 2 >= 0) && (s.y + i + 2 < (size_ - 2)); i++) {
            if (get_piece(s.x + i +2, s.y + i + 2) == Piece::empty) break;
            if (get_piece(s.x - i - 2, s.y + i + 2) == active_) {
                destinations.push_back({s.x - i - 2, s.y + i + 2});
                break;
            }
        }
    }

    if (!destinations.empty())
        possible_moves_.push_back({s, destinations});
}
