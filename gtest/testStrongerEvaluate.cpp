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
  EXPECT_GT(AI::stronger::mobilityScore(&gameState1),
            AI::stronger::mobilityScore(&gameState2));
  EXPECT_GT(AI::stronger::mobilityScore(&gameState3),
            AI::stronger::mobilityScore(&gameState4));
}
