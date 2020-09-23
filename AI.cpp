#include "AI.hpp"

#define debug

vector<int> AI::analyseField(Field field) {
  vector<int> step(2, 0);

  // First AI step
  if (countUnused(field) == 9) {
    step = getRandomStep(field);
    return step;
  }

  if (countUnused(field) <= 1) {
    step = getFreeCell(field);
    #ifdef debug
      cout << "Free Cell\n";
    #endif
    return step;
  }

  if (knowlege.size())
    step = analyseKnowledge(field);

  if (step == vector<int>(2, -1) || step == vector<int>(2, 0)) {
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
  } else {
    return step;
  }
}

double AI::getPercentage(Field gameField, Field relative) {  
  double percentage = 0.f;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (gameField[x][y] == relative[x][y]) 
        percentage += 1.0 / 9.0;
    }
  }
  return percentage;
}

double AI::getPercentage(FieldAI gameField, FieldAI relative) {  
  double percentage = 0.f;
  Field tmp = convertAItoGame(relative);
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (gameField[x][y] == relative[x][y]) 
        percentage += 1.0 / 9.0;
    }
  }
  return percentage;
}

FieldAI AI::compare(FieldAI field) {
  double max = 0.f;
  FieldAI maxField;
  cout << "Knows size: " << knowlege.size() << '\n';

  for (Knowledge::iterator it = knowlege.begin(); it != knowlege.end(); ++it) {
    if (getPercentage(field, it->first) > max) {
      printField(it->first);
      maxField = it->first;
    }
  }

  return maxField;
}

FieldAI AI::compare(FieldAI field, ArrayOfHistory aH) {
  double percentage = 0.f, max = 0.f;
  FieldAI maxField = FieldAI(3, vector<fStateAI>(3 ,fStateAI::NA));
  cout << "aH size: " << knowlege[field].size() << '\n';


  for (ArrayOfHistory::iterator aHit = knowlege[field].begin(); aHit != knowlege[field].end(); ++aHit) {
    for (FieldHistory::iterator history = aHit->begin(); history != aHit->end(); ++history) {
      for (int i = 0 ; i < history->size(); i++) {
        if (getPercentage(field, history[i]) > max) {
          max = percentage;
          maxField = history[i];
        }
      }
    }
  }

  return maxField;
}

vector<int> AI::analyseKnowledge(Field field) {
  FieldAI tmp = convertGametoAI(field);
  FieldAI maxField = compare(tmp);
  fStateAI winner = whoWin(maxField);

  if (winner == fStateAI::myStep) {
    return vector<int>(2, -1); // Temporary
  } else if (winner == fStateAI::opponentStep) {
      FieldAI maxFieldInArrOfHistory = compare(tmp, knowlege[maxField]);

      printField(maxFieldInArrOfHistory);
      return vector<int>(2, -1); // Temporary      
  } else return vector<int>(2, -1);
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

fStateAI AI::whoWin(FieldAI field) {
  for (int i = 0; i < 3; i++)
    if (field[0][i] == field[1][i] &&
        field[1][i] == field[2][i] &&
        field[0][i] != fStateAI::NA)
          return field[0][i];

  for (int i = 0; i < 3; i++)
    if (field[i][0] == field[i][1] &&
        field[i][1] == field[i][2] &&
        field[i][0] != fStateAI::NA)
          return field[i][0];
  
  if (field[0][0] == field[1][1] &&
      field[1][1] == field[2][2] &&
      field[0][0] != fStateAI::NA)
        return field[0][0];
  
  if (field[0][2] == field[1][1] &&
      field[1][1] == field[2][0] &&
      field[0][2] != fStateAI::NA)
        return field[0][2];

  return fStateAI::NA;
}

void AI::printField(FieldAI field) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (field[i][j] == fStateAI::NA) cout << " N";
      else if (field[i][j] == fStateAI::opponentStep) cout << " -";
      else if (field[i][j] == fStateAI::myStep) cout << " +";
    }
    cout << endl;
  }
  cout << "---------\n";
}

FieldAI AI::convertGametoAI(Field field) {
  FieldAI fAI = FieldAI(3, vector<fStateAI>(3, fStateAI::NA));

  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (field[x][y] == myLetter) fAI[x][y] = fStateAI::myStep;
      else if (field[x][y] == notMyLetter) fAI[x][y] = fStateAI::opponentStep;
      else fAI[x][y] = fStateAI::NA;  
    }
  }

  return fAI;
}

Field AI::convertAItoGame(FieldAI field) {
  Field f = Field(3, vector<fState>(3, fState::Unused));

  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (field[x][y] == fStateAI::myStep) f[x][y] = myLetter;
      else if (field[x][y] == fStateAI::opponentStep) f[x][y] = notMyLetter;
      else f[x][y] = fState::Unused;  
    }
  }

  return f;
}

AI::AI(fState myLetter) {
  this->myLetter = myLetter;
  this->notMyLetter = (myLetter == fState::X ? fState::O : fState::X);
  knowlege = KnowledgeSerializer::readKnowledge();
}

AI::~AI() { }

vector<int> AI::makeStep(Field field) {
  vector<int> step = analyseField(field);
  field[step[0]][step[1]] = myLetter;
  currentGame.push_back(convertGametoAI(field));

  return step;
}

void AI::saveKnowledge(Field field) {
  knowlege[convertGametoAI(field)].push_back(currentGame);
  KnowledgeSerializer::writeKnowledge(knowlege);
}