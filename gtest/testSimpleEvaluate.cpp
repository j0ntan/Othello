#include "core/Board.hpp"
#include "core/Evaluate.hpp"
#include "core/GameState.hpp"
#include <gtest/gtest.h>

TEST(testSimpleEvaluate, startingPositionScoresZero) {
  Board board;
  board.setCellAt(3, 3, OthelloCell::white);
  board.setCellAt(4, 3, OthelloCell::black);
  board.setCellAt(3, 4, OthelloCell::black);
  board.setCellAt(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_EQ(0, AI::simple::evaluate(&gameState, OthelloCell::black));
  EXPECT_EQ(0, AI::simple::evaluate(&gameState, OthelloCell::white));
}

TEST(testSimpleEvaluate, unequalPiecesScoresDifferently) {
  Board board;
  board.setCellAt(3, 3, OthelloCell::white);
  board.setCellAt(4, 3, OthelloCell::black);
  board.setCellAt(3, 4, OthelloCell::black);
  board.setCellAt(4, 4, OthelloCell::white);
  board.setCellAt(3, 2, OthelloCell::black);
  GameState gameState(board);

  EXPECT_EQ(1, AI::simple::evaluate(&gameState, OthelloCell::black));
  EXPECT_EQ(-1, AI::simple::evaluate(&gameState, OthelloCell::white));
}
