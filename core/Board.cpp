#include "Board.hpp"

Board::Board(const unsigned int size) : board_width(size), board_height(size) {}

int Board::width() const noexcept { return board_width; }

int Board::height() const noexcept { return board_height; }

bool Board::isValidCell(int x, int y) const noexcept {
  return true;
}

OthelloCell Board::cellAt(int x, int y) const {}

void Board::setCellAt(int x, int y, OthelloCell cell) {}

void Board::placeTile(int x, int y, OthelloCell cell) {}

void Board::flipTile(int x, int y) {}
