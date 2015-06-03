// Copyright 2015 Tammo Behrends

#include "./direction.h"
#include "./reversi_game.h"

int main() {
    std::cout << "Hello, ReversiWorld!" << std::endl;

    ReversiGame game;
    game.displayBoard();

    Square start{2, 5};
    Square end{0, 7};

    std::cout << determine(start, end) << std::endl;

    return 0;
}
