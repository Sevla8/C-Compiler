#ifndef IR_H
#define IR_H

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

// Declarations from the parser
#include "SymbolTable.h"

using namespace std;
class CFG;
class BasicBlock;



//! The class for one 3-address instruction
class IRInstr {
 
   public:
	/** The instructions themselves -- feel free to subclass instead */
	typedef enum {
		ldconst,
		copy,
		add,
		sub,
		mul,
		div,
		mod,
		neg,
		land,
		lor,
		lxor,
		lsl, 
		lsr, 
		rmem,
		wmem,
		call, 
		cmp_eq,
		cmp_ne,
		cmp_lt,
		cmp_le,
		cmp_gt,
		cmp_ge,
		cmp_z,
		ret
	} Operation;


	/**  constructor */
	IRInstr(CFG* cfg_, BasicBlock* bb_, Operation op_, vector<string>& params_,int num_block) : cfg(cfg_), bb(bb_), op(op_), params(params_),num_block(num_block) {}
	
	/** Actual code generation */
	virtual void gen_asm(ostream &o) = 0; /**< x86 assembly code generation for this IR instruction */
	
 protected:
	CFG* cfg; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
	BasicBlock* bb;
	Operation op;
	vector<string> params; /**< For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
	int num_block;
	// if you subclass IRInstr, each IRInstr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design. 
};





/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
	 The entry block is the one with the same label as the AST function name.
	   (it could be the first of bbs, or it could be defined by an attribute value)
	 The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG {
 public:
	CFG(SymbolTable& sym) : symbols(sym), nextBBnumber(0) {}
	
	virtual BasicBlock* create_bb() = 0;
	virtual void add_IRInstr_to_current(IRInstr::Operation op, vector<string>& params) = 0;

	// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	virtual void gen_asm(ostream& o) = 0;
	virtual string IR_reg_to_asm(string reg) = 0; /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
	virtual void gen_asm_prologue(ostream& o) = 0;
	virtual void gen_asm_epilogue(ostream& o) = 0;

	virtual void set_current_bb(BasicBlock* bb)=0;
	virtual BasicBlock* get_current_bb()=0;
	virtual void create_jumps(BasicBlock* exit_true,BasicBlock* exit_false,ostream &o)=0;
	virtual void jump_to_epilogue(ostream &o)=0;
	virtual void add_bb(BasicBlock* newBB) = 0;
	virtual SymbolTable& get_table()=0;



 protected:
	BasicBlock* current_bb;

	SymbolTable& symbols; /**<the symbol table  */
	int nextBBnumber; /**< just for naming */
	
	vector <BasicBlock*> bbs; /**< all the basic blocks of this CFG*/
};




/**  The class for a basic block */

/* A few important comments.
	 IRInstr has no jump instructions.
	 cmp_* instructions behaves as an arithmetic two-operand instruction (add or mult),
	  returning a boolean value (as an int)

	 Assembly jumps are generated as follows:
	 BasicBlock::gen_asm() first calls IRInstr::gen_asm() on all its instructions, and then 
		    if  exit_true  is a  nullptr, 
            the epilogue is generated
        else if exit_false is a nullptr, 
          an unconditional jmp to the exit_true branch is generated
				else (we have two successors, hence a branch)
          an instruction comparing the value of test_var_name to true is generated,
					followed by a conditional branch to the exit_false branch,
					followed by an unconditional branch to the exit_true branch
	 The attribute test_var_name itself is defined when converting 
  the if, while, etc of the AST  to IR.

Possible optimization:
     a cmp_* comparison instructions, if it is the last instruction of its block, 
       generates an actual assembly comparison 
       followed by a conditional jump to the exit_false branch
*/

class BasicBlock {
 public:
	BasicBlock(CFG* cfg_, string entry_label) : cfg(cfg_), label(entry_label), exit_true(nullptr),exit_false(nullptr) {}
	void gen_asm(ostream &o){
		o<<label<<':'<<endl;
		vector<IRInstr*>::iterator it;
		for(it=instrs.begin();it!=instrs.end();it++) {
			(*it)->gen_asm(o);
		}
		cfg->create_jumps(exit_true,exit_false,o);
	}

	void add_IRInstr(IRInstr* instr) {
		instrs.push_back(instr);
	}

	// No encapsulation whatsoever here. Feel free to do better.
	BasicBlock* exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */ 
	BasicBlock* exit_false; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
	string label; /**< label of the BB, also will be the label in the generated code */
	CFG* cfg; /** < the CFG where this block belongs */
	vector<IRInstr*> instrs; /** < the instructions themselves. */
  	string test_var_name;  /** < when generating IR code for an if(expr) or while(expr) etc,
													 store here the name of the variable that holds the value of expr */
 protected:

 
};



#endif
