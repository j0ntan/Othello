#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/SimpleAI.hpp"
#include <iostream>

// function prototypes
Board startingPositionBoard();
void announceWinner(const GameState &gameState);
bool playerHasValidMove(const GameState &gameState, OthelloCell whichPlayer);
void humanMakesMove(GameState &gameState);
void skipTurn(GameState &gameState, OthelloCell whichPlayer);
void computerMakesMove(GameState &gameState);

int main() {
  Board board = startingPositionBoard();
  board.print();

  GameState gameState(board);
  while (!gameState.isGameOver()) {
    // human moves
    if (playerHasValidMove(gameState, OthelloCell::black))
      humanMakesMove(gameState);
    else
      skipTurn(gameState, OthelloCell::black);

    // computer moves
    if (playerHasValidMove(gameState, OthelloCell::white))
      computerMakesMove(gameState);
    else
      skipTurn(gameState, OthelloCell::white);
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

void humanMakesMove(GameState &gameState) {
  int x = 0, y = 0;
  std::cout << "Enter an x- and y-coordinate for your move:\n";
  std::cin >> x >> y;
  while (!gameState.isValidMove(x, y)) {
    std::cout << "Choice is invalid. Please try again.\n";
    std::cin >> x >> y;
  }

  std::cout << "Placing black tile @ (" << x << ", " << y << ")\n";
  gameState.makeMove(x, y);
  gameState.boardCopy().print();
  std::cout << std::endl;
}

void skipTurn(GameState &gameState, OthelloCell whichPlayer) {
  std::cout << (whichPlayer == OthelloCell::black ? "black" : "white")
            << " skips this turn\n\n";
  gameState =
      GameState(gameState.boardCopy(), whichPlayer != OthelloCell::black);
}

void computerMakesMove(GameState &gameState) {
  SimpleAI simpleAI;
  auto chosen_move = simpleAI.chooseMove(gameState);

  std::cout << "Placing white tile @ (" << chosen_move.first << ", "
            << chosen_move.second << ")\n";
  gameState.makeMove(chosen_move.first, chosen_move.second);
  gameState.boardCopy().print();
  std::cout << std::endl;
}
