#include "GameState.hpp"

namespace {
const int countTiles(const OthelloBoard &board, OthelloCell tile) noexcept {
  int counter = 0;
  for (int x = 0; x < board.width(); ++x)
    for (int y = 0; y < board.height(); ++y)
      if (board.cellAt(x, y) == tile)
        ++counter;
  return counter;
}
} // namespace

GameState::GameState(const Board &board) : reference_board(board) {}

const OthelloBoard &GameState::board() const noexcept {
  return reference_board;
}

int GameState::blackScore() const noexcept {
  return countTiles(board(), OthelloCell::black);
}

int GameState::whiteScore() const noexcept {
  return countTiles(board(), OthelloCell::white);
}

bool GameState::isGameOver() const noexcept {}

bool GameState::isBlackTurn() const noexcept {}

bool GameState::isWhiteTurn() const noexcept {}

bool GameState::isValidMove(int x, int y) const {}

void GameState::makeMove(int x, int y) {}

std::unique_ptr<OthelloGameState> GameState::clone() const {}
