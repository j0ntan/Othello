#ifndef EVALUATE_HPP
#define EVALUATE_HPP

#include "othellogame/OthelloCell.hpp"
#include "othellogame/OthelloGameState.hpp"
#include <utility>

namespace AI {
int quickMoveEval(const std::pair<int, int> &move);

namespace simple {
int evaluate(const OthelloGameState *gameState,
             const OthelloCell &choosersTiles);
} // namespace simple
} // namespace AI

#endif // EVALUATE_HPP
