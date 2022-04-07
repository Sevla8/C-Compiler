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
  void add(string id, string type);
  VDescriptor& get(pair<string, int> id);
  string getTempVariable();
  void clearTempSection();
  int getMaxStackSize();
  void addBlock();
  void setCurrentBlock(int numBlock);
  int getCurrentBlock();
  map<int, int> getBlockTree();
  bool existCurrent(string id,int blockNum);
  void setVoid(bool v);
  bool isVoid();


protected:
  void alignStack();

  map<pair<string, int>, VDescriptor> symbols;
  int stack_size = 0;
  int tmp_size = 0;
  int max_tmp = 0;
  int currentBlock = 0;
  map<int, int> blockTree;
  bool is_void;
};

