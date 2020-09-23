#include "AI.hpp"

#define AI_VS_AI

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
        cout << "> ";
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

  ai->saveKnowledge(game->getField());
  ai2->saveKnowledge(game->getField());

  delete ai;
  #ifdef AI_VS_AI
    delete ai2;
  #endif
  delete game;
/*
  FieldHistory fh;
  ArrayOfHistory aH;
  Knowledge k;
  
  fh.push_back(KnowledgeSerializer::getFieldFromString("1,2,2.2,0,1.2,1,0"));
  fh.push_back(KnowledgeSerializer::getFieldFromString("1,1,2.2,0,1.2,1,0"));
  fh.push_back(KnowledgeSerializer::getFieldFromString("1,1,1.2,0,1.2,1,0"));
  aH.push_back(fh);

  k[fh[0]] = aH;

  KnowledgeSerializer::writeKnowledge(k);
  //KnowledgeSerializer::printKnowledge(k);
  
  k = KnowledgeSerializer::readKnowledge();
  //KnowledgeSerializer::printKnowledge(k);
  fh.clear();
  aH.clear();
  
  fh.push_back(KnowledgeSerializer::getFieldFromString("1,2,2.2,0,1.0,0,0"));
  fh.push_back(KnowledgeSerializer::getFieldFromString("1,1,2.2,0,1.0,2,0"));
  fh.push_back(KnowledgeSerializer::getFieldFromString("1,1,1.2,0,1.0,2,2"));
  aH.push_back(fh);

  k[fh[0]] = aH;

  KnowledgeSerializer::writeKnowledge(k);
  //KnowledgeSerializer::printKnowledge(k);
  
  k = KnowledgeSerializer::readKnowledge();

  fh.push_back(KnowledgeSerializer::getFieldFromString("1,1,1.2,0,2.2,2,2"));
  aH.push_back(fh);
  k[fh[0]] = aH;
  KnowledgeSerializer::printKnowledge(k);
  KnowledgeSerializer::writeKnowledge(k);
  k = KnowledgeSerializer::readKnowledge();
  KnowledgeSerializer::printKnowledge(k);*/

  return 0;
}