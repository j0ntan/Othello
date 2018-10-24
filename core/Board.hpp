#ifndef BOARD_HPP
#define BOARD_HPP

#include "othellogame/OthelloBoard.hpp"
#include "othellogame/OthelloCell.hpp"

class Board : public OthelloBoard {
public:
  Board(unsigned int size = 8);

  ~Board() final = default;

  // width() returns the width of this Othello board.
  int width() const noexcept final;

  // height() returns the height of this Othello board.
  int height() const noexcept final;

  // isValidCell() returns true if the given (x, y) is a valid
  // cell on this board -- i.e., if (x, y) is in the boundaries
  // of the board -- or false otherwise.
  bool isValidCell(int x, int y) const noexcept final;

  // cellAt() returns the contents of the cell (x, y).  The cell
  // will either be empty, black, or white.
  OthelloCell cellAt(int x, int y) const final;

  // setCellAt() changes the contents of the cell (x, y) to the
  // given new value (empty, black, or white).
  void setCellAt(int x, int y, OthelloCell cell) final;

  // placeTile() places a tile on the board in cell (x, y),
  // provided that cell (x, y) is currently empty.  If the
  // cell is not currently empty, an OthelloException is
  // thrown.
  void placeTile(int x, int y, OthelloCell cell) final;

  // flipTile() flips the tile on the board in cell (x, y),
  // if any -- so, if it was white, it is now black; if it
  // was black, it is now white.  If the cell is not currently
  // occupied by a tile, an OthelloException is thrown.
  void flipTile(int x, int y) final;

private:
};

#endif // BOARD_HPP
