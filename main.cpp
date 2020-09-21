#include "AI.hpp"

//#define AI_VS_AI

int main() {
  bool who = false;
  #ifdef AI_VS_AI
    string playerNames[2] = { "AI(O)", "AI(X)" };
  #else
    string playerNames[2] = { "AI(O)", "Player(X)" };
  #endif
  Game * game = new Game(playerNames, &who);
  AI * ai = new AI();
  #ifdef AI_VS_AI
    AI * ai2 = new AI(fState::X);
  #endif
  int x, y;
  while (!game->getIsOver()) {
    if (who) {
      #ifdef AI_VS_AI
        vector<int> aiStep = ai2->makeStep(game->getField());
        x = aiStep[0];
        y = aiStep[1];
      #else
        cin >> x >> y;
      #endif
    } else {
      vector<int> aiStep = ai->makeStep(game->getField());
      x = aiStep[0];
      y = aiStep[1];
    } 

    if (game->makeStep(x, y, who ? fState::X : fState::O))
      who = !who;
  }

  delete ai;
  #ifdef AI_VS_AI
    delete ai2;
  #endif
  delete game;
  return 0;
}