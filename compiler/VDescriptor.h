#pragma once

#include <string>

using namespace std;

class VDescriptor {
public:
  enum TYPE {
    tvoid=0,
    tint = 1,
    tchar = 2,
  };
  VDescriptor(int off, TYPE t,int blockNum) : offset(off),type(t),blockNumber(blockNum) {}
  int getOffset();
  bool getUsed();
  void setUsed(bool v);
  int getBlockNumber();
  TYPE getType() {return type;};
  
protected:
  TYPE type; 
  int offset;
  bool used= false;
  int blockNumber;
};

VDescriptor::TYPE getTypeFromString(string type);