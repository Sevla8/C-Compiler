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
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" already declared here.\n";
		errors += 1;
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
	} else {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}
	std::cout<<" 	movl "<< (-4*(offset+1)) <<"(%rbp), %eax\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitPrio14(ifccParser::Prio14Context *ctx) {
	visit(ctx->expression());
	std::map<std::string, int>::iterator it;
	int offset;
	if ((it = symbols.find(ctx->IDENTIFIER()->getText()))!=symbols.end()) {
		offset = it->second;
	} else {
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<" not declared.\n";
		errors += 1;
	}
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	
	return 0;
}
antlrcpp::Any CodeGenVisitor::visitPrio3(ifccParser::Prio3Context *ctx) {
	visit(ctx->expression(0));
	int offset = var_count;
	++var_count;
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_3()->getText());
	if (token=="*") {
		std::cout<<" 	imull "<< (-4*(offset+1)) <<"(%rbp), %eax\n";
	}else if (token=="/" || token=="%") {
		std::cout<<
				" 	movl "<< "%eax, %ebx\n"
				" 	movl "<< (-4*(offset+1)) <<"(%rbp), %eax\n"
				" 	cltd\n"
				" 	idivl %ebx\n";
		if (token=="%") {
			std::cout<<
				" 	movl "<< "%edx, %eax\n";
		}
	}
	return 0;
}
antlrcpp::Any CodeGenVisitor::visitPrio4(ifccParser::Prio4Context *ctx) {
	visit(ctx->expression(0));
	int offset = var_count;
	++var_count;
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->BU_PRIO_2_4()->getText());
	if (token=="+") {
		std::cout<<" 	addl "<< (-4*(offset+1)) <<"(%rbp), %eax\n";
	}else if (token=="-") {
		std::cout<<" 	subl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n"
				" 	movl "<< (-4*(offset+1)) <<"(%rbp), %eax\n";
	}
	return 0;
}

int CodeGenVisitor::getErrors() {
	return errors;
}