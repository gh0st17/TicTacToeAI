#include "AI.hpp"

#define debug

vector<int> AI::analyseField(Field field) {
  vector<int> step(2, 0);

  // First AI step
  if (countUnused(field) == 9) {
    step = getRandomStep(field);
  }

  if (countUnused(field) <= 1) {
    step = getFreeCell(field);
    #ifdef debug
      cout << "Free Cell\n";
    #endif
    return step;
  }

  if (field[0][0] != notMyLetter &&
      field[1][1] != notMyLetter &&
      field[2][2] != notMyLetter) {
        
      for (int i = 0; i < 3; i++) {
        if (field[i][i] == fState::Unused &&
            canIStepHere(field, i, i)) {

              step[0] = step[1] = i;
              lastStep = step;
              #ifdef debug
                cout << "Diagonal \\\n";
              #endif
              return step;
        }
      }
  }

  if (field[0][2] != notMyLetter &&
      field[1][1] != notMyLetter &&
      field[2][0] != notMyLetter) {
        
      for (int i = 0; i < 3; i++) {
        if (field[i][2 - i] == fState::Unused &&
            canIStepHere(field, i, i)) {

              step[0] = step[1] = i;
              lastStep = step;
              #ifdef debug
                cout << "Diagonal /\n";
              #endif
              return step;
        }
      }
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
        #ifdef debug
          cout << "Vertical\n";
        #endif
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
        #ifdef debug
          cout << "Horizontal\n";
        #endif
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
          #ifdef debug
            cout << "Finding winning\n";
          #endif
          return step;
        }
      }
    }
  }

  return getRandomStep(field);
}

bool AI::isMyStep(Field field, int x, int y) {
  return field[x][y] == myLetter;
}

bool AI::canIStepHere(Field field, vector<int> step) {
  return field[step[0]][step[1]] == fState::Unused;
}

bool AI::canIStepHere(Field field, int x, int y) {
  return field[x][y] == fState::Unused;
}

bool AI::chkWinState(Field field) {
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

unsigned short AI::countUnused(Field field) {
  unsigned short count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      if(canIStepHere(field, i, j)) count++;
  }
  return count;
}

vector<int> AI::getFreeCell(Field field) {
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

vector<int> AI::getRandomStep(Field field) {
  vector<int> step(2, 0);
  srand(time(NULL));
  do {
    step[0] = rand() % 3;
    usleep(3000000);
    step[1] = rand() % 3;
    if (canIStepHere(field, step))
      break;
  } while (true);
  lastStep = step;

  #ifdef debug
    cout << "Random Step\n";
  #endif
  return step;
}

AI::AI(fState myLetter) {
  this->myLetter = myLetter;
  this->notMyLetter = (myLetter == fState::X ? fState::O : fState::X);  
  if (myLetter == fState::O) {
    knowlege = KnowledgeSerializer::readKnowledge();
  }
}

AI::~AI() { }

vector<int> AI::makeStep(Field field) {
  vector<int> step = analyseField(field);
  field[step[0]][step[1]] = myLetter;
  currentGame.push_back(field);

  return step;
}

void AI::saveKnowledge(Field field) {
  knowlege[field].push_back(currentGame);
  KnowledgeSerializer::writeKnowledge(knowlege);
}