#pragma once

class VDescriptor {
public:
  enum TYPE {
    tint = 0,
    tchar = 1
  };
  
  //VDescriptor(int off) : offset(off), type(tint) {}
  VDescriptor(int off, TYPE t) : offset(off), type(t) {}
  int getOffset();
  bool getUsed();
  void setUsed(bool v);
  int getType() {return type;};

protected:
  TYPE type; 
  int offset;
  bool used= false;
};

