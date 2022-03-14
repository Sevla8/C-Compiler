#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

// Declarations from the parser
#include "SymbolTable.h"
#include "IR.h"

using namespace std;

//! The class for one 3-address instruction
class IRInstrx86 : public IRInstr{
 
  public:
  IRInstrx86(CFG* cfg_, BasicBlock* bb_, Operation op_, vector<string>& params_) : IRInstr(cfg_, bb_, op_, params_) {}

	/** Actual code generation */
	virtual void gen_asm(ostream &o);
 protected:
};



class CFGx86 : public CFG {
 public:
	CFGx86(SymbolTable& sym) : CFG(sym) {}
	
	virtual void create_bb();

  virtual void add_IRInstr_to_current(IRInstr::Operation op, vector<string>& params);

	// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	virtual void gen_asm(ostream& o);
	virtual string IR_reg_to_asm(string reg);
	virtual void gen_asm_prologue(ostream& o);
	virtual void gen_asm_epilogue(ostream& o);

 protected:
};

