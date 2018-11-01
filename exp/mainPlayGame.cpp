#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/SimpleAI.hpp"

// function prototypes
Board startingPositionBoard();

int main() { Board board = startingPositionBoard(); }

Board startingPositionBoard() {
  Board board;
  board.setCellAt(3, 3, OthelloCell::white);
  board.setCellAt(4, 3, OthelloCell::black);
  board.setCellAt(3, 4, OthelloCell::black);
  board.setCellAt(4, 4, OthelloCell::white);
  return board;
}
