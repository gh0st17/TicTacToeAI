#include "game.hpp"

Game::Game(string * playerNames, bool * who) {
  this->playerNames = playerNames;
  this->who = who;

  field.resize(3);

  for (int i = 0; i < 3; i++) {
    field[i].resize(3);
    for (int j = 0; j < 3; j++)
      field[i][j] = fState::Unused;
  }

  printField();
 }

Game::~Game() {}

bool Game::makeStep(int x, int y, fState value) {
  if (stepValid(x, y)) {
    field[x][y] = *who ? fState::X : fState::O;
    stepCounter++;
    if (chkWinState() || stepCounter >= 9) {
      isOver = true;
      if (!chkWinState() && stepCounter >= 9)
        isNA = true;
    }
    printField();
    return true;
  } else cout << "You cant do this...\n";

  return false;
}

bool Game::chkWinState() {
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

bool Game::stepValid(int x, int y) {
  return (x < 3 && y < 3 && field[x][y] == fState::Unused);
}

void Game::printField() {
  system("clear");
  cout << "  0 1 2\n";
  for (int i = 0; i < 3; i++) {
    cout << i;
    for (int j = 0; j < 3; j++) {
      if (field[i][j] == fState::Unused) cout << " -";
      else if (field[i][j] == fState::X) cout << " X";
      else if (field[i][j] == fState::O) cout << " O";
    }
    cout << '\n';
  }

  if (!isOver && !isNA)
    cout << "Now player is " << (stepCounter == 0 ? playerNames[*who] : playerNames[!(*who)]) << '\n';
  else if (isOver && chkWinState())
    cout << "Player " << playerNames[*who] << " win!\n";
  else if (isOver && isNA) 
    cout << "N/A win -_-\n";
}

bool Game::getIsOver() { return this->isOver; }

vector<vector<fState>> Game::getField() { return field; }