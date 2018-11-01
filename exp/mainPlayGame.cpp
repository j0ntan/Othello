#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/SimpleAI.hpp"
#include <iostream>

// function prototypes
Board startingPositionBoard();
void announceWinner(const GameState &gameState);
bool playerHasValidMove(const GameState &gameState, OthelloCell whichPlayer);

int main() {
  Board board = startingPositionBoard();

  GameState gameState(board);
  while (!gameState.isGameOver()) {
    // human moves
    if (playerHasValidMove(gameState, OthelloCell::black))
      ; // prompt to make move
    else
      ; // skip turn

    // computer moves
    if (playerHasValidMove(gameState, OthelloCell::white))
      ; // AI chooses move
    else
      ; // skip turn
  }

  announceWinner(gameState);
}

Board startingPositionBoard() {
  Board board;
  board.setCellAt(3, 3, OthelloCell::white);
  board.setCellAt(4, 3, OthelloCell::black);
  board.setCellAt(3, 4, OthelloCell::black);
  board.setCellAt(4, 4, OthelloCell::white);
  return board;
}

void announceWinner(const GameState &gameState) {
  const int final_score = gameState.blackScore() - gameState.whiteScore();
  if (final_score > 0)
    std::cout << "Black wins!\n";
  else if (final_score < 0)
    std::cout << "White wins!\n";
  else
    std::cout << "Tied game!\n";
}

bool playerHasValidMove(const GameState &gameState, OthelloCell whichPlayer) {
  GameState current_game_state(gameState.boardCopy(),
                               whichPlayer == OthelloCell::black);
  bool hasValidMove = false;
  for (int x = 0; x < 8 && !hasValidMove; ++x)
    for (int y = 0; y < 8 && !hasValidMove; ++y)
      hasValidMove = current_game_state.isValidMove(x, y);
  return hasValidMove;
}
