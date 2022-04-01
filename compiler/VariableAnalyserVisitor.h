#pragma once


#include "antlr4-runtime.h"
#include "SymbolTable.h"
#include "IR.h"
#include "generated/ifccBaseVisitor.h"
#include <map>
#include <string>

class  VariableAnalyserVisitor : public ifccBaseVisitor {
public:
  VariableAnalyserVisitor(map<string,CFG*>& cfg, CFGFactory* f) : cfgTable(cfg), factory(f) {}

  virtual antlrcpp::Any visitFunction(ifccParser::FunctionContext *ctx) override;

  virtual antlrcpp::Any visitFuncarg(ifccParser::FuncargContext *ctx) override;

  virtual antlrcpp::Any visitDeclstatement(ifccParser::DeclstatementContext *ctx) override;

  virtual antlrcpp::Any visitVarvalue(ifccParser::VarvalueContext *ctx) override;

  virtual antlrcpp::Any visitCall(ifccParser::CallContext *ctx) override;

  virtual antlrcpp::Any visitPrio14(ifccParser::Prio14Context *ctx) override;

  int getErrors();

protected:
  map<string,CFG*>& cfgTable;
  CFG* cfg;
  CFGFactory* factory;
  SymbolTable* symbols;
  vector<string>* params;
  int errors = 0;
};

