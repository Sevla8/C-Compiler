#pragma once

class VDescriptor {
public:
  VDescriptor(int off) : offset(off) {}
  int getOffset();

protected:
  int offset;
};

