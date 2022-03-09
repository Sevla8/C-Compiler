#pragma once


#include "antlr4-runtime.h"
#include "SymbolTable.h"
#include "generated/ifccBaseVisitor.h"
#include <map>
#include <string>

class  VariableAnalyserVisitor : public ifccBaseVisitor {
public:
  VariableAnalyserVisitor(SymbolTable& sym) : symbols(sym) {}

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;

  virtual antlrcpp::Any visitVarvalue(ifccParser::VarvalueContext *ctx) override;

  virtual antlrcpp::Any visitPrio14(ifccParser::Prio14Context *ctx) override;

  int getErrors();

protected:
  SymbolTable& symbols;
  int errors = 0;
};

