#include "core/Board.cpp"
#include "core/Board.hpp"
#include <gtest/gtest.h>

TEST(testBoard, defaultConstructedBoardIs8x8) {
  Board board;

  EXPECT_EQ(8, board.width());
  EXPECT_EQ(8, board.height());
}
