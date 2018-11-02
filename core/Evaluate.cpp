#include "Evaluate.hpp"

int AI::simple::evaluate(const OthelloGameState *gameState,
                         const OthelloCell &choosersTiles) {
  int score = 0;
  if (choosersTiles == OthelloCell::black)
    score = gameState->blackScore() - gameState->whiteScore();
  else
    score = gameState->whiteScore() - gameState->blackScore();
  return score;
}
