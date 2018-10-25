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

inline bool chosenCellIsEmpty(const Board &board, int x, int y) {
  return board.cellAt(x, y) == OthelloCell::empty;
}
} // namespace

GameState::GameState(const Board &board, bool blackMovesFirst)
    : reference_board(board), blacksTurn(blackMovesFirst) {}

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

bool GameState::isBlackTurn() const noexcept { return blacksTurn; }

bool GameState::isWhiteTurn() const noexcept { return !blacksTurn; }

bool GameState::isValidMove(int x, int y) const {
  return chosenCellIsEmpty(reference_board, x, y);
}

void GameState::makeMove(int x, int y) {}

std::unique_ptr<OthelloGameState> GameState::clone() const {}
