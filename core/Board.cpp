#include "Board.hpp"

int Board::width() const noexcept {
  return 8;
}

int Board::height() const noexcept {
  return 8;
}

bool Board::isValidCell(int x, int y) const noexcept {}

OthelloCell Board::cellAt(int x, int y) const {}

void Board::setCellAt(int x, int y, OthelloCell cell) {}

void Board::placeTile(int x, int y, OthelloCell cell) {}

void Board::flipTile(int x, int y) {}
