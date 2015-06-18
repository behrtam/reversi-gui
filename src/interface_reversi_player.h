// Copyright 2015 Tammo Behrends

#ifndef REVERSI_INTERFACE_REVERSI_PLAYER_H
#define REVERSI_INTERFACE_REVERSI_PLAYER_H


#include "./square.h"
#include "./reversi_game.h"

class IReversiPlayer {
 public:
    virtual Square think(const ReversiGame& game) = 0;
    virtual ~IReversiPlayer() {}
};


#endif  // REVERSI_INTERFACE_REVERSI_PLAYER_H
