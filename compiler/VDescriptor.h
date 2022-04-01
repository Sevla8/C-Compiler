#pragma once

class VDescriptor {
public:
  VDescriptor(int off,int blockNum) : offset(off),blockNumber(blockNum) {}
  int getOffset();
  bool getUsed();
  void setUsed(bool v);
  int getBlockNumber();
  
protected:
  int offset;
  bool used= false;
  int blockNumber;
};

