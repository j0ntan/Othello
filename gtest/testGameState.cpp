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
