//
// Created by Tammo Behrends on 08.10.16.
//

#include <unistd.h>

#include "./reversi_player_thread.h"


ReversiPlayerThread::ReversiPlayerThread(std::unique_ptr<ReversiGame> g,
                                         IReversiPlayer *p) : game(std::move(g)) {
    game->display_board();
    player = p;
}

void ReversiPlayerThread::run() {
    sleep(3);
    Square s = player->think(*game);
    emit finished(s.x, s.y);
}