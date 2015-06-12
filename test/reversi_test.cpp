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
    EXPECT_EQ(Piece::white, default_game.get_piece({3, 4}));
    EXPECT_EQ(Piece::white, default_game.get_piece({4, 3}));
    EXPECT_EQ(Piece::black, default_game.get_piece({4, 4}));
    EXPECT_EQ(Piece::black, default_game.get_piece({3, 3}));

}

TEST_F(ReversiGameTest, Constructor) {
    ReversiGame game{16};
    ASSERT_EQ(16, game.board_size());
    EXPECT_EQ(Piece::empty, game.get_piece({0, 0}));
    EXPECT_EQ(Piece::empty, game.get_piece({15, 15}));
    EXPECT_EQ(Piece::white, game.get_piece({7, 8}));
    EXPECT_EQ(Piece::white, game.get_piece({8, 7}));
    EXPECT_EQ(Piece::black, game.get_piece({8, 8}));
    EXPECT_EQ(Piece::black, game.get_piece({7, 7}));

}

TEST_F(ReversiGameTest, ConstructorFail) {
    ASSERT_THROW(ReversiGame(15), std::out_of_range);
}

TEST_F(ReversiGameTest, PossibleMovesAtStart) {
    auto moves = default_game.get_moves();
    ASSERT_EQ(4, moves.size());

    // ToDo: would be better to check contains instead of exact position
    // ToDo: only start point is checked, not the end point
    EXPECT_EQ((Square{2, 3}), (moves[0].first));
    EXPECT_EQ((Square{3, 2}), (moves[1].first));
    EXPECT_EQ((Square{4, 5}), (moves[2].first));
    EXPECT_EQ((Square{5, 4}), (moves[3].first));
}

TEST_F(ReversiGameTest, ActivePlayerAtStart) {
    ASSERT_EQ(Piece::white, default_game.is_active());
}

TEST_F(ReversiGameTest, LongDefaultGame) {
    ReversiGame game;
    std::vector<Square> test_moves{{4,5}, {5,3}, {2,2}, {4,6}, {5,4}, {2,3}, {2,4},
                              {3,5}, {5,5}, {1,3}, {2,5}, {1,1}, {2,1}, {6,6},
                              {0,0}, {1,5}, {7,7}, {2,0}, {0,5}};

    for (auto m : test_moves)
        game.make_move(m);

    auto moves = game.get_moves();
    ASSERT_EQ(11, moves.size());

    EXPECT_EQ((Square{0, 1}), (moves[0].first));
    EXPECT_EQ((Square{2, 1}), (moves[0].second[0]));
    EXPECT_EQ((Square{0, 2}), (moves[1].first));
    EXPECT_EQ((Square{2, 0}), (moves[1].second[0]));
    EXPECT_EQ((Square{0, 6}), (moves[2].first));
    EXPECT_EQ((Square{2, 4}), (moves[2].second[0]));

    EXPECT_EQ((Square{2, 6}), (moves[4].first));
    ASSERT_EQ(2, moves[4].second.size());
    EXPECT_EQ((Square{2, 4}), (moves[4].second[0]));
    EXPECT_EQ((Square{5, 3}), (moves[4].second[1]));
    
    EXPECT_EQ((Square{3, 2}), (moves[5].first));
    EXPECT_EQ((Square{3, 4}), (moves[5].second[0]));
    EXPECT_EQ((Square{3, 6}), (moves[6].first));
    EXPECT_EQ((Square{3, 4}), (moves[6].second[0]));
    EXPECT_EQ((Square{4, 2}), (moves[7].first));
    EXPECT_EQ((Square{2, 4}), (moves[7].second[0]));

    EXPECT_EQ((Square{5, 6}), (moves[8].first));
    ASSERT_EQ(2, moves[8].second.size());
    EXPECT_EQ((Square{5, 3}), (moves[8].second[0]));
    EXPECT_EQ((Square{3, 4}), (moves[8].second[1]));

    EXPECT_EQ((Square{6, 4}), (moves[9].first));
    EXPECT_EQ((Square{3, 4}), (moves[9].second[0]));

    auto score = game.get_score();
    EXPECT_EQ(13, score.first);
    EXPECT_EQ(10, score.second);
}

TEST_F(ReversiGameTest, BlindFlightFullBoardGame) {
    ReversiGame game;
    int c = 0;
    
    while (true) {
        auto moves = game.get_moves();
        if (moves.size() == 0) break;
        auto move = (++c % 2) ? moves.front().first : moves.back().first;
        game.make_move(move);
    }
    
    EXPECT_EQ(60, c);
    EXPECT_EQ(0, game.get_moves().size());
    EXPECT_EQ(Piece::white, game.is_active());

    auto score = game.get_score();
    EXPECT_EQ(39, score.first);
    EXPECT_EQ(25, score.second);
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