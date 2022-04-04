#pragma once


#include "antlr4-runtime.h"
#include "SymbolTable.h"
#include "generated/ifccBaseVisitor.h"
#include "IRx86.h"
#include <string>
#include <vector>

using namespace std;

class  IRProducerVisitor : public ifccBaseVisitor {
public:
  IRProducerVisitor(map<string,CFG*>& cfg) : cfgTable(cfg) {}

  virtual antlrcpp::Any visitFunction(ifccParser::FunctionContext *ctx) override;
  
  virtual antlrcpp::Any visitInstruction(ifccParser::InstructionContext *ctx) override;

  virtual antlrcpp::Any visitCondition(ifccParser::ConditionContext *ctx) override;

  virtual antlrcpp::Any visitLoop(ifccParser::LoopContext *ctx) override;

  virtual antlrcpp::Any visitDeclstatement(ifccParser::DeclstatementContext *ctx) override;

  virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override;

  virtual antlrcpp::Any visitVarvalue(ifccParser::VarvalueContext *ctx) override;
  
  virtual antlrcpp::Any visitCall(ifccParser::CallContext *ctx) override;
  
  virtual antlrcpp::Any visitCallarg(ifccParser::CallargContext *ctx) override;

  virtual antlrcpp::Any visitPrio2(ifccParser::Prio2Context *ctx) override;

  virtual antlrcpp::Any visitPrio3(ifccParser::Prio3Context *ctx) override;
  
  virtual antlrcpp::Any visitPrio4(ifccParser::Prio4Context *ctx) override;

  virtual antlrcpp::Any visitPrio5(ifccParser::Prio5Context *ctx) override;
  
  virtual antlrcpp::Any visitPrio6(ifccParser::Prio6Context *ctx) override;

  virtual antlrcpp::Any visitPrio7(ifccParser::Prio7Context *ctx) override;

  virtual antlrcpp::Any visitPrio14(ifccParser::Prio14Context *ctx) override;

  virtual antlrcpp::Any visitPrio8(ifccParser::Prio8Context *ctx) override;
  
  virtual antlrcpp::Any visitPrio9(ifccParser::Prio9Context *ctx) override;

  virtual antlrcpp::Any visitPrio10(ifccParser::Prio10Context *ctx) override;

  virtual antlrcpp::Any visitPrio12(ifccParser::Prio12Context *ctx) override;

  virtual antlrcpp::Any visitPrio11(ifccParser::Prio11Context *ctx) override;

  virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;

  int getErrors();

protected:
  map<string,CFG*>& cfgTable;
  CFG* cfg;
  SymbolTable* symbols;
  vector<string>* params;
  int errors = 0;
  int block_visited=0;
};

