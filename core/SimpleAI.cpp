#include "SimpleAI.hpp"
#include "core/Evaluate.hpp"
#include "core/GameState.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>

namespace {
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
    return AI::simple::evaluate(s, choosersTiles);
  else {
    if (myTurn) {
      int max_score = -64;
      for (int x = 0; x < s->board().width(); ++x)
        for (int y = 0; y < s->board().height(); ++y)
          if (s->isValidMove(x, y)) {
            std::unique_ptr<OthelloGameState> clone = s->clone();
            clone->makeMove(x, y);
            int score = search(clone.get(), depth - 1, !myTurn, choosersTiles,
                               alpha, beta);
            max_score = std::max(score, max_score);
            alpha = std::max(alpha, max_score);
            if (beta <= alpha)
              return max_score;
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
            int score =
                search(s, depth - 1, !myTurn, choosersTiles, alpha, beta);
            min_score = std::min(score, min_score);
            beta = std::min(beta, min_score);
            if (beta <= alpha)
              return min_score;
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
  const int depth = 7;
  const int width = state.board().width();
  const int height = state.board().height();
  const OthelloCell currentPlayerTiles =
      state.isWhiteTurn() ? OthelloCell::white : OthelloCell::black;

  int best_move_x = 0, best_move_y = 0, best_score = -100;
  auto available_moves = findAvailableMoves(state);
  std::sort(std::begin(available_moves), std::end(available_moves),
            compareMoves);
  std::reverse(std::begin(available_moves), std::end(available_moves));
  for (const auto &move : available_moves) {
    const auto &x = move.first;
    const auto &y = move.second;
    std::unique_ptr<OthelloGameState> newState = state.clone();
    newState->makeMove(x, y);
    int score =
        search(newState.get(), depth - 1, false, currentPlayerTiles, -64, 64);
    if (score > best_score || (score == best_score && std::rand() % 2)) {
      best_score = score;
      best_move_x = x;
      best_move_y = y;
    }
  }

  return std::make_pair(best_move_x, best_move_y);
}
