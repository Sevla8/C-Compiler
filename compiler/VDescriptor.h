#pragma once

class VDescriptor {
public:
  enum TYPE {
    tvoid=0,
    tint = 1,
    tchar = 2,
  };
  
  //VDescriptor(int off) : offset(off), type(tint) {}
  VDescriptor(int off, TYPE t) : offset(off), type(t) {}
  int getOffset();
  bool getUsed();
  void setUsed(bool v);
  TYPE getType() {return type;};

protected:
  TYPE type; 
  int offset;
  bool used= false;
};

