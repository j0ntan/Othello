#include "Board.hpp"

int Board::width() const noexcept {}

int Board::height() const noexcept {}

bool Board::isValidCell(int x, int y) const noexcept {}

OthelloCell Board::cellAt(int x, int y) const {}

void Board::setCellAt(int x, int y, OthelloCell cell) {}

void Board::placeTile(int x, int y, OthelloCell cell) {}

void Board::flipTile(int x, int y) {}
