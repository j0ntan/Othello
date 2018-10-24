#include "core/Board.cpp"
#include "core/Board.hpp"
#include <gtest/gtest.h>

TEST(testBoard, defaultConstructedBoardIs8x8) {
  Board board;

  EXPECT_EQ(8, board.width());
  EXPECT_EQ(8, board.height());
}

TEST(testBoard, canConstructDifferentSizeBoards) {
  Board board1(10), board2(12), board3(15);
}

TEST(testBoard, largerBoardReturnsCorrectSize) {
  const unsigned int size = 10;
  Board board(size);

  EXPECT_EQ(size, board.width());
  EXPECT_EQ(size, board.height());
}
