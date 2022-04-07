#pragma once


/**
 * \file IR.h
 * \brief An abstraction of the IR (to be implemented for each target)
 * \author H4224
 *
 */

//-------------------------------------------------------- Include system
#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
using namespace std;

//-------------------------------------------------------- Include personnal
#include "SymbolTable.h"

class IRInstr;
class CFG;

/**
 * \class BasicBlock
 *  
 * \brief Class defining an atomic block where you can jump
 */
class BasicBlock {
 public:
	/**
	 * @brief Construct a new BasicBlock
	 * 
	 * @param cfg_ the cfg this block belongs to
	 * @param entry_label a label for this block
	 */
	BasicBlock(CFG* cfg_, string entry_label) : cfg(cfg_), label(entry_label), exit_true(nullptr),exit_false(nullptr) {}

	/**
	 * @brief Generates the asm code of this block
	 * 
	 * @param o the output stream
	 */
	void gen_asm(ostream &o);

	/**
	 * @brief Adds an instruction at the end of this block
	 * 
	 * @param instr the IR instruction
	 */
	void add_IRInstr(IRInstr* instr);

	/** \brief pointer to the next basic block, true branch. If nullptr, no jump. */ 
	BasicBlock* exit_true;
	/** \brief pointer to the next basic block, false branch. If nullptr, no jump. */ 
	BasicBlock* exit_false;
	/** \brief label of the basic block. */ 
	string label;
 protected:
	/** \brief the cfg attached to this block */ 
	CFG* cfg; 
	/** \brief the instructions themselves. */
	vector<IRInstr*> instrs;
};

/**
 * \class IRInstr
 *  
 * \brief Class defining an atomic instruction
 */
class IRInstr {
 
   public:
	/**
	 *\enum Operation 
	* 
	* \brief enum describing all the possible operations
	* 
	*/
	typedef enum {
		ldconst, // loads a constant into an identifier (arg1 = arg2)
		copy, // copy the contents of an identifier to another (arg1 = arg2)
		add, // add operation (arg1 = arg2 + arg3)
		sub, // sub operation (arg1 = arg2 - arg3)
		mul, // mul operation (arg1 = arg2 * arg3)
		div, // div operation (arg1 = arg2 / arg3)
		mod, // mod operation (arg1 = arg2 % arg3)
		neg, // neg operation (arg1 = -arg2)
		land, // bitwise and operation (arg1 = arg2 & arg3)
		lor, // bitwise or operation (arg1 = arg2 | arg3)
		lxor, // bitwise xor operation (arg1 = arg2 ^ arg3)
		lnot, // bitwise not operation (arg1 = ~arg2)
		cnot, // logical not operation (arg1 = !arg2)
		lsl, // left shift operation (arg1 = arg2 << arg3)
		lsr, // right shift operation (arg1 = arg2 >> arg3)
		rmem, // reads from a base identifier (!reg = arg1[arg2])
		wmem, // write from a base identifier (arg1[arg2] = arg3)
		call, // calls a function (arg1(arg2...))
		cmp_eq, // logical equal (arg1 = arg2==arg3)
		cmp_ne, // logical not equal (arg1 = arg2!=arg3)
		cmp_lt, // logical less than (arg1 = arg2<arg3)
		cmp_le, // logical less equal (arg1 = arg2<=arg3)
		cmp_gt, // logical greater than (arg1 = arg2>arg3)
		cmp_ge, // logical greater equal (arg1 = arg2>=arg3)
		cmp_z, // compares to 0
		cmp_zs, // compares to 0 and sets arg1 if not equal
		ret // returns from a function
	} Operation;


	/**
	 * @brief Construct a new IRInstr object
	 * 
	 * @param cfg_ the cfg this belongs to
	 * @param bb_ the basic block this belongs to
	 * @param op_ the operation type
	 * @param params_ its parameters
	 * @param num_block the block number where this instruction is executed
	 */
	IRInstr(CFG* cfg_, BasicBlock* bb_, Operation op_, vector<string>& params_,int num_block) : cfg(cfg_), bb(bb_), op(op_), params(params_),num_block(num_block) {}
	
	/**
	 * @brief Generates the asm code of this instruction
	 * 
	 * @param o the output stream
	 */
	virtual void gen_asm(ostream &o) = 0;
	
 protected:
	/** \brief the cfg attached to this intruction */ 
	CFG* cfg;
	/** \brief the block attached to this intruction */ 
	BasicBlock* bb;
	/** \brief the operation type of this instruction */ 
	Operation op;
	/** \brief params for this instruction */ 
	vector<string> params;
	/** \brief the block of the symbol table where this is executed */ 
	int num_block;
};


/**
 * \class CFG
 *  
 * \brief Class defining the control flow graph of one function
 */
class CFG {
 public:
	/**
	 * @brief Construct a new CFG object
	 * 
	 */
	CFG() : nextBBnumber(0) {}
	
