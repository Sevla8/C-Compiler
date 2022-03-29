#pragma once

class VDescriptor {
public:
  VDescriptor(int off,int blockNum) : offset(off),blockNumber(blockNum) {}
  int getOffset();
  int getBlockNumber();

protected:
  int offset;
  int blockNumber;
};

