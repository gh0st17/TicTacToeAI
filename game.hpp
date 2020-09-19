#include <vector>
#include <iostream>

using namespace std;

enum fState {
  X, O, Unused
};

class Game {

  private:
   
   vector<vector<fState>> field;
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
   bool makeStep(int x, int y, fState value);
   bool getIsOver();
   bool getIsNA();
   vector<vector<fState>> getField();
   
};