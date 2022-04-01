#pragma once

#include "VDescriptor.h"
#include <map>
#include <string>
#include <iostream>



using namespace std;

class SymbolTable {
public:
  int exists(string id);
  void variablesNotUsed();
  void add(string id);
  VDescriptor& get(pair<string, int> id);
  string getTempVariable();
  void clearTempVariable();
  int getMaxStackSize();
  void addBlock();
  void setCurrentBlock(int numBlock);
  int getCurrentBlock();
  map<int, int> getBlockTree();
  bool existCurrent(string id,int blockNum);


protected:
  map<pair<string, int>, VDescriptor> symbols;
  int var_count = 1;
  int tmp_count = 0;
  int max_tmp = 0;
  int currentBlock = 0;
  map<int, int> blockTree;
};

