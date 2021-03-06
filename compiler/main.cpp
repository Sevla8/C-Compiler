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
#include "IR.h"

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

  map<string,CFG*> functions;
  CFGx86Factory factory;

  DummyCFG putchar, getchar;
  vector<pair<VDescriptor::TYPE, string>> pcparams, gcparams;
  pcparams.push_back(make_pair(VDescriptor::TYPE::tint, "c"));
  putchar.specify_function(VDescriptor::TYPE::tint, "putchar@PLT", pcparams);
  getchar.specify_function(VDescriptor::TYPE::tint, "getchar@PLT", gcparams);
  functions.insert(make_pair("putchar", &putchar));
  functions.insert(make_pair("getchar", &getchar));

  VariableAnalyserVisitor vav(functions, &factory);
  vav.visit(tree);

  if (vav.getErrors()) {
      cerr << "error: during analyse" << endl;
      exit(1);
  }
  
  IRProducerVisitor ipv(functions);
  ipv.visit(tree);
  
  if (ipv.getErrors()) {
      cerr << "error: during assembly production" << endl;
      exit(1);
  }
  
  map<string, CFG*>::iterator p;

  for(p = functions.begin(); p != functions.end(); p++)
{
    p->second->gen_asm(cout);
    p->second->get_table().variablesNotUsed();
}

  return 0;
}
