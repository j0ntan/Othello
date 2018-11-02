#include "core/Board.hpp"
#include "core/Evaluate.hpp"
#include "core/GameState.hpp"
#include <gtest/gtest.h>
#include <utility>

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

TEST(testQuickMoveEval, scoresAreSymmetrical) {
  for (int x = 0; x < 8 / 2; ++x)
    for (int y = 0; y < 8 / 2; ++y)
      EXPECT_EQ(AI::quickMoveEval(std::make_pair(x, y)),
                AI::quickMoveEval(std::make_pair(y, x)));
}

TEST(testQuickMoveEval, cellHasCorrectScore) {
  EXPECT_EQ(AI::quickMoveEval(std::make_pair(0, 0)), 4);
  EXPECT_EQ(AI::quickMoveEval(std::make_pair(1, 1)), -4);
  EXPECT_EQ(AI::quickMoveEval(std::make_pair(4, 1)), -1);
  EXPECT_EQ(AI::quickMoveEval(std::make_pair(3, 5)), 0);
}
