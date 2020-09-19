#include "AI.hpp"
#include <cassert>
int main() {
  bool who = false;
  string playerNames[2] = { "AI(O)", "Player(X)" };
  Game * game = new Game(playerNames, &who);
  AI * ai = new AI();
  int x, y;
  while (!game->getIsOver()) {
    if (who)
      cin >> x >> y;
    else {
      vector<int> aiStep = ai->makeStep(game->getField());
      x = aiStep[0];
      y = aiStep[1];
    } 

    if (game->makeStep(x, y, who ? fState::X : fState::O))
      who = !who;
  }
}