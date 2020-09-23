#pragma once
#include "KnowledgeSerializer.hpp"

using namespace std;

enum fState {
  X, O, Unused
};

typedef vector<vector<fState>> Field;

class Game {

  private:
   
   Field field;
   unsigned stepCounter = 0;
   string * playerNames;
   bool isOver = false;
   bool isNA = false;
   bool * who;

   bool chkWinState();
   bool stepValid(int x, int y);
   void printField();
   
  public:
   
   Game(string * playerNames, bool * who);
   ~Game();
   bool makeStep(int x, int y, fState value);
   bool getIsOver();
   bool getIsNA();
   Field getField();
   static void printField(Field field);
   
};