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

TEST(testBoard, checkAllValidCells) {
  const unsigned int default_size = 8;
  Board board1;
  for (int x = 0; x < default_size; ++x)
    for (int y = 0; y < default_size; ++y)
      ASSERT_TRUE(board1.isValidCell(x, y));

  const unsigned int larger_size = 12;
  Board board2(larger_size);
  for (int x = 0; x < larger_size; ++x)
    for (int y = 0; y < larger_size; ++y)
      ASSERT_TRUE(board2.isValidCell(x, y));
}

TEST(testBoard, checkCellsOutsideBorderInvalid) {
  const unsigned int default_size = 8;
  Board board;

  // cells above top edge & below bottom edge
  for (int x = 0; x < default_size; ++x) {
    EXPECT_FALSE(board.isValidCell(x, -1));
    EXPECT_FALSE(board.isValidCell(x, board.height()));
  }
  // cells left of left edge & right of right  edge
  for (int y = 0; y < default_size; ++y) {
    EXPECT_FALSE(board.isValidCell(-1, y));
    EXPECT_FALSE(board.isValidCell(board.width(), y));
  }
}

TEST(testBoard, defaultConstructedBoardHasAllEmptyCells) {
  Board board;

  for (int x = 0; x < board.width(); ++x)
    for (int y = 0; y < board.height(); ++y)
      EXPECT_EQ(OthelloCell::empty, board.cellAt(x, y));
}
