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

TEST(testStrongerEvaluate, blackScoresHigherMobilityForAdvantageousBoard) {
  const char cells1[8][8] = {{' ', 'w', 'w', 'w', 'w', 'w', 'w', ' '},
                             {' ', ' ', 'w', 'w', 'w', 'w', ' ', ' '},
                             {'w', 'w', 'b', 'w', 'w', 'b', 'w', ' '},
                             {'w', 'w', 'b', 'w', 'w', 'w', 'w', ' '},
                             {'w', 'w', 'b', 'b', 'b', 'w', ' ', ' '},
                             {' ', 'w', 'w', 'w', 'b', 'w', ' ', ' '},
                             {' ', ' ', 'w', 'b', 'w', 'w', ' ', ' '},
                             {' ', ' ', 'w', 'w', ' ', 'w', ' ', ' '}};

  const char cells2[8][8] = {{' ', ' ', 'w', ' ', ' ', 'w', ' ', ' '},
                             {' ', ' ', 'w', 'w', 'w', 'w', ' ', ' '},
                             {'w', 'w', 'b', 'b', 'b', 'w', ' ', ' '},
                             {'w', 'b', 'b', 'b', 'w', 'w', ' ', ' '},
                             {'w', 'w', 'w', 'b', 'w', ' ', ' ', ' '},
                             {'w', 'w', 'w', 'b', 'w', ' ', ' ', ' '},
                             {' ', ' ', 'b', 'b', 'b', 'w', ' ', ' '},
                             {' ', 'b', 'b', 'b', 'b', 'b', 'b', ' '}};
  Board board1, board2;
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y) {
      if (cells1[y][x] == 'b')
        board1.setCellAt(x, y, OthelloCell::black);
      else if (cells1[y][x] == 'w')
        board1.setCellAt(x, y, OthelloCell::white);
      if (cells2[y][x] == 'b')
        board2.setCellAt(x, y, OthelloCell::black);
      else if (cells2[y][x] == 'w')
        board2.setCellAt(x, y, OthelloCell::white);
    }
  GameState gameState1(board1), gameState2(board1, false), gameState3(board2),
      gameState4(board2, false);
  EXPECT_GT(AI::stronger::evaluate(&gameState1, OthelloCell::black),
            AI::stronger::evaluate(&gameState2, OthelloCell::white));
  EXPECT_GT(AI::stronger::evaluate(&gameState3, OthelloCell::black),
            AI::stronger::evaluate(&gameState4, OthelloCell::white));
}

