#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "othellogame/OthelloException.hpp"
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

TEST(testGameState, blackScoreCorrectForPopulatedBoard) {
  Board board;
  board.placeTile(0, 0, OthelloCell::black);
  board.placeTile(1, 1, OthelloCell::black);
  board.placeTile(2, 2, OthelloCell::black);
  board.placeTile(3, 3, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);

  GameState gameState(board);
  EXPECT_EQ(4, gameState.blackScore());
}

TEST(testGameState, whiteScoreIsZeroForEmptyBoard) {
  Board board;
  GameState gameState(board);
  EXPECT_EQ(0, gameState.whiteScore());
}

TEST(testGameState, whiteScoreCorrectForPopulatedBoard) {
  Board board;
  board.placeTile(0, 0, OthelloCell::white);
  board.placeTile(1, 1, OthelloCell::white);
  board.placeTile(2, 2, OthelloCell::white);
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 4, OthelloCell::black);

  GameState gameState(board);
  EXPECT_EQ(4, gameState.whiteScore());
}

TEST(testGameState, blackGoesFirstForDefaultGameState) {
  GameState gameState(Board(8));
  EXPECT_TRUE(gameState.isBlackTurn());
  EXPECT_FALSE(gameState.isWhiteTurn());
}

TEST(testGameState, setWhiteGoesFirstForEmptyGameState) {
  GameState gameState(Board(), false);
  EXPECT_FALSE(gameState.isBlackTurn());
  EXPECT_TRUE(gameState.isWhiteTurn());
}

TEST(testGameState, occupiedCellIsNotValidMove) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_FALSE(gameState.isValidMove(3, 3));
  EXPECT_FALSE(gameState.isValidMove(4, 3));
  EXPECT_FALSE(gameState.isValidMove(3, 4));
  EXPECT_FALSE(gameState.isValidMove(4, 4));
}

TEST(testGameState, singleValidMovePerRowInStartingPosition) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_TRUE(gameState.isValidMove(2, 3));
  EXPECT_FALSE(gameState.isValidMove(5, 3));
  EXPECT_FALSE(gameState.isValidMove(2, 4));
  EXPECT_TRUE(gameState.isValidMove(5, 4));
}

TEST(testGameState, singleValidMovePerColumnInStartingPosition) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_TRUE(gameState.isValidMove(3, 2));
  EXPECT_FALSE(gameState.isValidMove(4, 2));
  EXPECT_FALSE(gameState.isValidMove(3, 5));
  EXPECT_TRUE(gameState.isValidMove(4, 5));
}

TEST(testGameState, singleValidMoveInPositiveDiagonalPosition) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  board.placeTile(2, 5, OthelloCell::white);
  GameState gameState(board, false);

  EXPECT_TRUE(gameState.isValidMove(5, 2));
  EXPECT_FALSE(gameState.isValidMove(2, 5));
}

TEST(testGameState, singleValidMoveInNegativeDiagonalPosition) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  board.placeTile(5, 5, OthelloCell::black);
  GameState gameState(board);

  EXPECT_TRUE(gameState.isValidMove(2, 2));
  EXPECT_FALSE(gameState.isValidMove(6, 6));
}

TEST(testGameState, makeMoveModifiesChosenCell) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_EQ(OthelloCell::empty, gameState.board().cellAt(3, 2));
  gameState.makeMove(3, 2);
  EXPECT_EQ(OthelloCell::black, gameState.board().cellAt(3, 2));
}

TEST(testGameState, whitesTurnAfterFirstBlackMove) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_TRUE(gameState.isBlackTurn());
  gameState.makeMove(3, 2);
  EXPECT_TRUE(gameState.isWhiteTurn());
}

TEST(testGameState, firstTwoMovesPlacesOppositeTiles) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_EQ(OthelloCell::empty, gameState.board().cellAt(3, 2));
  EXPECT_EQ(OthelloCell::empty, gameState.board().cellAt(4, 2));
  gameState.makeMove(3, 2);
  EXPECT_EQ(OthelloCell::black, gameState.board().cellAt(3, 2));
  gameState.makeMove(4, 2);
  EXPECT_EQ(OthelloCell::white, gameState.board().cellAt(4, 2));
}

TEST(testGameState, invalidMoveThrowsException) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_THROW(gameState.makeMove(0, 0), OthelloException);
  EXPECT_THROW(gameState.makeMove(3, 3), OthelloException);
}

TEST(testGameState, validHorizontalMoveFlipsInBetweenTiles) {
  Board board;
  board.placeTile(3, 3, OthelloCell::black);
  board.placeTile(4, 3, OthelloCell::white);
  board.placeTile(5, 3, OthelloCell::white);
  board.placeTile(7, 3, OthelloCell::white);
  GameState gameState(board);

  EXPECT_EQ(gameState.board().cellAt(4, 3), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(5, 3), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(7, 3), OthelloCell::white);
  gameState.makeMove(6, 3);
  EXPECT_EQ(gameState.board().cellAt(4, 3), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(5, 3), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(7, 3), OthelloCell::white);
}

TEST(testGameState, validVerticalMoveFlipsInBetweenTiles) {
  Board board;
  board.placeTile(3, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::white);
  board.placeTile(3, 5, OthelloCell::white);
  board.placeTile(3, 7, OthelloCell::white);
  GameState gameState(board);

  EXPECT_EQ(gameState.board().cellAt(3, 4), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(3, 5), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(3, 7), OthelloCell::white);
  gameState.makeMove(3, 6);
  EXPECT_EQ(gameState.board().cellAt(3, 4), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(3, 5), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(3, 7), OthelloCell::white);
}

