#include "VariableAnalyserVisitor.h"

antlrcpp::Any VariableAnalyserVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
	if (symbols.exists(ctx->IDENTIFIER()->getText())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" already declared here.\n";
		errors += 1;
	} else {
		symbols.add(ctx->IDENTIFIER()->getText());
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitVarvalue(ifccParser::VarvalueContext *ctx) {
	if (!symbols.exists(ctx->IDENTIFIER()->getText())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitPrio14(ifccParser::Prio14Context *ctx) {
	if (!symbols.exists(ctx->IDENTIFIER()->getText())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}
	return 0;
}

int VariableAnalyserVisitor::getErrors() {
	return errors;
}