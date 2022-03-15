#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"

#include "SymbolTable.h"
#include "VariableAnalyserVisitor.h"
#include "IRProducerVisitor.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv)
{
  stringstream in;
  if (argn==2)
  {
     ifstream lecture(argv[1]);
     in << lecture.rdbuf();
  }
  else
  {
      cerr << "usage: ifcc path/to/file.c" << endl ;
      exit(1);
  }
  
  ANTLRInputStream input(in.str());

  ifccLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();

  ifccParser parser(&tokens);
  tree::ParseTree* tree = parser.axiom();

  if(parser.getNumberOfSyntaxErrors() != 0)
  {
      cerr << "error: syntax error during parsing" << endl;
      exit(1);
  }

  SymbolTable sym;
  CFGx86 cfg(sym);

  VariableAnalyserVisitor vav(sym);
  vav.visit(tree);

  if (vav.getErrors()) {
      cerr << "error: syntax error during analyse" << endl;
      exit(1);
  }
  
  IRProducerVisitor ipv(sym, cfg);
  ipv.visit(tree);
  
  cfg.gen_asm(cout);
  cerr << " WARNINGS ";
  sym.variablesNotUsed();

  return 0;
}
