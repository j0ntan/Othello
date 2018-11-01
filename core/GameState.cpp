#include "GameState.hpp"
#include "othellogame/OthelloException.hpp"
#include <string>

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

bool rowIsValid(const GameState &gameState, const int x, const int y) {
  int x_n = x;
  const OthelloCell opposing =
      gameState.isBlackTurn() ? OthelloCell::white : OthelloCell::black;

  // check left side
  while (--x_n >= 0 && gameState.board().cellAt(x_n, y) == opposing)
    ;
  if (x_n >= 0 && gameState.board().cellAt(x_n, y) != OthelloCell::empty &&
      gameState.board().cellAt(x_n + 1, y) == opposing) // found anchor
    return true;

  // else, check right side
  x_n = x;
  const int width = gameState.board().width();
  while (++x_n < width && gameState.board().cellAt(x_n, y) == opposing)
    ;
  if (x_n < width && gameState.board().cellAt(x_n, y) != OthelloCell::empty &&
      gameState.board().cellAt(x_n - 1, y) == opposing) // found anchor
    return true;

  return false; // else, invalid
}

bool columnIsValid(const GameState &gameState, const int x, const int y) {
  int y_n = y;
  const OthelloCell opposing =
      gameState.isBlackTurn() ? OthelloCell::white : OthelloCell::black;

  // check top side
  while (--y_n >= 0 && gameState.board().cellAt(x, y_n) == opposing)
    ;
  if (y_n >= 0 && gameState.board().cellAt(x, y_n) != OthelloCell::empty &&
      gameState.board().cellAt(x, y_n + 1) == opposing) // found anchor
    return true;

  // else, check bottom side
  y_n = y;
  const int height = gameState.board().height();
  while (++y_n < height && gameState.board().cellAt(x, y_n) == opposing)
    ;
  if (y_n < height && gameState.board().cellAt(x, y_n) != OthelloCell::empty &&
      gameState.board().cellAt(x, y_n - 1) == opposing) // found anchor
    return true;

  return false; // else, invalid
}

bool positiveDiagonalIsValid(const GameState &gameState, const int x,
                             const int y) {
  int x_n = x;
  int y_n = y;
  const OthelloCell opposing =
      gameState.isBlackTurn() ? OthelloCell::white : OthelloCell::black;

  // check top-right direction
  const int width = gameState.board().width();
  while (++x_n < width && --y_n >= 0 &&
         gameState.board().cellAt(x_n, y_n) == opposing)
    ;
  if (x_n < width && y_n >= 0 &&
      gameState.board().cellAt(x_n, y_n) != OthelloCell::empty &&
      gameState.board().cellAt(x_n - 1, y_n + 1) == opposing) // found anchor
    return true;

  // else, check bottom-left direction
  x_n = x;
  y_n = y;
  const int height = gameState.board().height();
  while (--x_n >= 0 && ++y_n < height &&
         gameState.board().cellAt(x_n, y_n) == opposing)
    ;
  if (x_n >= 0 && y_n < height &&
      gameState.board().cellAt(x_n, y_n) != OthelloCell::empty &&
      gameState.board().cellAt(x_n + 1, y_n - 1) == opposing) // found anchor
    return true;

  return false; // else, invalid
}
bool negativeDiagonalIsValid(const GameState &gameState, const int x,
                             const int y) {
  int x_n = x;
  int y_n = y;
  const OthelloCell opposing =
      gameState.isBlackTurn() ? OthelloCell::white : OthelloCell::black;

  // check top-left direction
  while (--x_n >= 0 && --y_n >= 0 &&
         gameState.board().cellAt(x_n, y_n) == opposing)
    ;
  if (x_n >= 0 && y_n >= 0 &&
      gameState.board().cellAt(x_n, y_n) != OthelloCell::empty &&
      gameState.board().cellAt(x_n + 1, y_n + 1) == opposing) // found anchor
    return true;

  // else, check bottom-right direction
  x_n = x;
  y_n = y;
  const int width = gameState.board().width();
  const int height = gameState.board().height();
  while (++x_n < width && ++y_n < height &&
         gameState.board().cellAt(x_n, y_n) == opposing)
    ;
  if (x_n < width && y_n < height &&
      gameState.board().cellAt(x_n, y_n) != OthelloCell::empty &&
      gameState.board().cellAt(x_n - 1, y_n - 1) == opposing) // found anchor
    return true;

  return false; // else, invalid
}

void flipRowTiles(GameState &gameState, Board &board, const int x,
                  const int y) {
  int x_n = x;
  const OthelloCell opposing =
      gameState.isBlackTurn() ? OthelloCell::white : OthelloCell::black;

  // find left anchor
  while (--x_n >= 0 && gameState.board().cellAt(x_n, y) == opposing)
    ;
  if (x_n >= 0 && gameState.board().cellAt(x_n, y) != OthelloCell::empty)
    while (++x_n != x)
      board.flipTile(x_n, y);

  // find right anchor
  x_n = x;
  const int width = gameState.board().width();
  while (++x_n < width && gameState.board().cellAt(x_n, y) == opposing)
    ;
  if (x_n < width && gameState.board().cellAt(x_n, y) != OthelloCell::empty)
    while (--x_n != x)
      board.flipTile(x_n, y);
}

