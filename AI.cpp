#include "AI.hpp"

vector<int> AI::analyseField(vector<vector<fState>> field) {
  vector<int> step(2, 0);

  // First AI step
  if (countUnused(field) == 9) {
    srand (time(NULL));
    do {
      step[0] = rand() % 3;
      usleep(3000000);
      step[1] = rand() % 3;
      if (canIStepHere(field, step))
        break;
    } while (true);
    lastStep = step;
    return step;
  }

  if (countUnused(field) <= 1) {
    step = getFreeCell(field);
    return step;
  }  

  fieldMask = field;

  // Check last step
  for (int i = 0; i < 3; i++) {
    if (isMyStep(fieldMask, i, lastStep[1])) continue;
    if (canIStepHere(fieldMask, i, lastStep[1])) {
      fieldMask[i][lastStep[1]] = myLetter;
      if (!chkWinState(fieldMask)) continue;
      else {
        step[0] = i;
        step[1] = lastStep[1];
        lastStep = step;
        return step;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    if (isMyStep(fieldMask, lastStep[0], i)) continue;
    if (canIStepHere(fieldMask, lastStep[0], i)) {
      fieldMask[lastStep[0]][i] = myLetter;
      if (!chkWinState(fieldMask)) continue;
      else {
        step[0] = lastStep[0];
        step[1] = i;
        lastStep = step;
        return step;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    fieldMask = field;
    for (int j = 0; j < 3; j++) {
      if (isMyStep(fieldMask, i, j)) continue;
      if (canIStepHere(fieldMask, i, j)) {
        fieldMask[i][j] = myLetter;
        if (!chkWinState(fieldMask)) continue;
        else {
          step[0] = i;
          step[1] = j;
          lastStep = step;
          return step;
        }
      }
    }
  }

  return step;
}

bool AI::isMyStep(vector<vector<fState>> field, int x, int y) {
  return field[x][y] == myLetter;
}

bool AI::canIStepHere(vector<vector<fState>> field, vector<int> step) {
  return field[step[0]][step[1]] == fState::Unused;
}

bool AI::canIStepHere(vector<vector<fState>> field, int x, int y) {
  return field[x][y] == fState::Unused;
}

bool AI::chkWinState(vector<vector<fState>> field) {
  for (int i = 0; i < 3; i++)
    if (field[0][i] == field[1][i] &&
        field[1][i] == field[2][i] &&
        field[0][i] != fState::Unused)
          return true;

  for (int i = 0; i < 3; i++)
    if (field[i][0] == field[i][1] &&
        field[i][1] == field[i][2] &&
        field[i][0] != fState::Unused)
          return true;
  
  if (field[0][0] == field[1][1] &&
      field[1][1] == field[2][2] &&
      field[0][0] != fState::Unused)
        return true;
  
  if (field[0][2] == field[1][1] &&
      field[1][1] == field[2][0] &&
      field[0][2] != fState::Unused)
        return true;

  return false;
}

unsigned short AI::countUnused(vector<vector<fState>> field) {
  unsigned short count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      if(canIStepHere(field, i, j)) count++;
  }
  return count;
}

vector<int> AI::getFreeCell(vector<vector<fState>> field) {
  vector<int> step(2, 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      if(canIStepHere(field, i, j)) {
        step[0] = i;
        step[1] = j;
        break;
      }
  }
  return step;
}

AI::AI() { }

AI::~AI() { }

vector<int> AI::makeStep(vector<vector<fState>> field) {
  return analyseField(field);
}
