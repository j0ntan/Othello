#include "StrongerAI.hpp"
#include "core/Evaluate.hpp"
#include "core/GameState.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>

namespace {
const int eval_range = 1000;

bool compareMoves(const std::pair<int, int> &m1,
                  const std::pair<int, int> &m2) {
  return AI::quickMoveEval(m1) < AI::quickMoveEval(m2);
}

std::vector<std::pair<int, int>>
findAvailableMoves(const OthelloGameState &state) {
  std::vector<std::pair<int, int>> moves;
  const auto width = state.board().width();
  const auto height = state.board().height();
  for (int x = 0; x < width; ++x)
    for (int y = 0; y < height; ++y)
      if (state.isValidMove(x, y))
        moves.emplace_back(std::make_pair(x, y));
  return moves;
}

int search(OthelloGameState *s, int depth, bool myTurn,
           const OthelloCell &choosersTiles, int alpha, int beta) {
  if (depth == 0)
    return AI::stronger::evaluate(s, choosersTiles);
  else {
    if (myTurn) {
      int max_score = -1 * eval_range;
      auto available_moves = findAvailableMoves(*s);
      std::sort(std::begin(available_moves), std::end(available_moves),
                compareMoves);
      std::reverse(std::begin(available_moves), std::end(available_moves));
      for (const auto &move : available_moves) {
        const auto &x = move.first;
        const auto &y = move.second;
        const std::unique_ptr<OthelloGameState> clone = s->clone();
        clone->makeMove(x, y);
        const int score =
            search(clone.get(), depth - 1, !myTurn, choosersTiles, alpha, beta);
        max_score = std::max(score, max_score);
        alpha = std::max(alpha, max_score);
        if (beta <= alpha)
          return max_score;
      }
      if (max_score == -1 * eval_range)
        return AI::stronger::evaluate(s, choosersTiles);
      else
        return max_score;
    } else {
      int min_score = eval_range;
      auto available_moves = findAvailableMoves(*s);
      std::sort(std::begin(available_moves), std::end(available_moves),
                compareMoves);
      std::reverse(std::begin(available_moves), std::end(available_moves));
      for (const auto &move : available_moves) {
        const auto &x = move.first;
        const auto &y = move.second;
        const std::unique_ptr<OthelloGameState> clone = s->clone();
        clone->makeMove(x, y);
        const int score =
            search(clone.get(), depth - 1, !myTurn, choosersTiles, alpha, beta);
        min_score = std::min(score, min_score);
        beta = std::min(beta, min_score);
        if (beta <= alpha)
          return min_score;
      }
      if (min_score == eval_range)
        return AI::stronger::evaluate(s, choosersTiles);
      else
        return min_score;
    }
  }
}
} // namespace

std::pair<int, int> StrongerAI::chooseMove(const OthelloGameState &state) {
  std::srand(std::time(nullptr));
  const int depth = 7;
  const OthelloCell currentPlayerTiles =
      state.isWhiteTurn() ? OthelloCell::white : OthelloCell::black;

  int best_move_x = 0, best_move_y = 0, best_score = -1 * eval_range;
  auto available_moves = findAvailableMoves(state);
  std::sort(std::begin(available_moves), std::end(available_moves),
            compareMoves);
  std::reverse(std::begin(available_moves), std::end(available_moves));
  for (const auto &move : available_moves) {
    const auto &x = move.first;
    const auto &y = move.second;
    const std::unique_ptr<OthelloGameState> newState = state.clone();
    newState->makeMove(x, y);
    const int score = search(newState.get(), depth - 1, false,
                             currentPlayerTiles, -1 * eval_range, eval_range);
    if (score > best_score || (score == best_score && std::rand() % 2)) {
      best_score = score;
      best_move_x = x;
      best_move_y = y;
    }
  }

  return std::make_pair(best_move_x, best_move_y);
}