void flipColumnTiles(GameState &gameState, Board &board, const int x,
                     const int y) {
  int y_n = y;
  const OthelloCell opposing =
      gameState.isBlackTurn() ? OthelloCell::white : OthelloCell::black;

  // find top anchor
  while (--y_n >= 0 && gameState.board().cellAt(x, y_n) == opposing)
    ;
  if (y_n >= 0 && gameState.board().cellAt(x, y_n) != OthelloCell::empty)
    while (++y_n != y)
      board.flipTile(x, y_n);

  // find right anchor
  y_n = y;
  const int height = gameState.board().height();
  while (++y_n < height && gameState.board().cellAt(x, y_n) == opposing)
    ;
  if (y_n < height && gameState.board().cellAt(x, y_n) != OthelloCell::empty)
    while (--y_n != y)
      board.flipTile(x, y_n);
}

void flipPositiveDiagonalTiles(GameState &gameState, Board &board, const int x,
                               const int y) {
  int x_n = x;
  int y_n = y;
  const OthelloCell opposing =
      gameState.isBlackTurn() ? OthelloCell::white : OthelloCell::black;

  // find bottom-left anchor
  const int height = gameState.board().height();
  while (--x_n >= 0 && ++y_n < height &&
         gameState.board().cellAt(x_n, y_n) == opposing)
    ;
  if (x_n >= 0 && y_n < height &&
      gameState.board().cellAt(x_n, y_n) != OthelloCell::empty)
    while (++x_n != x && --y_n != y)
      board.flipTile(x_n, y_n);

  // find top-right anchor
  x_n = x;
  y_n = y;
  const int width = gameState.board().width();
  while (++x_n < width && --y_n >= 0 &&
         gameState.board().cellAt(x_n, y_n) == opposing)
    ;
  if (x_n < width && y_n >= 0 &&
      gameState.board().cellAt(x_n, y_n) != OthelloCell::empty)
    while (--x_n != x && ++y_n != y)
      board.flipTile(x_n, y_n);
}

void flipNegativeDiagonalTiles(GameState &gameState, Board &board, const int x,
                               const int y) {
  int x_n = x;
  int y_n = y;
  const OthelloCell opposing =
      gameState.isBlackTurn() ? OthelloCell::white : OthelloCell::black;

  // find top-left anchor
  while (--x_n >= 0 && --y_n >= 0 &&
         gameState.board().cellAt(x_n, y_n) == opposing)
    ;
  if (x_n >= 0 && y_n >= 0 &&
      gameState.board().cellAt(x_n, y_n) != OthelloCell::empty)
    while (++x_n != x && ++y_n != y)
      board.flipTile(x_n, y_n);

  // find bottom-right anchor
  x_n = x;
  y_n = y;
  const int width = gameState.board().width();
  const int height = gameState.board().height();
  while (++x_n < width && ++y_n < height &&
         gameState.board().cellAt(x_n, y_n) == opposing)
    ;
  if (x_n < width && y_n < height &&
      gameState.board().cellAt(x_n, y_n) != OthelloCell::empty)
    while (--x_n != x && --y_n != y)
      board.flipTile(x_n, y_n);
}
} // namespace

GameState::GameState(const Board &board, bool blackMovesFirst)
    : reference_board(board), blacksTurn(blackMovesFirst) {}

GameState::GameState(const GameState &gameState)
    : reference_board(gameState.reference_board),
      blacksTurn(gameState.blacksTurn) {}

const OthelloBoard &GameState::board() const noexcept {
  return reference_board;
}

Board GameState::boardCopy() const noexcept {
  return reference_board;
}

int GameState::blackScore() const noexcept {
  return countTiles(board(), OthelloCell::black);
}

int GameState::whiteScore() const noexcept {
  return countTiles(board(), OthelloCell::white);
}

bool GameState::isGameOver() const noexcept {
  bool move_available = false;
  const int width = reference_board.width();
  const int height = reference_board.height();
  for (int x = 0; x < width && !move_available; ++x)
    for (int y = 0; y < height && !move_available; ++y)
      move_available = isValidMove(x, y);
  return !move_available;
}

bool GameState::isBlackTurn() const noexcept { return blacksTurn; }

bool GameState::isWhiteTurn() const noexcept { return !blacksTurn; }

bool GameState::isValidMove(int x, int y) const {
  return chosenCellIsEmpty(reference_board, x, y) &&
         (rowIsValid(*this, x, y) || columnIsValid(*this, x, y) ||
          positiveDiagonalIsValid(*this, x, y) ||
          negativeDiagonalIsValid(*this, x, y));
}

void GameState::makeMove(int x, int y) {
  if (!isValidMove(x, y))
    throw OthelloException(std::string(isBlackTurn() ? "Black" : "White") +
                           "'s move at (" + std::to_string(x) + ", " +
                           std::to_string(y) + ") is invalid.");

  if (isBlackTurn())
    reference_board.placeTile(x, y, OthelloCell::black);
  else
    reference_board.placeTile(x, y, OthelloCell::white);

  if (rowIsValid(*this, x, y))
    flipRowTiles(*this, reference_board, x, y);
  if (columnIsValid(*this, x, y))
    flipColumnTiles(*this, reference_board, x, y);
  if (positiveDiagonalIsValid(*this, x, y))
    flipPositiveDiagonalTiles(*this, reference_board, x, y);
  if (negativeDiagonalIsValid(*this, x, y))
    flipNegativeDiagonalTiles(*this, reference_board, x, y);

  blacksTurn = !blacksTurn;
}

std::unique_ptr<OthelloGameState> GameState::clone() const {
  return std::unique_ptr<OthelloGameState>(new GameState(*this));
}
