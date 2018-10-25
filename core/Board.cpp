#include "Board.hpp"
#include "othellogame/OthelloException.hpp"
#include <iostream>
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
  if (cellAt(x, y) != OthelloCell::empty)
    throw OthelloException("Cell at (" + std::to_string(x) + ", " +
                           std::to_string(y) +
                           ") already has a tile, cannot place another tile.");
  setCellAt(x, y, cell); // may throw if (x, y) invalid
}

void Board::flipTile(int x, int y) {
  if (cellAt(x, y) == OthelloCell::empty)
    throw OthelloException("Cannot flip empty cell at (" + std::to_string(x) +
                           ", " + std::to_string(y) + ").");
  setCellAt(x, y,
            (cellAt(x, y) == OthelloCell::white) ? OthelloCell::black
                                                 : OthelloCell::white);
}

void Board::print() const noexcept {
  const int board_width = width();
  const int board_height = height();
  const char white = 'w';
  const char black = 'b';

  // print top border
  for (int x = 0; x < board_width; ++x) {
    std::cout << "*-";
  }
  std::cout << "*\n";

  // print row by row
  for (int y = 0; y < board_height; ++y) {
    std::cout << '|'; // left border wall

    // print cell value & right wall
    for (int x = 0; x < board_width; ++x) {
      switch (cellAt(x, y)) {
      case OthelloCell::empty:
        std::cout << ' ';
        break;
      case OthelloCell::white:
        std::cout << white;
        break;
      case OthelloCell::black:
        std::cout << black;
        break;
      }
      std::cout << '|';
    }
    std::cout << '\n';

    // print bottom wall
    std::cout << '*';
    for (int x = 0; x < board_width; ++x)
      std::cout << "-*";
    std::cout << '\n';
  }
  std::cout << '\n';
}
