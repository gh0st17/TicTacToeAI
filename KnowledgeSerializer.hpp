#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
#include <time.h>
#include <unistd.h>

using namespace std;

enum fStateAI {
  myStep, opponentStep, NA
};

typedef vector<vector<fStateAI>> FieldAI;
typedef vector<FieldAI> FieldHistory;
typedef vector<FieldHistory> ArrayOfHistory;
typedef map<FieldAI, ArrayOfHistory> Knowledge;

class KnowledgeSerializer {
  private:
    
    static vector<string> split(string str, char delimiter);

  public:
    
    static FieldAI getFieldFromString(string str);
    static Knowledge readKnowledge();
    static void writeKnowledge(Knowledge knowledge);
    static void printKnowledge(Knowledge knowledge);

};
