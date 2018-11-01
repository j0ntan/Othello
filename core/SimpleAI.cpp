#include "SimpleAI.hpp"
#include "core/GameState.hpp"
#include <cstdlib>
#include <ctime>

namespace {
int eval(const OthelloGameState *s, const OthelloCell &choosersTiles) {}

int search(OthelloGameState *s, int depth, bool myTurn,
           const OthelloCell &choosersTiles) {}
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
