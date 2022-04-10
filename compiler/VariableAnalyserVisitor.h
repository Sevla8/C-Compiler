#pragma once

/**
 * \file VariableAnalyserVisitor.h
 * \brief Visitor to carry out specific checks
 * \author H4224
 *
 */

//-------------------------------------------------------- Include system

#include "antlr4-runtime.h"
#include "SymbolTable.h"
#include "IR.h"
#include "generated/ifccBaseVisitor.h"
#include <map>
#include <string>

/**
 * \class VariableAnalyserVisitor
 *  
 * \brief Class carrying out specific checks for the declaration of variables
 */
class  VariableAnalyserVisitor : public ifccBaseVisitor {
public:

/**
   * \brief Construct a new VariableAnalyserVisitor object
   * 
   * \param cfg map that stores the cfg associated to each function
   * \param f factory that creates objects of type CFG
   */
  VariableAnalyserVisitor(map<string,CFG*>& cfg, CFGFactory* f) : cfgTable(cfg), factory(f) {}

 /**
	 * \brief create the cfg associated to the function, modifiy the arguments, visit the children nodes (arguments), specify the function and insert it into the cfg tables
	 */
  virtual antlrcpp::Any visitFunction(ifccParser::FunctionContext *ctx) override;

 /**
	 * \brief add the temporary variables to the symbol table
	 */
  virtual antlrcpp::Any visitFuncarg(ifccParser::FuncargContext *ctx) override;

 /**
	 * \brief check if the context was declared before use, or create it in the symbol table if it isn't already present. Call the visit of children nodes. 
	 */
  virtual antlrcpp::Any visitDeclstatement(ifccParser::DeclstatementContext *ctx) override;

 /**
	 * \brief check if the context was declared before use, or create it in the symbol table if it isn't already present
	 */
  virtual antlrcpp::Any visitVarvalue(ifccParser::VarvalueContext *ctx) override;

 /**
	 * \brief check if the context function was declared and call the visit of children nodes
	 */
  virtual antlrcpp::Any visitCall(ifccParser::CallContext *ctx) override;

 /**
	 * \brief check if the context has been declared and call the visit of children node
	 */
  virtual antlrcpp::Any visitPrio14(ifccParser::Prio14Context *ctx) override;

 /**
	 * \brief add the block to the symbol table, set it as current block and call the visit of children node
	 */
  virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;

 /**
	 * \brief get the type of the context and call the visit of children nodes
	 */
  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;

 /**
	 * \brief know if errors occured during the visit
	 * 
	 * \return errors
	 */
  int getErrors();

protected:
  map<string,CFG*>& cfgTable;
  CFG* cfg;
  CFGFactory* factory;
  SymbolTable* symbols;
  vector<pair<VDescriptor::TYPE, string>>* params;
  int errors = 0;
  string currentType;
};