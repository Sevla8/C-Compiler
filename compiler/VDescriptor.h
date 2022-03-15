#pragma once

class VDescriptor {
public:
  VDescriptor(int off) : offset(off) {}
  int getOffset();
  bool getUsed();
  void setUsed(bool v);

protected:
  int offset;
  bool used= false;
};

