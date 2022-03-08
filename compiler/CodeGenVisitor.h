#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include <map>
#include <string>

class  CodeGenVisitor : public ifccBaseVisitor {
public:
  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;

  virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override;

  virtual antlrcpp::Any visitVarvalue(ifccParser::VarvalueContext *ctx) override;
  
  virtual antlrcpp::Any visitPrio3(ifccParser::Prio3Context *ctx) override;
  
  virtual antlrcpp::Any visitPrio4(ifccParser::Prio4Context *ctx) override;
  
  virtual antlrcpp::Any visitPrio14(ifccParser::Prio14Context *ctx) override;

  int getErrors();

protected:
  std::map<std::string, int> symbols;
  int var_count = 0;
  int errors = 0;
};

