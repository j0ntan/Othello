#include "core/Board.hpp"
#include "core/Evaluate.hpp"
#include "core/GameState.hpp"
#include "core/SimpleAI.hpp"
#include <gtest/gtest.h>

TEST(testEvaluate, startingPositionScoresZero) {
  Board board;
  board.setCellAt(3, 3, OthelloCell::white);
  board.setCellAt(4, 3, OthelloCell::black);
  board.setCellAt(3, 4, OthelloCell::black);
  board.setCellAt(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_EQ(0, AI::simple::evaluate(&gameState, OthelloCell::black));
  EXPECT_EQ(0, AI::simple::evaluate(&gameState, OthelloCell::white));
}
