// Copyright 2015 Tammo Behrends

#include "./reversi_game.h"


int main() {
    std::cout << "Hello, ReversiWorld!" << std::endl;

    Square start{2, 5};
    Square end{0, 7};

    std::cout << determine(start, end) << std::endl;

    return 0;
}
