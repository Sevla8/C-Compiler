#pragma once

/**
 * \file IRProducerVisitor.h
 * \brief Visitor to produce an intermediate representation
 * \author H4224
 *
 */

//-------------------------------------------------------- Include system
#include <string>
#include <vector>
using namespace std;

//-------------------------------------------------------- Include personnal
#include "antlr4-runtime.h"
#include "SymbolTable.h"
#include "generated/ifccBaseVisitor.h"
#include "IRx86.h"

/**
 * \class IRProducerVistor
 *  
 * \brief Class overriding vistors generated automatically by ANTLR
 */
class  IRProducerVisitor : public ifccBaseVisitor {
public:
  /**
   * \brief Construct a new IRProducerVisitor object
   * 
   * \param cfg 
   */
  IRProducerVisitor(map<string,CFG*>& cfg) : cfgTable(cfg) {}

  /**
   * \brief Visit the item function defined in the grammar
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitFunction(ifccParser::FunctionContext *ctx) override;
  
  /**
   * \brief Visit the item instruction defined in the grammar
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitInstruction(ifccParser::InstructionContext *ctx) override;

  /**
   * \brief Visit the item condition defined in the grammar
   * 
   * A condition is composed of an 'if' and optionnaly 'else if' or 'else'
   * To code a condition in assembly we have to switch block depending on the result of the 
   * condition
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitCondition(ifccParser::ConditionContext *ctx) override;

  /**
   * \brief Visit the item loop defined in the grammar
   * 
   * A loop is defined with a 'while'. To implement it we have to switch of block
   * depending of the expression for the loop.
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitLoop(ifccParser::LoopContext *ctx) override;

  /**
   * \brief Visit the item declstatement defined in the grammar
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitDeclstatement(ifccParser::DeclstatementContext *ctx) override;

  /**
   * \brief Visit the item value defined in the grammar
   * 
   * A value is defined as an integer
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override;

  /**
   * \brief Visit the item varValue defined in the grammar
   * 
   * A varValue is defined as an identifier of a variable
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */ 
  virtual antlrcpp::Any visitVarvalue(ifccParser::VarvalueContext *ctx) override;
  
  /**
   * \brief Visit the item char defined in the grammar
   * 
   * A char is defined as a character bewteen quotes, such as 'a'
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitChar(ifccParser::CharContext *ctx) override;

  /**
   * \brief Visit the item call defined in the grammar
   * 
   * A call is defined when in the code there is an utilisation of a method defined previously
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitCall(ifccParser::CallContext *ctx) override;
  
  /**
   * \brief Visit the item callArg defined in the grammar
   * 
   * A callArg is an argument in a function which is an expression
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitCallarg(ifccParser::CallargContext *ctx) override;

  /**
   * \brief Visit the item prio2 defined in the grammar
   * 
   * The prio2 corresponds to the operation unary 'NOT' and unary/binary '+', '-'
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio2(ifccParser::Prio2Context *ctx) override;

  /**
   * \brief Visit the item prio3 defined in the grammar
   * 
   * The prio3 corresponds to an arithmetic operation between 2 expressions 
   * such as : '*', '/' and '%' 
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio3(ifccParser::Prio3Context *ctx) override;
  
  /**
   * \brief Visit the item prio4 defined in the grammar
   * 
   * The prio4 corresponds to an arithmetic operation between 2 expressions 
   * such as : '+' and '-' 
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio4(ifccParser::Prio4Context *ctx) override;

  /**
   * \brief Visit the item prio5 defined in the grammar
   * 
   * The prio5 corresponds to the binary operation 'SHIFT' between 2 expressions
   * such as : '<<' and '>>'
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio5(ifccParser::Prio5Context *ctx) override;
  
  /**
   * \brief Visit the item prio6 defined in the grammar
   * 
   * The prio6 corresponds to comparison between 2 expressions
   * such as : '<', '>', '<=' and '>='
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio6(ifccParser::Prio6Context *ctx) override;

  /**
   * \brief Visit the item prio7 defined in the grammar
   * 
   * The prio7 correpsonds to an equality comparison between 2 expressions,
   * such as : '==' and '!=' 
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio7(ifccParser::Prio7Context *ctx) override;

  /**
   * \brief Visit the item prio14 defined in the grammar
   * 
   * The prio14 corresponds which link a variable identifier and an expression with operators
   * such as : '=', '-=', '+=', '*='...
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio14(ifccParser::Prio14Context *ctx) override;

  /**
   * \brief Visit the item prio8 defined in the grammar
   * 
   * The prio 8 corresponds to the binary operation 'AND' between 2 expressions
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio8(ifccParser::Prio8Context *ctx) override;
  
  /**
   * \brief Visit the item prio9 defined in the grammar
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio9(ifccParser::Prio9Context *ctx) override;

  /**
   * \brief Visit the item prio10 defined in the grammar
   * 
   * The prio10 corresponds to the binary operation 'OR' between 2 expressions
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio10(ifccParser::Prio10Context *ctx) override;

  /**
   * \brief Visit the item prio12 defined in the grammar
   * 
   * The prio12 corresponds to the logical 'OR' between 2 expressions,
   * such as : '||'
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio12(ifccParser::Prio12Context *ctx) override;

  /**
   * \brief Visit the item prio11 defined in the grammar
   * 
   * The prio12 corresponds to the logical 'AND' between 2 expressions,
   * such as : '&&'
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitPrio11(ifccParser::Prio11Context *ctx) override;

  /**
   * \brief Visit the item block defined in the grammar
   * 
   * A block corresponds to a portion in the program which is defined between '{ }'
   * 
   * \param ctx 
   * \return antlrcpp::Any 
   */
  virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;

  /**
   * \brief Return the number of errors 
   * 
   * \return int 
   */
  int getErrors();

protected:
  /**
   * \brief Ensures that we don't use a return of a void function
   * 
   * \return true 
   * \return false 
   */
  bool checkNoVoid();
  /** \brief Map to store all CFG */
  map<string,CFG*>& cfgTable;

  /** \brief Current CFG */
  CFG* cfg;
  
  /** \brief A table to store all symbols */
  SymbolTable* symbols;

  /** \brief Store differents parameters */
  vector<string>* params;

  /** \brief Count the number of errors */
  int errors = 0;

  /** \brief Count the number of block visited */
  int block_visited=0;
};

