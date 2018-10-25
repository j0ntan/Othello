#include "core/Board.hpp"
#include "othellogame/OthelloCell.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int main() {
  Board board1;

  std::cout << "Empty board:\n";
  board1.print();

  // starting position board
  board1.placeTile(3, 3, OthelloCell::white);
  board1.placeTile(4, 3, OthelloCell::black);
  board1.placeTile(3, 4, OthelloCell::black);
  board1.placeTile(4, 4, OthelloCell::white);
  std::cout << "Starting position:\n";
  board1.print();

  // board with random cells
  std::srand(std::time(nullptr));
  OthelloCell options[] = {OthelloCell::black, OthelloCell::white,
                           OthelloCell::empty};
  std::vector<OthelloCell> randomCellsList;
  for (int i = 0; i < 64; ++i)
    randomCellsList.push_back(options[std::rand() % 3]);
  Board board2;
  for (int x = 0; x < 8; ++x) {
    for (int y = 0; y < 8; ++y) {
      board2.placeTile(x, y, randomCellsList.back());
      randomCellsList.pop_back();
    }
  }
  std::cout << "Random cells board:\n";
  board2.print();

  // non-square board with random cells
  const unsigned int width = 16;
  const unsigned int height = 8;
  for (int i = 0; i < width * height; ++i)
    randomCellsList.push_back(options[std::rand() % 3]);
  Board board3(width, height);
  for (int x = 0; x < width; ++x) {
    for (int y = 0; y < height; ++y) {
      board3.placeTile(x, y, randomCellsList.back());
      randomCellsList.pop_back();
    }
  }
  std::cout << "Non-square with random cells:\n";
  board3.print();
}
