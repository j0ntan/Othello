#ifndef EVALUATE_HPP
#define EVALUATE_HPP

#include "othellogame/OthelloBoard.hpp"
#include "othellogame/OthelloCell.hpp"
#include "othellogame/OthelloGameState.hpp"

namespace AI {
namespace simple {
int evaluate(const OthelloGameState *gameState,
             const OthelloCell &choosersTiles) {
  int score = 0;
  if (choosersTiles == OthelloCell::black)
    score = gameState->blackScore() - gameState->whiteScore();
  else
    score = gameState->whiteScore() - gameState->blackScore();
  return score;
}
} // namespace simple
} // namespace AI

#endif // EVALUATE_HPP
