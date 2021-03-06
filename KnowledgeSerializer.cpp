#include "KnowledgeSerializer.hpp"
#include "game.hpp"
#include "AI.hpp"

Knowledge KnowledgeSerializer::readKnowledge() {
  Knowledge knowledge;
  ifstream ifs("knows.bin");
  if (ifs.fail()) return knowledge;
  string line;
  while(ifs >> line) {
    cout << line << endl;
    vector<string> keyAndValue = split(line, '-');
    cout << keyAndValue.size() << endl;
    FieldAI key = getFieldFromString(keyAndValue[0]);
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
    knowledge[key] = value;
  }
  return knowledge;
}

void KnowledgeSerializer::writeKnowledge(Knowledge knowledge) {
  if (!knowledge.size()) return;
  ofstream ofs("knows.bin");
  for (Knowledge::iterator i = knowledge.begin(); i != knowledge.end(); ++i) {
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
        if (game != it->size() - 1) ofs << '|';
      }
      ofs << '?';
    }
    ofs << '\n';
  }
  ofs.close();
}

vector<string> KnowledgeSerializer::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;
	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
	return internal;
}

FieldAI KnowledgeSerializer::getFieldFromString(string str) {
  vector<string> rows = split(str, '.');
  FieldAI field(3, vector<fStateAI>(3, fStateAI::NA));
  int x = 0, y = 0;
  for (vector<string>::iterator it = rows.begin(); it != rows.end(); ++it) {
    vector<string> row = split((*it), ',');
    y = 0;
    for (vector<string>::iterator it2 = row.begin(); it2 != row.end(); ++it2) {
      stringstream value;
      value << (*it2);
      int tmp;
      value >> tmp;
      field[x][y] = (fStateAI)tmp;
      y++;
    }
    x++;
  }
  return field;
}

void KnowledgeSerializer::printKnowledge(Knowledge knowledge) {
  for (Knowledge::iterator it = knowledge.begin(); it != knowledge.end(); ++it) {
    cout << "Key:\n";
    AI::printField((*it).first);
    cout << "Values:\n";
    for (ArrayOfHistory::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2) {
      for (int i = 0; i < (*it2).size(); i++) {
        AI::printField((*it2)[i]);
        cout << "\n";
      }
      cout << "-------------------\n";
    }
  }

  cout << "===================\n\n";
}