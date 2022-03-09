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


antlrcpp::Any CodeGenVisitor::visitPrio2(ifccParser::Prio2Context *ctx) {
	visit(ctx->expression());
	std::string token(ctx->BU_PRIO_2_4()->getText());
	if(token == "+"){
	}else if(token == "-"){
		std::cout<<"	negl	%eax\n";
	}
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


antlrcpp::Any CodeGenVisitor::visitPrio6(ifccParser::Prio6Context *ctx) {
	visit(ctx->expression(0));
	int offset = var_count;
	++var_count;
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_6()->getText());


	std::cout<<" cmpl	%eax,"<< (-4*(offset+1))<<"(%rbp)\n";

		if (token=="<") std::cout<<" 	setl	%al\n ";
		if (token==">") std::cout<<" 	setg	%al\n ";
		if (token=="<=") std::cout<<" 	setle	%al\n ";
    	if (token==">=") std::cout<<" 	setge	%al\n ";
	std::cout<<"movzbl	%al, %eax\n";
	return 0;
}


antlrcpp::Any CodeGenVisitor::visitPrio7(ifccParser::Prio7Context *ctx) {
	visit(ctx->expression(0));
	int offset = var_count;
	++var_count;
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_7()->getText());


	std::cout<<" cmpl	%eax,"<< (-4*(offset+1))<<"(%rbp)\n";

		if (token=="==") std::cout<<" 	sete	%al\n ";
		if (token=="!=") std::cout<<" 	setne	%al\n ";
	std::cout<<"movzbl	%al, %eax\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitPrio5(ifccParser::Prio5Context *ctx) {
	visit(ctx->expression(0));
	int offset = var_count;
	++var_count;
	std::cout<<" 	movl %eax, "<< (-4*(offset+1)) <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_5()->getText());

	std::cout<<" 	movl	"<< (-4*(offset+1))<<"(%rbp),%edx\n";
	std::cout<<" 	movl	%eax,%ecx\n";
	
	if (token=="<<") std::cout<<" 	sall	%cl,%edx\n";;
	if (token==">>") std::cout<<" 	sarl	%cl,%edx\n";;
	std::cout<<" movl	%edx,%eax\n";
	return 0;
}
int CodeGenVisitor::getErrors() {
	return errors;
}