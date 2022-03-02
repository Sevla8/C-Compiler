#include "CodeGenVisitor.h"

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	std::cout<<".globl	main\n"
		" main: \n"
		" 	pushq  %rbp\n"
		" 	movq   %rsp, %rbp\n";
	visitChildren(ctx);
	std::cout<<
		" 	popq   %rbp\n"
		" 	ret\n";

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
	std::map<std::string, int>::iterator it;
	int offset;
	if (ctx->expression()!=nullptr) {
		visit(ctx->expression());
	}
	if ((it = symbols.find(ctx->IDENTIFIER()->getText()))!=symbols.end()) {
		offset = it->second;
	} else {
		symbols.insert(make_pair(ctx->IDENTIFIER()->getText(), var_count));
		offset = var_count;
		++var_count;
	}
	if (ctx->expression()!=nullptr) {
		std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitValue(ifccParser::ValueContext *ctx) {
	std::cout<<" 	movl $"<<ctx->CONST()->getText()<<", %eax\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarvalue(ifccParser::VarvalueContext *ctx) {
	std::map<std::string, int>::iterator it;
	int offset;
	if ((it = symbols.find(ctx->IDENTIFIER()->getText()))!=symbols.end()) {
		offset = it->second;
	}
	std::cout<<" 	movl "<< (-4*(offset+1)) <<"(%rbp), %eax\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
	visit(ctx->expression());
	std::map<std::string, int>::iterator it;
	int offset;
	if ((it = symbols.find(ctx->IDENTIFIER()->getText()))!=symbols.end()) {
		offset = it->second;
	}
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	return 0;
}