	/**
	 * @brief specifies the function attributes associated to this cfg
	 * 
	 * @param type of the function
	 * @param name of the function
	 * @param params list of pairs <type, identifier> of the function
	 */
	void specify_function(VDescriptor::TYPE type, string name, vector<pair<VDescriptor::TYPE, string>>& params);

	/**
	 * @brief Create a bb object
	 * 
	 * @return BasicBlock* a pointer to the basic block created 
	 */
	BasicBlock* create_bb();

	/**
	 * @brief adds an instruction to the current block
	 * 
	 * @param op the operation type
	 * @param params the list of parameters
	 */
	virtual void add_IRInstr_to_current(IRInstr::Operation op, vector<string>& params) = 0;

	/**
	 * @brief Generates the asm code of this cfg
	 * 
	 * @param o the output stream
	 */
	virtual void gen_asm(ostream& o) = 0;

	/**
	 * @brief get the asm representation of an identifier
	 * 
	 * @param reg the identifier
	 * @return string its asm represenation
	 */
	virtual string IR_reg_to_asm(string reg) = 0;

	/**
	 * @brief get the type of an identifier
	 * 
	 * @param reg the identifier
	 * @return VDescriptor::TYPE its type
	 */
	virtual VDescriptor::TYPE get_type_reg(string reg)=0;

	/**
	 * @brief Generates the asm code for the beginning of this function
	 * 
	 * @param o the output stream
	 */
	virtual void gen_asm_prologue(ostream& o) = 0;
	
	/**
	 * @brief Generates the asm code for the ending of this function
	 * 
	 * @param o the output stream
	 */
	virtual void gen_asm_epilogue(ostream& o) = 0;

	/**
	 * @brief Set the current basic block
	 * 
	 * @param bb the new current basic block
	 */
	void set_current_bb(BasicBlock* bb);
	
	/**
	 * @brief adds a basic block to the list
	 * 
	 * @param newBB the basic block to add
	 */
	void add_bb(BasicBlock* newBB);
	
	/**
	 * @brief Get the current basic block
	 * 
	 * @return BasicBlock* a pointer to the current basic block
	 */
	BasicBlock* get_current_bb();
	
	/**
	 * @brief Create the jumps for branches at the end of a block
	 * 
	 * @param exit_true true branch
	 * @param exit_false false branch
	 * @param o the output
	 */
	virtual void create_jumps(BasicBlock* exit_true,BasicBlock* exit_false,ostream &o)=0;

	/**
	 * @brief Get the symbol table
	 * 
	 * @return SymbolTable& the symbol table
	 */
	SymbolTable& get_table();

	/**
	 * @brief Get the name of the function
	 * 
	 * @return string the name
	 */
	string get_name();

	/**
	 * @brief Get the type of the function
	 * 
	 * @return VDescriptor::TYPE the type
	 */
	VDescriptor::TYPE get_type();

	/**
	 * @brief Get the parameters of the function
	 * 
	 * @return vector<pair<VDescriptor::TYPE, string>>& the parameters
	 */
	vector<pair<VDescriptor::TYPE, string>>& get_params();

	/**
	 * @brief create a jump to the epilogue of the function
	 * 
	 * @param o the output stream
	 */
	virtual void jump_to_epilogue(ostream &o)=0;

 protected:
	/** @brief The type of the function associated to this cfg */
	VDescriptor::TYPE type;
	/** @brief The name of the function associated to this cfg */
	string name;
	/** @brief The parameters of the function associated to this cfg */
	vector<pair<VDescriptor::TYPE, string>> params;
	
	/** @brief The current basic block */
	BasicBlock* current_bb;

	/** @brief The symbol table */
	SymbolTable symbols; 
	/** @brief A counter to name the blocks */
	int nextBBnumber;
	
	/** @brief The list of all basic blocks */
	vector <BasicBlock*> bbs;
};

/**
 * \class DummyCFG
 *  
 * \brief Subclass of CFG for functions that exist and usable but are not defined in this code (e.g. standard functions putchar, getchar,...)
 */
class DummyCFG : public CFG {
 public:
	DummyCFG() {}
	
	virtual void add_IRInstr_to_current(IRInstr::Operation op, vector<string>& params) {}

	virtual void gen_asm(ostream& o) {}
	virtual string IR_reg_to_asm(string reg) {return string();}
	virtual void gen_asm_prologue(ostream& o) {}
	virtual void gen_asm_epilogue(ostream& o) {}
	virtual void create_jumps(BasicBlock* exit_true,BasicBlock* exit_false,ostream &o) {}
	virtual void jump_to_epilogue(ostream &o) {}
	virtual VDescriptor::TYPE get_type_reg(string reg){return VDescriptor::TYPE::tvoid;}
};

/**
 * \class CFGFactory
 *  
 * \brief Factory class to create CFGs based on the targetted architecture 
 */
class CFGFactory {
 public:
	/**
	 * @brief Construct a new CFGFactory object
	 * 
	 */
	CFGFactory() {}
	
	/**
	 * @brief creates a new CFG
	 * 
	 * @return CFG* a new CFG
	 */
	virtual CFG* create() = 0;

 protected:
};