// Copyright 2015 Tammo Behrends

#include "../src/direction.h"

#include <gtest/gtest.h>

TEST(DirectionTest, BaseTest) {
    Direction d = Direction::up;
    ASSERT_TRUE(d == Direction::up);
}