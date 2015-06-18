// Copyright 2015 Tammo Behrends

#ifndef REVERSI_RANDOM_PLAYER_H
#define REVERSI_RANDOM_PLAYER_H


#include "./interface_reversi_player.h"

class RandomReversiPlayer : public IReversiPlayer {
 public:
    Square think(const ReversiGame& game) override;
};


#endif  // REVERSI_RANDOM_PLAYER_H
