#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/SimpleAI.hpp"
#include <iostream>

// function prototypes
Board startingPositionBoard();
void announceWinner(const GameState &gameState);

int main() {
  Board board = startingPositionBoard();

  GameState gameState(board);
  while (!gameState.isGameOver()) {
    // human moves
    // computer moves
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
