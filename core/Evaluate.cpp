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

int AI::quickMoveEval(const std::pair<int, int> &move) {
  const int scores[8][8] = {
      {4, -3, 2, 2, 2, 2, -3, 4},       {-3, -4, -1, -1, -1, -1, -4, -3},
      {2, -1, 1, 0, 0, 1, -1, 2},       {2, -1, 0, 1, 1, 0, -1, 2},
      {2, -1, 0, 1, 1, 0, -1, 2},       {2, -1, 1, 0, 0, 1, -1, 2},
      {-3, -4, -1, -1, -1, -1, -4, -3}, {4, -3, 2, 2, 2, 2, -3, 4}};
  return scores[move.second][move.first];
}

int AI::stronger::evaluate(const OthelloGameState *gameState,
                           const OthelloCell &choosersTiles) {}
