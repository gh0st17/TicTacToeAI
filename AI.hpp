#include "game.hpp"

using namespace std;

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
    vector<int> getRandomStep(Field field);

  public:

    AI(fState myLetter = fState::O);
    ~AI();
    vector<int> makeStep(Field field);
    void saveKnowledge(Field field);

};
