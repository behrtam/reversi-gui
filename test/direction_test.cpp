// Copyright 2015 Tammo Behrends

#include "../src/direction.h"
#include "../src/square.h"

#include <gtest/gtest.h>
#include <sstream>


TEST(DirectionTest, BaseTest) {
    Direction d = Direction::up;
    ASSERT_TRUE(d == Direction::up);
}

TEST(DirectionTest, DeterminUp) {
    ASSERT_EQ(Direction::up, determine({3, 3}, {3, 5}));
}

TEST(DirectionTest, DeterminDown) {
    ASSERT_EQ(Direction::down, determine({3, 3}, {3, 1}));
}

TEST(DirectionTest, DeterminRight) {
    ASSERT_EQ(Direction::right, determine({3, 3}, {5, 3}));
}

TEST(DirectionTest, DeterminLeft) {
    ASSERT_EQ(Direction::left, determine({3, 3}, {1, 3}));
}

TEST(DirectionTest, DeterminUpLeft) {
    ASSERT_EQ(Direction::up_left, determine({3, 3}, {0, 6}));
}

TEST(DirectionTest, DeterminDownLeft) {
    ASSERT_EQ(Direction::down_left, determine({3, 3}, {0, 0}));
}

TEST(DirectionTest, DeterminUpRight) {
    ASSERT_EQ(Direction::up_right, determine({3, 3}, {6, 6}));
}

TEST(DirectionTest, DeterminDownRight) {
    ASSERT_EQ(Direction::down_right, determine({3, 3}, {6, 0}));
}

TEST(DirectionTest, DownToString) {
    std::stringstream ss;
    ss << Direction::down;
    ASSERT_EQ("DOWN", ss.str());
}

TEST(DirectionTest, DownLeftToString) {
    std::stringstream ss;
    ss << Direction::down_left;
    ASSERT_EQ("DOWNLEFT", ss.str());
}