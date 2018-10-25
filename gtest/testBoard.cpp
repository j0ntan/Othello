#include "core/Board.cpp"
#include "core/Board.hpp"
#include "othellogame/OthelloException.hpp"
#include <gtest/gtest.h>

TEST(testBoard, defaultConstructedBoardIs8x8) {
  Board board;

  EXPECT_EQ(8, board.width());
  EXPECT_EQ(8, board.height());
}

TEST(testBoard, canConstructDifferentSizeBoards) {
  Board board1(10), board2(12), board3(15);
}

TEST(testBoard, canConstructNonSquareBoards) {
  Board board1(3, 4), board2(4, 3);
}

TEST(testBoard, largerBoardReturnsCorrectSize) {
  const unsigned int size = 10;
  Board board(size);

  EXPECT_EQ(size, board.width());
  EXPECT_EQ(size, board.height());
}

TEST(testBoard, nonSquareBoardReturnsCorrectSize) {
  const unsigned int width = 4;
  const unsigned int height = 6;
  Board board(width, height);

  EXPECT_EQ(width, board.width());
  EXPECT_EQ(height, board.height());
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

TEST(testBoard, cellOutsideBorderThrowsException) {
  Board board;
  EXPECT_THROW(board.cellAt(board.width(), board.height()), OthelloException);
}

TEST(testBoard, setSingleCellAndVerify) {
  Board board;
  EXPECT_EQ(OthelloCell::empty, board.cellAt(0, 0));
  board.setCellAt(0, 0, OthelloCell::black);
  EXPECT_EQ(OthelloCell::black, board.cellAt(0, 0));
  board.setCellAt(0, 0, OthelloCell::white);
  EXPECT_EQ(OthelloCell::white, board.cellAt(0, 0));
}

TEST(testBoard, setInvalidCellThrowsException) {
  Board board;
  EXPECT_THROW(board.setCellAt(-1, -1, OthelloCell::white), OthelloException);
}

TEST(testBoard, placeTileInCellOnBoard) {
  Board board;
  EXPECT_EQ(OthelloCell::empty, board.cellAt(0, 0));
  board.placeTile(0, 0, OthelloCell::white);
  EXPECT_EQ(OthelloCell::white, board.cellAt(0, 0));
}

TEST(testBoard, placeTileInInvalidCellThrowsException) {
  Board board;
  EXPECT_THROW(board.placeTile(-1, -1, OthelloCell::white), OthelloException);
}

TEST(testBoard, placeTileInNonEmptyCellThrowsException) {
  Board board;
  EXPECT_EQ(OthelloCell::empty, board.cellAt(0, 0));
  board.placeTile(0, 0, OthelloCell::white);
  EXPECT_THROW(board.placeTile(0, 0, OthelloCell::black), OthelloException);
}

TEST(testBoard, flipAPlacedTile) {
  Board board;
  EXPECT_EQ(OthelloCell::empty, board.cellAt(0, 0));
  board.placeTile(0, 0, OthelloCell::white);
  EXPECT_EQ(OthelloCell::white, board.cellAt(0, 0));
  board.flipTile(0, 0);
  EXPECT_EQ(OthelloCell::black, board.cellAt(0, 0));
  board.flipTile(0, 0);
  EXPECT_EQ(OthelloCell::white, board.cellAt(0, 0));
}

TEST(testBoard, flipInvalidCellThrowsException) {
  Board board;
  EXPECT_THROW(board.flipTile(-1, -1), OthelloException);
}

TEST(testBoard, flipEmptyCellThrowsException) {
  Board board;
  EXPECT_EQ(OthelloCell::empty, board.cellAt(0,0));
  EXPECT_THROW(board.flipTile(0, 0), OthelloException);
}

TEST(testBoard, copyPopulatedBoard) {
  Board board;
  board.placeTile(0,0, OthelloCell::black);
  board.placeTile(1,1, OthelloCell::white);
  board.placeTile(2,2, OthelloCell::black);
  board.placeTile(3,3, OthelloCell::white);

  Board copy = board;
  EXPECT_EQ(OthelloCell::black, copy.cellAt(0,0));
  EXPECT_EQ(OthelloCell::white, copy.cellAt(1,1));
  EXPECT_EQ(OthelloCell::black, copy.cellAt(2,2));
  EXPECT_EQ(OthelloCell::white, copy.cellAt(3,3));
}