TEST(testStrongerEvaluate, negatedScoreWhenCurrentPlayerIsNotChooser) {
  const char cells[8][8] = {{' ', 'w', 'w', 'w', 'w', 'w', 'w', ' '},
                            {' ', ' ', 'w', 'w', 'w', 'w', ' ', ' '},
                            {'w', 'w', 'b', 'w', 'w', 'b', 'w', ' '},
                            {'w', 'w', 'b', 'w', 'w', 'w', 'w', ' '},
                            {'w', 'w', 'b', 'b', 'b', 'w', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', 'w', ' ', ' '},
                            {' ', ' ', 'w', 'b', 'w', 'w', ' ', ' '},
                            {' ', ' ', 'w', 'w', ' ', 'w', ' ', ' '}};
  Board board;
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (cells[y][x] == 'b')
        board.setCellAt(x, y, OthelloCell::black);
      else if (cells[y][x] == 'w')
        board.setCellAt(x, y, OthelloCell::white);
  GameState gameState(board, false);
  EXPECT_EQ(AI::stronger::evaluate(&gameState, OthelloCell::black),
            AI::stronger::evaluate(&gameState, OthelloCell::white) * -1);
}

TEST(testStrongerEvaluate, occupyingCornersIncreasesScore) {
  int previous_score = 0, current_score = 0;
  Board board;

  board.setCellAt(0, 0, OthelloCell::black);
  GameState gameState1(board);
  current_score = AI::stronger::evaluate(&gameState1, OthelloCell::black);
  EXPECT_GT(current_score, previous_score);

  board.setCellAt(7, 0, OthelloCell::black);
  GameState gameState2(board);
  previous_score = current_score;
  current_score = AI::stronger::evaluate(&gameState2, OthelloCell::black);
  EXPECT_GT(current_score, previous_score);

  board.setCellAt(0, 7, OthelloCell::black);
  GameState gameState3(board);
  previous_score = current_score;
  current_score = AI::stronger::evaluate(&gameState3, OthelloCell::black);
  EXPECT_GT(current_score, previous_score);

  board.setCellAt(7, 7, OthelloCell::black);
  GameState gameState4(board);
  previous_score = current_score;
  current_score = AI::stronger::evaluate(&gameState4, OthelloCell::black);
  EXPECT_GT(current_score, previous_score);
}

TEST(testStrongerEvaluate, negativeScoreWhenOpponentHasMoreCorners) {
  Board board;
  board.setCellAt(0, 0, OthelloCell::black);
  board.setCellAt(7, 0, OthelloCell::white);
  board.setCellAt(0, 7, OthelloCell::white);
  board.setCellAt(7, 7, OthelloCell::white);
  GameState gameState(board);
  EXPECT_LT(AI::stronger::evaluate(&gameState, OthelloCell::black), 0);
}

TEST(testStrongerEvaluate, detectStableCellsInTopLeftCorner) {
  Board board;
  board.setCellAt(0, 0, OthelloCell::black);
  GameState gameState_just_the_corner(board);

  const char cells[8][8] = {{'b', 'b', 'b', 'b', 'b', 'b', ' ', ' '},
                            {'b', 'b', 'b', ' ', ' ', ' ', ' ', ' '},
                            {'b', 'b', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', 'b', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (cells[y][x] == 'b')
        board.setCellAt(x, y, OthelloCell::black);
  GameState gameState_adjacent_stable_cells(board);

  EXPECT_GT(
      AI::stronger::evaluate(&gameState_adjacent_stable_cells,
                             OthelloCell::black),
      AI::stronger::evaluate(&gameState_just_the_corner, OthelloCell::black));
}

TEST(testStrongerEvaluate, zeroStableScoreForTopLeftEdgeWithoutCorner) {
  Board board;
  const char cells[8][8] = {{' ', ' ', 'b', 'b', 'b', 'b', ' ', ' '},
                            {'b', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (cells[y][x] == 'b')
        board.setCellAt(x, y, OthelloCell::black);
  GameState gameState_adjacent_without_corner(board);

  EXPECT_EQ(AI::stronger::evaluate(&gameState_adjacent_without_corner,
                                   OthelloCell::black),
            0);
}

TEST(testStrongerEvaluate, detectStableCellsInTopRightCorner) {
  Board board;
  board.setCellAt(7, 0, OthelloCell::black);
  GameState gameState_just_the_corner(board);

  const char cells[8][8] = {{' ', ' ', 'b', 'b', 'b', 'b', 'b', 'b'},
                            {' ', ' ', ' ', ' ', ' ', 'b', 'b', 'b'},
                            {' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},
                            {' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (cells[y][x] == 'b')
        board.setCellAt(x, y, OthelloCell::black);
  GameState gameState_adjacent_stable_cells(board);

  EXPECT_GT(
      AI::stronger::evaluate(&gameState_adjacent_stable_cells,
                             OthelloCell::black),
      AI::stronger::evaluate(&gameState_just_the_corner, OthelloCell::black));
}

TEST(testStrongerEvaluate, detectStableCellsInBottomLeftCorner) {
  Board board;
  board.setCellAt(0, 7, OthelloCell::black);
  GameState gameState_just_the_corner(board);

  const char cells[8][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', 'b', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', 'b', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', 'b', 'b', ' ', ' ', ' ', ' ', ' '},
                            {'b', 'b', 'b', 'b', 'b', 'b', ' ', ' '}};
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (cells[y][x] == 'b')
        board.setCellAt(x, y, OthelloCell::black);
  GameState gameState_adjacent_stable_cells(board);

  EXPECT_GT(
      AI::stronger::evaluate(&gameState_adjacent_stable_cells,
                             OthelloCell::black),
      AI::stronger::evaluate(&gameState_just_the_corner, OthelloCell::black));
}

TEST(testStrongerEvaluate, detectStableCellsInBottomRightCorner) {
  Board board;
  board.setCellAt(7, 7, OthelloCell::black);
  GameState gameState_just_the_corner(board);

  const char cells[8][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b'},
                            {' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},
                            {' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},
                            {' ', ' ', ' ', ' ', ' ', 'b', 'b', 'b'},
                            {' ', ' ', 'b', 'b', 'b', 'b', 'b', 'b'}};
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (cells[y][x] == 'b')
        board.setCellAt(x, y, OthelloCell::black);
  GameState gameState_adjacent_stable_cells(board);

  EXPECT_GT(
      AI::stronger::evaluate(&gameState_adjacent_stable_cells,
                             OthelloCell::black),
      AI::stronger::evaluate(&gameState_just_the_corner, OthelloCell::black));
}

TEST(testStrongerEvaluate, detectFrontierBlackTiles) {
  Board board;
  const char cells[8][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', 'b', 'b', 'b', 'b', ' ', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', ' ', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', ' ', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (cells[y][x] == 'b')
        board.setCellAt(x, y, OthelloCell::black);
  GameState gameState_adjacent_stable_cells(board);

  EXPECT_LT(AI::stronger::evaluate(&gameState_adjacent_stable_cells,
                                   OthelloCell::black),
            0);
}

TEST(testStrongerEvaluate, excludeEdgeTilesAsFrontier) {
  Board board;
  for (int i = 0; i < 8; ++i) {
    board.setCellAt(i, 0, OthelloCell::black);
    board.setCellAt(7, i, OthelloCell::black);
    board.setCellAt(i, 7, OthelloCell::black);
    board.setCellAt(0, i, OthelloCell::black);
  }
  GameState gameState_edge_tiles_only(board);

  const char cells[8][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', 'b', 'b', 'b', 'b', ' ', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', ' ', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', ' ', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (cells[y][x] == 'b')
        board.setCellAt(x, y, OthelloCell::black);
  GameState gameState_frontier_added(board);

  EXPECT_GT(
      AI::stronger::evaluate(&gameState_edge_tiles_only, OthelloCell::black),
      AI::stronger::evaluate(&gameState_frontier_added, OthelloCell::black));
}

TEST(testStrongerEvaluate, flippingInteriorTilesKeepsSameScore) {
  Board board;
  const char cells[8][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', 'b', 'b', 'b', 'b', ' ', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', ' ', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', ' ', ' ', ' '},
                            {' ', 'w', 'w', 'w', 'b', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (cells[y][x] == 'b')
        board.setCellAt(x, y, OthelloCell::black);
      else if (cells[y][x] == 'w')
        board.setCellAt(x, y, OthelloCell::white);
  GameState gameState_initial_frontier(board);

  board.flipTile(3, 3);
  GameState gameState_interior_flipped(board);

  EXPECT_EQ(
      AI::stronger::evaluate(&gameState_initial_frontier, OthelloCell::black),
      AI::stronger::evaluate(&gameState_interior_flipped, OthelloCell::black));
}
