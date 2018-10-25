#include "GameState.hpp"

GameState::GameState(const Board &board) : reference_board(board) {}

const OthelloBoard &GameState::board() const noexcept {
  return reference_board;
}

int GameState::blackScore() const noexcept {}

int GameState::whiteScore() const noexcept {}

bool GameState::isGameOver() const noexcept {}

bool GameState::isBlackTurn() const noexcept {}

bool GameState::isWhiteTurn() const noexcept {}

bool GameState::isValidMove(int x, int y) const {}

void GameState::makeMove(int x, int y) {}

std::unique_ptr<OthelloGameState> GameState::clone() const {}
