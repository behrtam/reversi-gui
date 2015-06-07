// Copyright 2015 Tammo Behrends

#include "../src/reversi_game.h"

#include <gtest/gtest.h>

#include <stdexcept>

class ReversiGameTest : public testing::Test {
 protected:
    const ReversiGame default_game;
};


TEST_F(ReversiGameTest, DefaultConstructor) {
    ASSERT_EQ(8, default_game.board_size());
    EXPECT_EQ(Piece::empty, default_game.get_piece({0, 0}));
    EXPECT_EQ(Piece::empty, default_game.get_piece({7, 7}));
    EXPECT_EQ(Piece::black, default_game.get_piece({3, 4}));
    EXPECT_EQ(Piece::black, default_game.get_piece({4, 3}));
    EXPECT_EQ(Piece::white, default_game.get_piece({4, 4}));
    EXPECT_EQ(Piece::white, default_game.get_piece({3, 3}));

}

TEST_F(ReversiGameTest, Constructor) {
    ReversiGame game{16};
    ASSERT_EQ(16, game.board_size());
    EXPECT_EQ(Piece::empty, game.get_piece({0, 0}));
    EXPECT_EQ(Piece::empty, game.get_piece({15, 15}));
    EXPECT_EQ(Piece::black, game.get_piece({7, 8}));
    EXPECT_EQ(Piece::black, game.get_piece({8, 7}));
    EXPECT_EQ(Piece::white, game.get_piece({8, 8}));
    EXPECT_EQ(Piece::white, game.get_piece({7, 7}));

}

TEST_F(ReversiGameTest, ConstructorFail) {
    ASSERT_THROW(ReversiGame(15), std::out_of_range);
}

TEST_F(ReversiGameTest, PossibleMovesAtStart) {
    auto moves = default_game.get_moves();
    ASSERT_EQ(4, moves.size());

    // ToDo: would be better to check contains instead of exact position
    // ToDo: only start point is checked, not the end point
    EXPECT_EQ((Square{2, 4}), (moves[0].first));
    EXPECT_EQ((Square{3, 5}), (moves[1].first));
    EXPECT_EQ((Square{4, 2}), (moves[2].first));
    EXPECT_EQ((Square{5, 3}), (moves[3].first));
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

TEST_F(ReversiGameTest, ScoreAtStart) {
    auto score = default_game.get_score();
    EXPECT_EQ(2, score.first);
    EXPECT_EQ(2, score.second);
}

TEST_F(ReversiGameTest, Score) {
    ReversiGame game;
    game.make_move(game.get_moves()[0].first);
    auto score = game.get_score();
    EXPECT_EQ(4, score.first);
    EXPECT_EQ(1, score.second);
}

TEST_F(ReversiGameTest, GetPieceOutOfRange) {
    //EXPECT_THROW(default_game.get_piece(Square{-1, 0}), std::out_of_range);
    EXPECT_THROW(default_game.get_piece(Square{0, default_game.board_size()}), std::out_of_range);
    EXPECT_THROW(default_game.get_piece(Square{default_game.board_size(), 0}), std::out_of_range);
}