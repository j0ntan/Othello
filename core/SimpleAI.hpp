#ifndef SIMPLEAI_HPP
#define SIMPLEAI_HPP

#include "othellogame/OthelloAI.hpp"

class SimpleAI : public OthelloAI {
public:
  ~SimpleAI() final = default;

  // chooseMove() takes a constant OthelloGameState and decides on
  // a move, returning a std::pair whose elements describe the (x, y)
  // coordinate of the cell where the chosen move should be made.
  std::pair<int, int> chooseMove(const OthelloGameState &state) final;
};

#endif // SIMPLEAI_HPP
