// Copyright 2015 Tammo Behrends

#include "./random_reversi_player.h"

#include <random>
#include <algorithm>
#include <iterator>


Square RandomReversiPlayer::think(const ReversiGame& game) {
    static std::random_device rd;
    static std::mt19937 g(rd());

    auto moves = game.get_moves();
    std::shuffle(moves.begin(), moves.end(), g);
    return moves.front().first;
}
