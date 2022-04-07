#pragma once
/**
 * \file IRInstrx86.h
 * \brief Definition of specific classes for x86
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
#include "IR.h"


/**
 * \class IRInstrx86
 *  
 * \brief Class defining the assembly instructions for x86
 */
class IRInstrx86 : public IRInstr{
  public:
  /**
   * \brief Construct a new IRInstrx86 object
   * 
   * \param cfg_ the control flow graph attached to the instructions
   * \param bb_ the basic block corresponding to the level where instructions have to be written
   * \param op_ the operations 
   * \param params_ register or const
   * \param num_block the number of block declared
   */
  	IRInstrx86(CFG* cfg_, BasicBlock* bb_, Operation op_, vector<string>& params_,int num_block) : IRInstr(cfg_, bb_, op_, params_,num_block) {}

	/**
	 * \brief Actual code generation 
	 * 
	 * \param o output stream of the generated code
	 */
	virtual void gen_asm(ostream &o);
 protected:
};


/**
 * \class CFGx86
 *  
 * \brief Class defining the control flow graph for x86
 */
class CFGx86 : public CFG {
 public:
 	/**
	 * \brief Construct a new CFGx86 object
	 * 
	 */
	CFGx86() {}

	/**
	 * \brief Create a jump instruction (x86) depending on the parameters
	 * Different cases :
	 *  - exit_true and exit_false are defined and equal : jump without condition to the label of exit_true
	 *  - exit_true is defined : jump with a condition 'not equal' to the label of exit_true
	 *  - exit_false is defined : jump with a condition 'equal' to the label of exit_false
	 * 
	 * \param exit_true Basicblock to reach
	 * \param exit_false Basicblock to reach
	 * \param o Output stream to write assembly code
	 */
	virtual void create_jumps(BasicBlock* exit_true,BasicBlock* exit_false,ostream &o);

	/**
	 * \brief Get the symbol table object
	 * 
	 * \return SymbolTable& 
	 */
	virtual SymbolTable& get_table();

	/**
	 * \brief  Create a jump instruction (x86) to the function's epilogue
	 * 
	 * \param o Output stream to write assembly code
	 */
	virtual void jump_to_epilogue(ostream &o);

	/**
	 * \brief Add instructions to the current block
	 * 
	 * \param op Operations to add
	 * \param params Parameters for operations
	 */
	virtual void add_IRInstr_to_current(IRInstr::Operation op, vector<string>& params);

	/**
	 * \brief Generation of the assembly code following instructions
	 * 
	 * \param o Output stream to write assembly code
	 */
	virtual void gen_asm(ostream& o);

	/**
	 * \brief Give the register depending on the value of reg
	 * 
	 * \param reg A temporary register or a variable in the symbol table or the register at the top of the stack represented by '!reg'
	 * \return string Represent the code assembly with the name of the register ('%eax' for '!reg' or more generally '-offset(%rbp)')
	 */
	virtual string IR_reg_to_asm(string reg);

	/**
	 * \brief Get the type of a register
	 * 
	 * It returns the type 'tint' if the symbol is not in the symbol table
	 * It returns the type of the symbol if the symbol is in the symbol table
	 * 
	 * \param reg A variable in the symbol table or another register
	 * \return VDescriptor::TYPE Type of the register
	 */
	virtual VDescriptor::TYPE get_type_reg(string reg);

	/**
	 * \brief Write the generic prologue of a function
	 * 
	 * \param o Output stream to write assembly code
	 */
	virtual void gen_asm_prologue(ostream& o);

	/**
	 * \brief Write the generic epilogue of a function
	 * 
	 * \param o Output stream to write assembly code
	 */
	virtual void gen_asm_epilogue(ostream& o);
 protected:
};

/**
 * \class CFGx86Factory
 *  
 * \brief Class defining the control flow graph factory for x86
 */
class CFGx86Factory : public CFGFactory {
 public:
	/**
	 * \brief Construct a new CFGx86Factory object
	 * 
	 */
	CFGx86Factory() {}
	
	/**
	 * \brief Creation of a new CFGx86
	 * 
	 * \return CFG* CFG created
	 */
	virtual CFG* create();

 protected:
};