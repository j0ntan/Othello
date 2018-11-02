#ifndef STRONGERAI_HPP
#define STRONGERAI_HPP

#include "othellogame/OthelloAI.hpp"

class StrongerAI : public OthelloAI {
public:
  ~StrongerAI() final = default;

  // chooseMove() takes a constant OthelloGameState and decides on
  // a move, returning a std::pair whose elements describe the (x, y)
  // coordinate of the cell where the chosen move should be made.
  std::pair<int, int> chooseMove(const OthelloGameState &state) final;
};

#endif // STRONGERAI_HPP
