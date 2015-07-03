// Copyright 2015 Tammo Behrends

#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <string>

#include "./reversi_game.h"
#include "./utils.h"


ReversiGame::ReversiGame(unsigned int size, Piece starting_player)
        : size_(size), board_(size * size), moves_(0) {
    if (size < 4 || size > 16 || size % 2 == 1)
        throw std::out_of_range{"ReversiGame(int)"};

    set_piece(size_ / 2, size_ / 2, Piece::black);
    set_piece(size_ / 2 - 1, size_ / 2 - 1, Piece::black);
    set_piece(size_ / 2 - 1, size_ / 2, Piece::white);
    set_piece(size_ / 2, size_ / 2 - 1, Piece::white);

    active_ = starting_player;
    set_all_moves();
}

ReversiGame::ReversiGame(std::string board, Piece active_player, unsigned int moves)
        : ReversiGame(static_cast<unsigned int>(sqrt(board.size())), active_player) {
    moves_ = moves;

    for (unsigned int i = 0; i < board.size(); ++i) {
        if (board[i] == '1') {
            set_piece({i % size_, i / size_}, Piece::black);
        } else if (board[i] == '2') {
            set_piece({i % size_, i / size_}, Piece::white);
        }
    }
    set_all_moves();
}


void ReversiGame::display_board() const {
    for (unsigned int y = size_; y-- > 0; ) {
        std::cout << y;
        for (unsigned int x = 0; x < size_; ++x) {
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

Piece ReversiGame::get_piece(unsigned int x, unsigned int y) const {
    if (x >= size_ || y >= size_)
        throw std::out_of_range{"get_piece(int, int)"};
    return board_.at(x + y * size_);
}

Piece ReversiGame::get_piece(Square s) const {
    return get_piece(s.x, s.y);
}

void ReversiGame::set_piece(Square s, Piece p) {
    set_piece(s.x, s.y, p);
}

void ReversiGame::set_piece(unsigned int x, unsigned int y, Piece p) {
    if (x >= size_ || y >= size_)
        throw std::out_of_range{"set_piece(int, int, Piece)"};
    board_[x + y * size_] = p;
}

void ReversiGame::set_all_moves() {
    possible_moves_.clear();

    for (unsigned int x = 0; x < size_; ++x) {
        for (unsigned int y = 0; y < size_; ++y) {
            if (get_piece(x, y) != Piece::empty) continue;
            set_moves({x, y});
        }
    }
}

void ReversiGame::set_moves(Square s) {
    std::vector<Square> destinations;

    // up check
    if ((s.y < (size_ - 2)) && get_piece(s.x, s.y + 1) == invert(active_)) {
        for (unsigned int i = s.y + 2; i < size_; ++i) {
            if (get_piece(s.x, i) == Piece::empty) break;
            if (get_piece(s.x, i) == active_) {
                destinations.push_back({s.x, i});
                break;
            }
        }
    }

    // down check
    if ((s.y > 1) && get_piece(s.x, s.y - 1) == invert(active_)) {
        for (unsigned int i = s.y - 1; i-- > 0; ) {
            if (get_piece(s.x, i) == Piece::empty) break;
            if (get_piece(s.x, i) == active_) {
                destinations.push_back({s.x, i});
                break;
            }
        }
    }

    // right check
    if ((s.x < (size_ - 2)) && get_piece(s.x + 1, s.y) == invert(active_)) {
        for (unsigned int i = s.x + 2; i < size_; ++i) {
            if (get_piece(i, s.y) == Piece::empty) break;
            if (get_piece(i, s.y) == active_) {
                destinations.push_back({i, s.y});
                break;
            }
        }
    }

    // left check
    if ((s.x > 1) && get_piece(s.x - 1, s.y) == invert(active_)) {
        for (unsigned int i = s.x - 1; i-- > 0; ) {
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
        for (unsigned int i = 2; ((s.x + i) < size_) && ((s.y + i) < size_); i++) {
            if (get_piece(s.x + i, s.y + i) == Piece::empty) break;
            if (get_piece(s.x + i, s.y + i) == active_) {
                destinations.push_back({s.x + i, s.y + i});
                break;
            }
        }
    }

    // down-right check
    if ((s.y > 1) && (s.x < (size_ - 2)) && get_piece(s.x + 1, s.y - 1) == invert(active_)) {
        for (unsigned int i = 2; (s.x + i < size_) && ((s.y - i + 1) > 0); i++) {
            if (get_piece(s.x + i, s.y - i) == Piece::empty) break;
            if (get_piece(s.x + i, s.y - i) == active_) {
                destinations.push_back({s.x + i, s.y - i});
                break;
            }
        }
    }

    // down-left check
    if ((s.y > 1) && (s.x > 1) && get_piece(s.x - 1, s.y - 1) == invert(active_)) {
        for (unsigned int i = 2; ((s.x - i + 1) > 0) && ((s.y - i + 1) > 0); i++) {
            if (get_piece(s.x - i, s.y - i) == Piece::empty) break;
            if (get_piece(s.x - i, s.y - i) == active_) {
                destinations.push_back({s.x - i, s.y - i});
                break;
            }
        }
    }

    // up-left check
    if ((s.y < (size_ - 2)) && (s.x > 1) && get_piece(s.x - 1, s.y + 1) == invert(active_)) {
        for (unsigned int i = 2; ((s.x - i + 1) > 0) && ((s.y + i) < size_); i++) {
            if (get_piece(s.x - i, s.y + i) == Piece::empty) break;
            if (get_piece(s.x - i, s.y + i) == active_) {
                destinations.push_back({s.x - i, s.y + i});
                break;
            }
        }
    }

    if (!destinations.empty())
        possible_moves_.push_back({s, destinations});
}

void ReversiGame::make_move(Square s) {
    auto moves = std::find_if(std::begin(possible_moves_), std::end(possible_moves_),
                               [&s](const auto &item) { return item.first == s; });
    if (moves != std::end(possible_moves_)) {
        set_piece(s, active_);
        for (auto end : (*moves).second) {
            flip_pieces((*moves).first, end);
        }
        active_ = invert(active_);
        ++moves_;
        set_all_moves();
    }
}

bool ReversiGame::is_valid_move(Square s) const {
    return std::find_if(
            std::begin(possible_moves_),
            std::end(possible_moves_),
            [&s](const auto &item) { return item.first == s; }) != std::end(possible_moves_);
}

void ReversiGame::flip_pieces(Square start, Square end) {
    while (start != end) {
        if (start.x > end.x) start.x--;
        else if (start.x < end.x) start.x++;
        if (start.y > end.y) start.y--;
        else if (start.y < end.y) start.y++;
        set_piece(start, active_);
    }
}

std::pair<unsigned int, unsigned int> ReversiGame::get_score() const {
    std::pair<unsigned int, unsigned int> score{0, 0};
    for (Piece p : board_) {
        if (p == Piece::white)
            ++score.first;
        else if (p == Piece::black)
            ++score.second;
    }
    return score;
}

std::string ReversiGame::board2string() const {
    std::string board(size_ * size_, '0');
    for (int i = 0; i < board_.size(); ++i) {
        if (board_[i] == Piece::white)
            board[i] = '2';
        else if (board_[i] == Piece::black)
            board[i] = '1';
    }
    return board;
}
