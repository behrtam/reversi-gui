// Copyright 2015 Tammo Behrends

#include "./reversi_game.h"


int main() {
    std::cout << "Hello, Reversi!" << std::endl;

    ReversiGame game;
    game.displayBoard();

    while (game.moves_possible()) {
        for (auto m : game.get_moves()) {
            std::cout << "(" << m.first.x << "|" << m.first.y << ") -> ";
            for (auto s : m.second) {
                std::cout << "(" << s.x << "|" << s.y << ")";
            }
            std::cout << std::endl;
        }
        int x, y;
        std::cout << "turn: " << game.is_active() << std::endl;
        std::cin >> x >> y;
        game.make_move({x, y});
        game.displayBoard();
    }

    return 0;
}
