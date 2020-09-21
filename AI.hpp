#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
#include <time.h>
#include <unistd.h> 
#include "game.hpp"

using namespace std;

typedef vector<vector<fState>> Field;
typedef vector<Field> FieldHistory;
typedef vector<FieldHistory> ArrayOfHistory;
typedef map<Field, ArrayOfHistory> Knowledge;

class AI {

  private:
    Knowledge knowlege;
    FieldHistory currentGame;
    fState myLetter;
    fState notMyLetter;
    vector<int> lastStep = vector<int>(2, 0);
    Field fieldMask;

    vector<int> analyseField(Field field);
    bool isMyStep(Field field, int x, int y);
    bool canIStepHere(Field field, vector<int> step);
    bool canIStepHere(Field field, int x, int y);
    bool chkWinState(Field field);
    unsigned short countUnused(Field field);
    vector<int> getFreeCell(Field field);
    void writeKnowledge();
    vector<string> split(string str, char delimiter);
    Field getFieldFromString(string str);

  public:

    AI(fState myLetter = fState::O);
    ~AI();
    vector<int> makeStep(Field field);

};
