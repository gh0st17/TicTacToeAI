#include <vector>
#include <iostream>
#include <random>
#include <time.h>
#include <unistd.h> 
#include "game.hpp"

using namespace std;

class AI {

  private:
    fState myLetter;
    fState notMyLetter;
    vector<int> lastStep;
    vector<vector<fState>> fieldMask;

    vector<int> analyseField(vector<vector<fState>> field);
    bool isMyStep(vector<vector<fState>> field, int x, int y);
    bool canIStepHere(vector<vector<fState>> field, vector<int> step);
    bool canIStepHere(vector<vector<fState>> field, int x, int y);
    bool chkWinState(vector<vector<fState>> field);
    unsigned short countUnused(vector<vector<fState>> field);
    vector<int> getFreeCell(vector<vector<fState>> field);

  public:

    AI(fState myLetter = fState::O);
    ~AI();
    vector<int> makeStep(vector<vector<fState>> field);

};
