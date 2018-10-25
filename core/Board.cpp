#include "Board.hpp"
#include "othellogame/OthelloException.hpp"
#include <string>

Board::Board(const unsigned int size) {
  cells = std::vector<std::vector<OthelloCell>>(
      size, std::vector<OthelloCell>(size, OthelloCell::empty));
}

Board::Board(const unsigned int width, const unsigned int height) {
  cells = std::vector<std::vector<OthelloCell>>(
      width, std::vector<OthelloCell>(height, OthelloCell::empty));
}

int Board::width() const noexcept { return cells.size(); }

int Board::height() const noexcept { return cells[0].size(); }

bool Board::isValidCell(int x, int y) const noexcept {
  return x >= 0 && y >= 0 && x < cells.size() && y < cells[0].size();
}

OthelloCell Board::cellAt(int x, int y) const {
  if (!isValidCell(x, y))
    throw OthelloException("Cell at (" + std::to_string(x) + ", " +
                           std::to_string(y) + ") is invalid, cannot access.");
  return cells[x][y];
}

void Board::setCellAt(int x, int y, OthelloCell cell) {
  if (!isValidCell(x, y))
    throw OthelloException("Cell at (" + std::to_string(x) + ", " +
                           std::to_string(y) + ") is invalid, cannot set.");
  cells[x][y] = cell;
}

void Board::placeTile(int x, int y, OthelloCell cell) {
  setCellAt(x, y, cell); // may throw if (x, y) invalid
}

void Board::flipTile(int x, int y) {}
