// Copyright 2015 Tammo Behrends

#include "./reversi_game.h"

int main() {
    std::cout << "Hello, ReversiWorld!" << std::endl;

    ReversiGame game;
    game.displayBoard();

    for (auto m : game.get_moves()) {
        std::cout << "(" << m.first.x << "|" << m.first.y << ") -> ";
        for (auto s : m.second) {
            std::cout << "(" << s.x << "|" << s.y << ")";
        }
        std::cout << std::endl;
    }

    return 0;
}
