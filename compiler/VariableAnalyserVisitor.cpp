#include "VariableAnalyserVisitor.h"

antlrcpp::Any VariableAnalyserVisitor::visitFunction(ifccParser::FunctionContext *ctx)
{
	cfg = factory->create();
	vector<pair<VDescriptor::TYPE, string>> p;
	vector<pair<VDescriptor::TYPE, string>>* previous = params;
	params = &p;
	symbols = &cfg->get_table();
	if (ctx->arguments()!=nullptr) {
		symbols->setCurrentBlock(1);
		visit(ctx->arguments());
		symbols->setCurrentBlock(0);
	}
	cfg->specify_function(getTypeFromString(ctx->type->getText()), ctx->IDENTIFIER()->getText(), p);
	cfgTable.insert(make_pair(ctx->IDENTIFIER()->getText(),cfg));
	params = previous;
	visit(ctx->block());
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitFuncarg(ifccParser::FuncargContext *ctx)
{
	symbols->add(ctx->IDENTIFIER()->getText(), ctx->type->getText());
	params->push_back(make_pair(getTypeFromString(ctx->type->getText()), ctx->IDENTIFIER()->getText()));
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {	
	currentType=ctx->type->getText();
	visitChildren(ctx);	
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitDeclstatement(ifccParser::DeclstatementContext *ctx) {
	if (ctx->expression()!=nullptr) {
		visit(ctx->expression());
	}	
	if (symbols->existCurrent(ctx->IDENTIFIER()->getText(),symbols->getCurrentBlock())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" already declared here.\n";
		errors += 1;
	} else {
		symbols->add(ctx->IDENTIFIER()->getText(), currentType);
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitVarvalue(ifccParser::VarvalueContext *ctx) {
	int res=symbols->exists(ctx->IDENTIFIER()->getText());
	if (res==-1) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}else{
		//cerr << ctx->IDENTIFIER()->getText();
		symbols->get(make_pair(ctx->IDENTIFIER()->getText(),res)).setUsed(true);
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
	int res=symbols->exists(ctx->IDENTIFIER()->getText());
	if (res==-1) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitBlock(ifccParser::BlockContext *ctx) {
	symbols->addBlock();
	visitChildren(ctx);
	symbols->setCurrentBlock(symbols->getBlockTree().at(symbols->getCurrentBlock()));
	
	return 0;
}

int VariableAnalyserVisitor::getErrors() {
	return errors;
}