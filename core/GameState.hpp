#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "core/Board.hpp"
#include "othellogame/OthelloGameState.hpp"

class OthelloBoard;

class GameState : public OthelloGameState {
public:
  GameState(const Board &board, bool blackMovesFirst = true);

  GameState(const GameState &gameState);

  ~GameState() final = default;

  // board() returns a reference to a constant OthelloBoard describing
  // what's on the board in this game state.
  const OthelloBoard &board() const noexcept final;

  // blackScore() returns the black player's current score.
  int blackScore() const noexcept final;

  // whiteScore() returns the white player's current score.
  int whiteScore() const noexcept final;

  // isGameOver() returns true if the game is over in this game state,
  // false otherwise.
  bool isGameOver() const noexcept final;

  // isBlackTurn() returns true if it is currently the black player's
  // turn in this game state, false otherwise.
  bool isBlackTurn() const noexcept final;

  // isWhiteTurn() returns true if it is currently the white player's
  // turn in this game state, false otherwise.
  bool isWhiteTurn() const noexcept final;

  // isValidMove() returns true if the current player whose turn it is
  // can make a valid move at cell (x, y).
  bool isValidMove(int x, int y) const final;

  // makeMove() modifies this game state by making a move on behalf of
  // the current player at cell (x, y).  If the move is invalid, an
  // OthelloException is thrown.
  void makeMove(int x, int y) final;

  // clone() makes a copy of this game state and returns a unique_ptr
  // to it.
  std::unique_ptr<OthelloGameState> clone() const final;

private:
  Board reference_board;
  bool blacksTurn;
};

#endif // GAMESTATE_HPP
