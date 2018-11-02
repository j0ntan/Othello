#include "core/Board.hpp"
#include "core/Evaluate.hpp"
#include "core/GameState.hpp"
#include <gtest/gtest.h>

TEST(testStrongerEvaluate, startingPositionScoresAreEqual) {
  Board board;
  board.setCellAt(3, 3, OthelloCell::white);
  board.setCellAt(4, 3, OthelloCell::black);
  board.setCellAt(3, 4, OthelloCell::black);
  board.setCellAt(4, 4, OthelloCell::white);
  GameState gameState1(board), gameState2(board, false);

  EXPECT_EQ(AI::stronger::evaluate(&gameState1, OthelloCell::black),
            AI::stronger::evaluate(&gameState2, OthelloCell::white));
}
