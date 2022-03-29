#pragma once

#include "VDescriptor.h"
#include <map>
#include <string>

using namespace std;

class SymbolTable {
public:
  int exists(string id);
  void add(std::string id);
  VDescriptor& get(std::pair<std::string, int> id);
  string getTempVariable();
  void clearTempVariable();
  void addBlock();
  void setCurrentBlock(int numBlock);
  int getCurrentBlock();
  std::map<int, int> getBlockTree();
  bool existCurrent(std::string id,int blockNum);


protected:
  std::map<std::pair<std::string, int>, VDescriptor> symbols;
  int var_count = 1;
  int tmp_count = 0;
  int max_tmp = 0;
  int currentBlock = 0;
  std::map<int, int> blockTree;
};

