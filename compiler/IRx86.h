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
  IRInstrx86(CFG* cfg_, BasicBlock* bb_, Operation op_, vector<string>& params_,int num_block) : IRInstr(cfg_, bb_, op_, params_,num_block) {}

	/** Actual code generation */
	virtual void gen_asm(ostream &o);
 protected:
};



class CFGx86 : public CFG {
 public:
	CFGx86(SymbolTable& sym) : CFG(sym) {}
	
	virtual BasicBlock * create_bb();
	virtual void add_bb(BasicBlock* newBB);
	virtual void set_current_bb(BasicBlock* bb);
	virtual BasicBlock* get_current_bb();
	virtual void create_jumps(BasicBlock* exit_true,BasicBlock* exit_false,ostream &o);
	virtual SymbolTable& get_table();

  virtual void add_IRInstr_to_current(IRInstr::Operation op, vector<string>& params);

	// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	virtual void gen_asm(ostream& o);
	virtual string IR_reg_to_asm(string reg);
	virtual void gen_asm_prologue(ostream& o);
	virtual void gen_asm_epilogue(ostream& o);

 protected:
};

