// Copyright 2015 Tammo Behrends

#include "../src/reversi_game.h"

#include <gtest/gtest.h>

class ReversiGameTest : public testing::Test {
 protected:
    const ReversiGame default_game;
};


TEST_F(ReversiGameTest, DefaultConstructor) {
    ASSERT_EQ(Piece::empty, default_game.get_piece({0, 0}));
    ASSERT_EQ(Piece::empty, default_game.get_piece({7, 7}));
    ASSERT_EQ(Piece::black, default_game.get_piece({3, 4}));
    ASSERT_EQ(Piece::black, default_game.get_piece({4, 3}));
    ASSERT_EQ(Piece::white, default_game.get_piece({4, 4}));
    ASSERT_EQ(Piece::white, default_game.get_piece({3, 3}));
    ASSERT_EQ(8, default_game.board_size());
}

TEST_F(ReversiGameTest, Constructor) {
    ReversiGame game{16};
    ASSERT_EQ(Piece::empty, game.get_piece({0, 0}));
    ASSERT_EQ(Piece::empty, game.get_piece({15, 15}));
    ASSERT_EQ(Piece::black, game.get_piece({7, 8}));
    ASSERT_EQ(Piece::black, game.get_piece({8, 7}));
    ASSERT_EQ(Piece::white, game.get_piece({8, 8}));
    ASSERT_EQ(Piece::white, game.get_piece({7, 7}));
    ASSERT_EQ(16, game.board_size());
}

TEST_F(ReversiGameTest, PossibleMovesAtStart) {
    auto moves = default_game.get_moves();
    ASSERT_EQ(4, moves.size());

    // ToDo: would be better to check contains instead of exact position
    // ToDo: only start point is checked, not the end point
    ASSERT_EQ((Square{2, 4}), (moves[0].first));
    ASSERT_EQ((Square{3, 5}), (moves[1].first));
    ASSERT_EQ((Square{4, 2}), (moves[2].first));
    ASSERT_EQ((Square{5, 3}), (moves[3].first));
}

TEST_F(ReversiGameTest, ActivePlayerAtStart) {
    ASSERT_EQ(Piece::white, default_game.is_active());
}

TEST_F(ReversiGameTest, ActivePlayer) {
    ReversiGame game;
    game.make_move(game.get_moves()[0].first);
    ASSERT_EQ(Piece::black, game.is_active());
}

TEST_F(ReversiGameTest, ActivePlayerAfterImpossibleMove) {
    ReversiGame game;
    game.make_move({0, 0});
    ASSERT_EQ(Piece::white, game.is_active());
}

TEST_F(ReversiGameTest, ValidMove) {
    ASSERT_TRUE(default_game.is_valid_move(default_game.get_moves()[0].first));
}

TEST_F(ReversiGameTest, ValidMoveNegative) {
    ASSERT_FALSE(default_game.is_valid_move({0, 0}));
}
