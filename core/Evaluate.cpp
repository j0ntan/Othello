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
                           const OthelloCell &choosersTiles) {
  return 0;
}

int AI::stronger::mobilityScore(const OthelloGameState *gameState) {
  const OthelloCell current =
      gameState->isBlackTurn() ? OthelloCell::black : OthelloCell::white;
  const OthelloCell opponent =
      current == OthelloCell::black ? OthelloCell::white : OthelloCell::black;
  const int immediate_cell_value = 4;
  const int potential_cell_value = 1;
  int score = 0;

  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
      if (gameState->isValidMove(x, y)) // immediate mobility
        score += immediate_cell_value + AI::quickMoveEval({x, y});
      else { // potential mobility
        const bool cell_is_empty =
            gameState->board().cellAt(x, y) == OthelloCell::empty;
        const bool opponent_cell_above =
            gameState->board().isValidCell(x, y - 1) &&
            gameState->board().cellAt(x, y - 1) == opponent;
        const bool opponent_cell_below =
            gameState->board().isValidCell(x, y + 1) &&
            gameState->board().cellAt(x, y + 1) == opponent;
        const bool opponent_cell_left =
            gameState->board().isValidCell(x - 1, y) &&
            gameState->board().cellAt(x - 1, y) == opponent;
        const bool opponent_cell_right =
            gameState->board().isValidCell(x + 1, y) &&
            gameState->board().cellAt(x + 1, y) == opponent;
        if (cell_is_empty && (opponent_cell_above || opponent_cell_below ||
                              opponent_cell_left || opponent_cell_right))
          score += potential_cell_value;
      }

  return score;
}
