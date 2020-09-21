#include "AI.hpp"

template <typename Iter>
Iter nexti(Iter iter) {
    return ++iter;
}

vector<int> AI::analyseField(Field field) {
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

  if (field[0][0] != notMyLetter &&
      field[1][1] != notMyLetter &&
      field[2][2] != notMyLetter) {
        
      for (int i = 0; i < 3; i++) {
        if (field[i][i] == fState::Unused &&
            canIStepHere(field, i, i)) {
          step[0] = step[1] = i;
          lastStep = step;
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

void AI::writeKnowledge() {
  if (myLetter == fState::O) {
    size_t size = sizeof(knowlege);
    printf("Size knows: %zu\n", size);
    ofstream ofs("knows.bin");
    for (Knowledge::iterator i = knowlege.begin(); i != knowlege.end(); ++i) {
      //Write key
      for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
          ofs << i->first[x][y];
          if (y != 2) ofs << ',';
        }
        if (x != 2) ofs << '.';
      }
      ofs << "-";

      //Write value
      for (ArrayOfHistory::iterator it = i->second.begin(); it != i->second.end(); ++it) {
        for (int game = 0; game < it->size(); game++) {
          for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
              ofs << (*it)[game][x][y];
              if (y != 2) ofs << ',';
            }
            if (x != 2) ofs << '.';
          }
          if (game != i->first.size() - 1) ofs << '|';
        }
        if ((it!= i->second.end()) && (nexti(it) == i->second.end())) ofs << '?';
      }
      if ((i!= knowlege.end()) && (nexti(i) == knowlege.end())) ofs << '\n';
    }
    ofs.close();
  }
}

vector<string> AI::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;
	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
	return internal;
}

Field AI::getFieldFromString(string str) {
  vector<string> rows = split(str, '.');
  Field field(3, vector<fState>(3, fState::Unused));
  int x = 0, y = 0;
  for (vector<string>::iterator it = rows.begin(); it != rows.end(); ++it) {
    vector<string> row = split((*it), ',');
    y = 0;
    for (vector<string>::iterator it2 = row.begin(); it2 != row.end(); ++it2) {
      stringstream value;
      value << (*it2);
      int tmp;
      value >> tmp;
      field[x][y] = (fState)tmp;
      y++;
    }
    x++;
  }
  return field;
}

AI::AI(fState myLetter) {
  this->myLetter = myLetter;
  this->notMyLetter = (myLetter == fState::X ? fState::O : fState::X);  
  if (myLetter == fState::O) {
    ifstream ifs("knows.bin");
    string line;
    while(ifs >> line) {
      vector<string> keyAndValue = split(line, '-');
      Field key = getFieldFromString(keyAndValue[0]);
      vector<string> arrayOfHistory = split(keyAndValue[1], '?');
      ArrayOfHistory value;
      for (vector<string>::iterator it = arrayOfHistory.begin(); it != arrayOfHistory.end(); ++it) {
        vector<string> fieldHistory = split((*it), '|');
        FieldHistory fH;
        for (vector<string>::iterator it2 = fieldHistory.begin(); it2 != fieldHistory.end(); ++it2) {
          fH.push_back(getFieldFromString((*it2)));
        }
        value.push_back(fH);
      }
      knowlege[key] = value;
    }
  }
}

AI::~AI() { }

vector<int> AI::makeStep(Field field) {
  vector<int> step = analyseField(field);
  field[step[0]][step[1]] = myLetter;
  currentGame.push_back(field);

  if (!countUnused(field) || chkWinState(field)) {
    if (knowlege.find(field) == knowlege.end())
      knowlege[field].push_back(currentGame);
    writeKnowledge();
  }

  return step;
}