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
		std::cerr<<"Variable "<<ctx->IDENTIFIER()->getText()<<"already declared here.\n";
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
	}else if (token=="/") {
		std::cout<<" 	idivl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n"
				" 	movl "<< (-4*(offset+1)) <<"(%rbp), %eax\n";
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

antlrcpp::Any CodeGenVisitor::visitPrio8(ifccParser::Prio8Context *ctx){
	visit(ctx->expression(0));
	int offset=var_count;
	++var_count;
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_8()->getText());
	if(token=="&"){
		std::cout<<" 	andl "<<(-4*(offset+1)) <<"(%rbp), %eax\n"; 	
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitPrio9(ifccParser::Prio9Context *ctx){
	visit(ctx->expression(0));
	int offset=var_count;
	++var_count;
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_9()->getText());
	if(token=="^"){
		std::cout<<" 	xorl "<<(-4*(offset+1)) <<"(%rbp), %eax\n"; 	
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitPrio10(ifccParser::Prio10Context *ctx){
	visit(ctx->expression(0));
	int offset=var_count;
	++var_count;
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_10()->getText());
	if(token=="|"){
		std::cout<<" 	orl "<<(-4*(offset+1)) <<"(%rbp), %eax\n"; 	
	}
	return 0;
}

int CodeGenVisitor::getErrors() {
	return errors;
}