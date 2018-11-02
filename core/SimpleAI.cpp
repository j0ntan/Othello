#include "SimpleAI.hpp"
#include "core/Evaluate.hpp"
#include "core/GameState.hpp"
#include <cstdlib>
#include <ctime>

namespace {
int search(OthelloGameState *s, int depth, bool myTurn,
           const OthelloCell &choosersTiles) {
  if (depth == 0)
    return AI::simple::evaluate(s, choosersTiles);
  else {
    if (myTurn) {
      int max_score = -64;
      for (int x = 0; x < s->board().width(); ++x)
        for (int y = 0; y < s->board().height(); ++y)
          if (s->isValidMove(x, y)) {
            std::unique_ptr<OthelloGameState> clone = s->clone();
            clone->makeMove(x, y);
            int score = search(clone.get(), depth - 1, !myTurn, choosersTiles);
            max_score = std::max(score, max_score);
          }
      if (max_score == -64)
        return AI::simple::evaluate(s, choosersTiles);
      else
        return max_score;
    } else {
      int min_score = 64;
      for (int x = 0; x < s->board().width(); ++x)
        for (int y = 0; y < s->board().height(); ++y)
          if (s->isValidMove(x, y)) {
            s->makeMove(x, y);
            int score = search(s, depth - 1, !myTurn, choosersTiles);
            min_score = std::min(score, min_score);
          }
      if (min_score == 64)
        return AI::simple::evaluate(s, choosersTiles);
      else
        return min_score;
    }
  }
}
} // namespace

std::pair<int, int> SimpleAI::chooseMove(const OthelloGameState &state) {
  std::srand(std::time(nullptr));
  const int depth = 8;
  const int width = state.board().width();
  const int height = state.board().height();
  const OthelloCell currentPlayerTiles =
      state.isWhiteTurn() ? OthelloCell::white : OthelloCell::black;

  int best_move_x = 0, best_move_y = 0, best_score = -100;
  for (int x = 0; x < width; ++x)
    for (int y = 0; y < height; ++y)
      if (state.isValidMove(x, y)) {
        std::unique_ptr<OthelloGameState> newState = state.clone();
        newState->makeMove(x, y);
        int score =
            search(newState.get(), depth - 1, false, currentPlayerTiles);
        if (score > best_score || (score == best_score && std::rand() % 2)) {
          best_score = score;
          best_move_x = x;
          best_move_y = y;
        }
      }

  return std::make_pair(best_move_x, best_move_y);
}
