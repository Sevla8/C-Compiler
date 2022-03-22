#pragma once

#include "VDescriptor.h"
#include <map>
#include <string>

using namespace std;

class SymbolTable {
public:
  bool exists(std::string id);
  void add(std::string id);
  VDescriptor& get(std::string id);
  string getTempVariable();
  void clearTempVariable();

protected:
  std::map<std::string, VDescriptor> symbols;
  int var_count = 1;
  int tmp_count = 0;
  int max_tmp = 0;
};
