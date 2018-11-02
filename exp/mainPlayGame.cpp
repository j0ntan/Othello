#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/SimpleAI.hpp"
#include <cctype>
#include <iostream>

// function prototypes
Board startingPositionBoard();
void announceWinner(const GameState &gameState);
bool playerHasValidMove(const GameState &gameState, OthelloCell whichPlayer);
void humanMakesMove(GameState &gameState);
void skipTurn(GameState &gameState, OthelloCell whichPlayer);
void computerMakesMove(GameState &gameState);
void printScores(const GameState &gameState);

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
  printScores(gameState);
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
  char first_input = '\0';
  int x = 0, y = 0;
  std::cout << "Enter an x- and y-coordinate for your move:\n";
  std::cout << "(Enter the letter \'C\' to let the AI choose)\n";
  std::cin >> first_input;
  if (first_input == 'c' || first_input == 'C') {
    SimpleAI simpleAI;
    auto move = simpleAI.chooseMove(gameState);
    x = move.first;
    y = move.second;

  } else {
    x = first_input - '0';
    std::cin >> y;
    while (!gameState.isValidMove(x, y)) {
      std::cout << "Choice is invalid. Please try again.\n";
      std::cin >> x >> y;
    }
  }

  std::cout << "Placing black tile @ (" << x << ", " << y << ")\n";
  gameState.makeMove(x, y);
  printScores(gameState);
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
  printScores(gameState);
  gameState.boardCopy().print();
  std::cout << std::endl;
}

void printScores(const GameState &gameState) {
  std::cout << "Score: (" << gameState.blackScore() << " - "
            << gameState.whiteScore() << ")\n";
}
