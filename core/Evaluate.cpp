#include "Evaluate.hpp"

namespace {
inline int mobilityScore(const OthelloGameState *gameState) {
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

inline int scoreCornerCells(const OthelloGameState *gameState,
                            const OthelloCell &currentPlayer,
                            const OthelloCell &opponent) {
  const int corner_cell_value = 4;
  int score = 0;

  if (gameState->board().cellAt(0, 0) == currentPlayer)
    score += corner_cell_value;
  else if (gameState->board().cellAt(0, 0) == opponent)
    score -= corner_cell_value;
  if (gameState->board().cellAt(0, 7) == currentPlayer)
    score += corner_cell_value;
  else if (gameState->board().cellAt(0, 7) == opponent)
    score -= corner_cell_value;
  if (gameState->board().cellAt(7, 0) == currentPlayer)
    score += corner_cell_value;
  else if (gameState->board().cellAt(7, 0) == opponent)
    score -= corner_cell_value;
  if (gameState->board().cellAt(7, 7) == currentPlayer)
    score += corner_cell_value;
  else if (gameState->board().cellAt(7, 7) == opponent)
    score -= corner_cell_value;

  return score;
}

inline int continuousRow(const OthelloGameState *gameState,
                         const OthelloCell targetCell, const int searchStartX,
                         const int searchStartY) {
  int continuous_begin = searchStartX;
  while (gameState->board().isValidCell(continuous_begin, searchStartY) &&
         gameState->board().cellAt(continuous_begin, searchStartY) !=
             targetCell)
    ++continuous_begin;

  int continuous_end = continuous_begin;
  while (gameState->board().isValidCell(continuous_end, searchStartY) &&
         gameState->board().cellAt(continuous_end, searchStartY) == targetCell)
    ++continuous_end;

  return continuous_end - continuous_begin;
}

inline int continuousCol(const OthelloGameState *gameState,
                         const OthelloCell targetCell, const int searchStartX,
                         const int searchStartY) {
  int continuous_begin = searchStartY;
  while (gameState->board().isValidCell(searchStartX, continuous_begin) &&
         gameState->board().cellAt(searchStartX, continuous_begin) !=
             targetCell)
    ++continuous_begin;

  int continuous_end = continuous_begin;
  while (gameState->board().isValidCell(searchStartX, continuous_end) &&
         gameState->board().cellAt(searchStartX, continuous_end) == targetCell)
    ++continuous_end;

  return continuous_end - continuous_begin;
}

inline int scoreAdjacentStableCells(const OthelloGameState *gameState,
                                    const OthelloCell &currentPlayer) {
  const int adjacent_stable_value = 2;
  int adjacent_stable_count = 0;

  // look at top-left
  for (int i = 0; i < 4; ++i) {
    adjacent_stable_count += continuousRow(gameState, currentPlayer, i + 1, i);
    adjacent_stable_count += continuousCol(gameState, currentPlayer, i, i + 1);
  }

  return adjacent_stable_count * adjacent_stable_value;
}
} // namespace

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
  int score = 0;
  score += mobilityScore(gameState);

  if ((gameState->isBlackTurn() && choosersTiles == OthelloCell::white) ||
      (gameState->isWhiteTurn() && choosersTiles == OthelloCell::black))
    score *= -1;

  return score;
}

int AI::stronger::stableScore(const OthelloGameState *gameState) {
  const OthelloCell current_player =
      gameState->isBlackTurn() ? OthelloCell::black : OthelloCell::white;
  const OthelloCell opponent = current_player == OthelloCell::black
                                   ? OthelloCell::white
                                   : OthelloCell::black;
  int score = 0;

  score += scoreCornerCells(gameState, current_player, opponent);
  score += scoreAdjacentStableCells(gameState, current_player);

  return score;
}
