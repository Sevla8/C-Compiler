#include "VariableAnalyserVisitor.h"

antlrcpp::Any VariableAnalyserVisitor::visitDeclstatement(ifccParser::DeclstatementContext *ctx) {
	if (ctx->expression()!=nullptr) {
		visit(ctx->expression());
	}	
	if (symbols.exists(ctx->IDENTIFIER()->getText())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" already declared here.\n";
		errors += 1;
	} else {
		symbols.add(ctx->IDENTIFIER()->getText(), ctx->type->getText());
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitVarvalue(ifccParser::VarvalueContext *ctx) {
	if (!symbols.exists(ctx->IDENTIFIER()->getText())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}else{
		//cerr << ctx->IDENTIFIER()->getText();
		symbols.add(ctx->IDENTIFIER()->getText(),ctx->type->getText());
		symbols.get(ctx->IDENTIFIER()->getText()).setUsed(true);
	}  
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitPrio14(ifccParser::Prio14Context *ctx) {
	visit(ctx->expression());
	if (!symbols.exists(ctx->IDENTIFIER()->getText())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}
	return 0;
}


int VariableAnalyserVisitor::getErrors() {
	return errors;
}