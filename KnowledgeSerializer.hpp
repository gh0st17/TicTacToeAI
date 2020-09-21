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

enum fState {
  X, O, Unused
};

typedef vector<vector<fState>> Field;
typedef vector<Field> FieldHistory;
typedef vector<FieldHistory> ArrayOfHistory;
typedef map<Field, ArrayOfHistory> Knowledge;

class KnowledgeSerializer {
  private:
    
    static vector<string> split(string str, char delimiter);

  public:
    
    static Field getFieldFromString(string str);
    static Knowledge readKnowledge();
    static void writeKnowledge(Knowledge knowledge);
    static void printKnowledge(Knowledge knowledge);

};
