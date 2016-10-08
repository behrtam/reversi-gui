//
// Created by Tammo Behrends on 08.10.16.
//

#ifndef REVERSI_REVERSI_PLAYER_THREAD_H
#define REVERSI_REVERSI_PLAYER_THREAD_H

#include <QThread>

#include "./reversi_game.h"
#include "./square.h"
#include "./interface_reversi_player.h"

#include <memory>


class ReversiPlayerThread : public QThread {
    Q_OBJECT

public:
    ReversiPlayerThread(std::unique_ptr<ReversiGame> g, IReversiPlayer* p);
    void run();

signals:
    void finished(unsigned int, unsigned int);

private:
    IReversiPlayer* player = nullptr;
    std::unique_ptr<ReversiGame> game;
};


#endif //REVERSI_REVERSI_PLAYER_THREAD_H
