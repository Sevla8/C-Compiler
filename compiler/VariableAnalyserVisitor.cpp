#include "VariableAnalyserVisitor.h"

antlrcpp::Any VariableAnalyserVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
	if (symbols.existCurrent(ctx->IDENTIFIER()->getText(),symbols.getCurrentBlock())) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" already declared here.\n";
		errors += 1;
	} else {
		symbols.add(ctx->IDENTIFIER()->getText());
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitVarvalue(ifccParser::VarvalueContext *ctx) {
	int res=symbols.exists(ctx->IDENTIFIER()->getText());
	if (res==-1) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitPrio14(ifccParser::Prio14Context *ctx) {
	int res=symbols.exists(ctx->IDENTIFIER()->getText());
	if (res==-1) {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}
	return 0;
}

antlrcpp::Any VariableAnalyserVisitor::visitBlock(ifccParser::BlockContext *ctx) {
	symbols.addBlock();
	visitChildren(ctx);
	symbols.setCurrentBlock(symbols.getBlockTree().at(symbols.getCurrentBlock()));

	return 0;
}

int VariableAnalyserVisitor::getErrors() {
	return errors;
}