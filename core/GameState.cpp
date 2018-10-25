#include "GameState.hpp"

const OthelloBoard &GameState::board() const noexcept {}

int GameState::blackScore() const noexcept {}

int GameState::whiteScore() const noexcept {}

bool GameState::isGameOver() const noexcept {}

bool GameState::isBlackTurn() const noexcept {}

bool GameState::isWhiteTurn() const noexcept {}

bool GameState::isValidMove(int x, int y) const {}

void GameState::makeMove(int x, int y) {}

std::unique_ptr<OthelloGameState> GameState::clone() const {}
