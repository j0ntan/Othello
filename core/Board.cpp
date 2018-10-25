#include "Board.hpp"
#include "othellogame/OthelloException.hpp"
#include <string>

Board::Board(const unsigned int size) : board_width(size), board_height(size) {}

int Board::width() const noexcept { return board_width; }

int Board::height() const noexcept { return board_height; }

bool Board::isValidCell(int x, int y) const noexcept {
  return x >= 0 && y >= 0 && x < board_width && y < board_height;
}

OthelloCell Board::cellAt(int x, int y) const {
  if (!isValidCell(x, y))
    throw OthelloException("Cell at (" + std::to_string(x) + ", " +
                           std::to_string(y) + ") is invalid, cannot access.");
  return OthelloCell::empty;
}

void Board::setCellAt(int x, int y, OthelloCell cell) {}

void Board::placeTile(int x, int y, OthelloCell cell) {}

void Board::flipTile(int x, int y) {}
