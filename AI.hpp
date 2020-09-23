#pragma once
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
    double getPercentage(Field gameField, Field relative);
    double getPercentage(FieldAI gameField, FieldAI relative);
    FieldAI compare(FieldAI field);
    FieldAI compare(FieldAI field, ArrayOfHistory aH);
    vector<int> analyseKnowledge(Field field);
    bool isMyStep(Field field, int x, int y);
    bool canIStepHere(Field field, vector<int> step);
    bool canIStepHere(Field field, int x, int y);
    bool chkWinState(Field field);
    unsigned short countUnused(Field field);
    vector<int> getFreeCell(Field field);
    vector<int> getRandomStep(Field field);
    fStateAI whoWin(FieldAI field);
    Field convertAItoGame(FieldAI field);
    FieldAI convertGametoAI(Field field);

  public:

    AI(fState myLetter = fState::O);
    ~AI();
    vector<int> makeStep(Field field);
    void saveKnowledge(Field field);
    static void printField(FieldAI field);

};
