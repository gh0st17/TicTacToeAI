#include "KnowledgeSerializer.hpp"

using namespace std;

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
   vector<vector<fState>> getField();
   static void printField(Field field);
   
};