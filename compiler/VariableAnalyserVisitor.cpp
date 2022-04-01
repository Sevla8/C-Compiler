#include "VariableAnalyserVisitor.h"

antlrcpp::Any VariableAnalyserVisitor::visitFunction(ifccParser::FunctionContext *ctx)
{
	cfg = factory->create();
	vector<string> p;
	vector<string>* previous = params;
	params = &p;
	symbols = &cfg->get_table();
	visitChildren(ctx);
	cfg->specify_function(ctx->IDENTIFIER()->getText(), p);
	cfgTable.insert(make_pair(ctx->IDENTIFIER()->getText(),cfg));
	params = previous;
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitFuncarg(ifccParser::FuncargContext *ctx)
{
	params->push_back(ctx->IDENTIFIER()->getText());
	symbols->add(ctx->IDENTIFIER()->getText());
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitDeclstatement(ifccParser::DeclstatementContext *ctx) {
	if (ctx->expression()!=nullptr) {
		visit(ctx->expression());
	}	
	if (symbols->exists(ctx->IDENTIFIER()->getText())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" already declared here.\n";
		errors += 1;
	} else {
		symbols->add(ctx->IDENTIFIER()->getText());
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitVarvalue(ifccParser::VarvalueContext *ctx) {
	if (!symbols->exists(ctx->IDENTIFIER()->getText())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}else{
		//cerr << ctx->IDENTIFIER()->getText();
		symbols->get(ctx->IDENTIFIER()->getText()).setUsed(true);
	}  
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitCall(ifccParser::CallContext *ctx) {
	visitChildren(ctx);
	if (cfgTable.find(ctx->IDENTIFIER()->getText())==cfgTable.end()) {
		std::cerr<<"Function "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitPrio14(ifccParser::Prio14Context *ctx) {
	visit(ctx->expression());
	if (!symbols->exists(ctx->IDENTIFIER()->getText())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}
	return 0;
}


int VariableAnalyserVisitor::getErrors() {
	return errors;
}