TEST(testGameState, validPositiveDiagonalMoveFlipsInBetweenTiles) {
  Board board;
  board.placeTile(2, 5, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::white);
  board.placeTile(6, 1, OthelloCell::white);
  GameState gameState(board);

  EXPECT_EQ(gameState.board().cellAt(3, 4), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(4, 3), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(6, 1), OthelloCell::white);
  gameState.makeMove(5, 2);
  EXPECT_EQ(gameState.board().cellAt(3, 4), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(4, 3), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(6, 1), OthelloCell::white);
}

TEST(testGameState, validNegativeDiagonalMoveFlipsInBetweenTiles) {
  Board board;
  board.placeTile(5, 5, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(1, 1, OthelloCell::white);
  GameState gameState(board);

  EXPECT_EQ(gameState.board().cellAt(4, 4), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(3, 3), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(1, 1), OthelloCell::white);
  gameState.makeMove(2, 2);
  EXPECT_EQ(gameState.board().cellAt(4, 4), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(3, 3), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(1, 1), OthelloCell::white);
}

TEST(testGameState, comboVerticalAndHorizontalMoveFlipsAllInBetweenTiles) {
  Board board;
  board.placeTile(1, 4, OthelloCell::black);
  board.placeTile(2, 4, OthelloCell::white);
  board.placeTile(3, 4, OthelloCell::white);
  board.placeTile(4, 1, OthelloCell::black);
  board.placeTile(4, 2, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::white);
  GameState gameState(board);

  EXPECT_EQ(gameState.board().cellAt(2, 4), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(3, 4), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(4, 2), OthelloCell::white);
  EXPECT_EQ(gameState.board().cellAt(4, 3), OthelloCell::white);
  gameState.makeMove(4, 4);
  EXPECT_EQ(gameState.board().cellAt(2, 4), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(3, 4), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(4, 2), OthelloCell::black);
  EXPECT_EQ(gameState.board().cellAt(4, 3), OthelloCell::black);
}

TEST(testGameState, gameNotOverForStartingBoard) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  GameState gameState(board);

  EXPECT_FALSE(gameState.isGameOver());
}

TEST(testGameState, gameOverForFullBoard) {
  Board board;
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      board.placeTile(x, y, OthelloCell::white);
  GameState gameState(board);

  EXPECT_TRUE(gameState.isGameOver());
}

TEST(testGameState, lastEmptyCellEndsGameForOneSideOnly) {
  Board board;
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      board.placeTile(x, y, OthelloCell::white);
  board.flipTile(0, 0);
  board.setCellAt(7, 0, OthelloCell::empty);
  GameState gameState1(board);        // set black's turn to move
  GameState gameState2(board, false); // set white's turn

  EXPECT_FALSE(gameState1.isGameOver());
  EXPECT_TRUE(gameState2.isGameOver());
}

TEST(testGameState, gameOverForNonFilledBoard) {
  // Vlasakova vs Schotte @ European Grand Prix Prague 2011
  Board board1;
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      board1.placeTile(x, y, OthelloCell::white);
  board1.flipTile(7, 5);
  board1.setCellAt(7, 3, OthelloCell::empty);
  board1.setCellAt(6, 4, OthelloCell::empty);
  board1.setCellAt(7, 4, OthelloCell::empty);
  board1.setCellAt(6, 5, OthelloCell::empty);
  board1.setCellAt(7, 6, OthelloCell::empty);
  GameState gameState1(board1);
  GameState gameState2(board1, false);
  EXPECT_TRUE(gameState1.isGameOver());
  EXPECT_TRUE(gameState2.isGameOver());

  // Vecci vs Nicolas @ World Othello Championship 2017, Ghent
  Board board2;
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (x == 0 || y == 7)
        board2.placeTile(x, y, OthelloCell::black);
      else
        board2.placeTile(x, y, OthelloCell::white);
  board2.setCellAt(0, 0, OthelloCell::empty);
  board2.setCellAt(0, 1, OthelloCell::empty);
  board2.setCellAt(6, 1, OthelloCell::empty);
  board2.setCellAt(0, 7, OthelloCell::empty);
  board2.setCellAt(6, 7, OthelloCell::empty);
  board2.setCellAt(7, 7, OthelloCell::empty);
  GameState gameState3(board2);
  GameState gameState4(board2, false);
  EXPECT_TRUE(gameState3.isGameOver());
  EXPECT_TRUE(gameState4.isGameOver());
}

TEST(testGameState, cloneIsIndependantFromOriginal) {
  Board board;
  board.placeTile(3, 3, OthelloCell::white);
  board.placeTile(4, 3, OthelloCell::black);
  board.placeTile(3, 4, OthelloCell::black);
  board.placeTile(4, 4, OthelloCell::white);
  GameState gameState(board);

  auto clone = gameState.clone();
  EXPECT_EQ(gameState.isBlackTurn(), clone->isBlackTurn());
  EXPECT_EQ(gameState.board().cellAt(3, 2), clone->board().cellAt(3, 2));
  clone->makeMove(3, 2);
  EXPECT_NE(gameState.isBlackTurn(), clone->isBlackTurn());
  EXPECT_NE(gameState.board().cellAt(3, 2), clone->board().cellAt(3, 2));
}
