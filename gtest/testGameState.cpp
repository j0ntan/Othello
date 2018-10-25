#include "core/Board.hpp"
#include "core/GameState.hpp"
#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>
#include <vector>

TEST(testGameState, boardIsIndependantFromGameState) {
  Board board;
  board.placeTile(0, 0, OthelloCell::white);
  GameState gameState(board);
  EXPECT_EQ(gameState.board().cellAt(0, 0), board.cellAt(0, 0));

  board.flipTile(0, 0);
  EXPECT_NE(gameState.board().cellAt(0, 0), board.cellAt(0, 0));
}

TEST(testGameState, blackScoreIsZeroForEmptyBoard) {
  Board board;
  GameState gameState(board);
  EXPECT_EQ(0, gameState.blackScore());
}
