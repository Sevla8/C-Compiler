#include "IRProducerVisitor.h"

antlrcpp::Any IRProducerVisitor::visitProg(ifccParser::ProgContext *ctx)
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

antlrcpp::Any IRProducerVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
	if (ctx->expression()!=nullptr) {
		visit(ctx->expression());
		int offset = symbols.get(ctx->IDENTIFIER()->getText()).getOffset();
		std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	}
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitValue(ifccParser::ValueContext *ctx) {
	std::cout<<" 	movl $"<<ctx->CONST()->getText()<<", %eax\n";
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitVarvalue(ifccParser::VarvalueContext *ctx) {
	int offset = symbols.get(ctx->IDENTIFIER()->getText()).getOffset();
	std::cout<<" 	movl "<< -offset <<"(%rbp), %eax\n";
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio14(ifccParser::Prio14Context *ctx) {
	visit(ctx->expression());
	std::map<std::string, int>::iterator it;
	int offset = symbols.get(ctx->IDENTIFIER()->getText()).getOffset();
	if (ctx->EQ() != nullptr) {
		std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	}
	else if (ctx->B_PRIO_14() != nullptr) {
		std::string token(ctx->B_PRIO_14()->getText());
		if (token == "+=") {
			std::cout<<" 	addl %eax, "<< -offset <<"(%rbp)\n";
			}
		else if (token == "-=") {
			std::cout<<" 	subl %eax, "<< -offset <<"(%rbp)\n";
		}
	}

	return 0;
}


antlrcpp::Any IRProducerVisitor::visitPrio2(ifccParser::Prio2Context *ctx) {
	visit(ctx->expression());
	if (ctx->BU_PRIO_2_4()!=nullptr) {
		std::string token(ctx->BU_PRIO_2_4()->getText());
		if(token == "+"){
		}else if(token == "-"){
			std::cout<<"	negl	%eax\n";
		}
	} else {
		std::string token(ctx->U_PRIO_2()->getText());
		if(token == "~") {
			std::cout<<"	notl	%eax\n";
		}else if(token == "!") {
			std::cout<<" 	cmpl	$0, %eax\n";
			std::cout<<" 	sete	%al\n ";
			std::cout<<" 	movzbl	%al, %eax\n";
		}
	}
	return 0;
	
}

antlrcpp::Any IRProducerVisitor::visitPrio3(ifccParser::Prio3Context *ctx) {
	visit(ctx->expression(0));
	int offset = symbols.getTempVariable();
	std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_3()->getText());
	if (token=="*") {
		std::cout<<" 	imull "<< -offset <<"(%rbp), %eax\n";
	}else if (token=="/" || token=="%") {
		std::cout<<
				" 	movl "<< "%eax, %ebx\n"
				" 	movl "<< -offset <<"(%rbp), %eax\n"
				" 	cltd\n"
				" 	idivl %ebx\n";
		if (token=="%") {
			std::cout<<
				" 	movl "<< "%edx, %eax\n";
		}
	}
	return 0;
}
antlrcpp::Any IRProducerVisitor::visitPrio4(ifccParser::Prio4Context *ctx) {
	visit(ctx->expression(0));
	int offset = symbols.getTempVariable();
	std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->BU_PRIO_2_4()->getText());
	if (token=="+") {
		std::cout<<" 	addl "<< -offset <<"(%rbp), %eax\n";
	}else if (token=="-") {
		std::cout<<" 	subl %eax, "<< -offset <<"(%rbp)\n"
				" 	movl "<< -offset <<"(%rbp), %eax\n";
	}
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio8(ifccParser::Prio8Context *ctx){
	visit(ctx->expression(0));
	int offset = symbols.getTempVariable();
	std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_8()->getText());
	if(token=="&"){
		std::cout<<" 	andl "<<-offset <<"(%rbp), %eax\n"; 	
	}
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio9(ifccParser::Prio9Context *ctx){
	visit(ctx->expression(0));
	int offset = symbols.getTempVariable();
	std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_9()->getText());
	if(token=="^"){
		std::cout<<" 	xorl "<<-offset <<"(%rbp), %eax\n"; 	
	}
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio10(ifccParser::Prio10Context *ctx){
	visit(ctx->expression(0));
	int offset = symbols.getTempVariable();
	std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_10()->getText());
	if(token=="|"){
		std::cout<<" 	orl "<<-offset <<"(%rbp), %eax\n"; 	
	}
	return 0;
}


antlrcpp::Any IRProducerVisitor::visitPrio6(ifccParser::Prio6Context *ctx) {
	visit(ctx->expression(0));
	int offset = symbols.getTempVariable();
	std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_6()->getText());


	std::cout<<" cmpl	%eax,"<< -offset<<"(%rbp)\n";

		if (token=="<") std::cout<<" 	setl	%al\n ";
		if (token==">") std::cout<<" 	setg	%al\n ";
		if (token=="<=") std::cout<<" 	setle	%al\n ";
    	if (token==">=") std::cout<<" 	setge	%al\n ";
	std::cout<<"movzbl	%al, %eax\n";
	return 0;
}


antlrcpp::Any IRProducerVisitor::visitPrio7(ifccParser::Prio7Context *ctx) {
	visit(ctx->expression(0));
	int offset = symbols.getTempVariable();
	std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_7()->getText());


	std::cout<<" cmpl	%eax,"<< -offset<<"(%rbp)\n";

		if (token=="==") std::cout<<" 	sete	%al\n ";
		if (token=="!=") std::cout<<" 	setne	%al\n ";
	std::cout<<"movzbl	%al, %eax\n";
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio5(ifccParser::Prio5Context *ctx) {
	visit(ctx->expression(0));
	int offset = symbols.getTempVariable();
	std::cout<<" 	movl %eax, "<< -offset <<"(%rbp)\n";
	visit(ctx->expression(1));
	std::string token(ctx->B_PRIO_5()->getText());

	std::cout<<" 	movl	"<< -offset<<"(%rbp),%edx\n";
	std::cout<<" 	movl	%eax,%ecx\n";
	
	if (token=="<<") std::cout<<" 	sall	%cl,%edx\n";;
	if (token==">>") std::cout<<" 	sarl	%cl,%edx\n";;
	std::cout<<" movl	%edx,%eax\n";
	return 0;
}
int IRProducerVisitor::getErrors() {
	return errors;
}