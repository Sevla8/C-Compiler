#include "IRProducerVisitor.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

antlrcpp::Any IRProducerVisitor::visitProg(ifccParser::ProgContext *ctx)
{
	cfg.create_bb();
	visitChildren(ctx);
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitDeclstatement(ifccParser::DeclstatementContext *ctx) {
	if (ctx->expression()!=nullptr) {
		visit(ctx->expression());
		vector<string> p;
		p.push_back(ctx->IDENTIFIER()->getText());
		p.push_back("!reg");
		cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	}
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitValue(ifccParser::ValueContext *ctx) {
	vector<string> p;
	p.push_back("!reg");
	p.push_back(ctx->CONST()->getText());
	cfg.add_IRInstr_to_current(IRInstr::Operation::ldconst,p);
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitVarvalue(ifccParser::VarvalueContext *ctx) {
	vector<string> p;
	p.push_back("!reg");
	p.push_back(ctx->IDENTIFIER()->getText());
	cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio14(ifccParser::Prio14Context *ctx) {
	visit(ctx->expression());
	vector<string> p, q;
	if (ctx->EQ() != nullptr) {
		p.push_back(ctx->IDENTIFIER()->getText());
		p.push_back("!reg");
		cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	}
	else if (ctx->B_PRIO_14() != nullptr) {
		std::string token(ctx->B_PRIO_14()->getText());
		if (token == "+=") {
			p.push_back(ctx->IDENTIFIER()->getText());
			p.push_back(ctx->IDENTIFIER()->getText());
			p.push_back("!reg");
			cfg.add_IRInstr_to_current(IRInstr::Operation::add,p);
		}
		else if (token == "-=") {
			p.push_back(ctx->IDENTIFIER()->getText());
			p.push_back(ctx->IDENTIFIER()->getText());
			p.push_back("!reg");
			cfg.add_IRInstr_to_current(IRInstr::Operation::sub,p);
		}
		q.push_back("!reg");
		q.push_back(ctx->IDENTIFIER()->getText());
		cfg.add_IRInstr_to_current(IRInstr::Operation::copy,q);
	}

	return 0;
}


antlrcpp::Any IRProducerVisitor::visitPrio2(ifccParser::Prio2Context *ctx) {
	visit(ctx->expression());
	vector<string> p;
	p.push_back("!reg");
	p.push_back("!reg");
	if (ctx->BU_PRIO_2_4()!=nullptr) {
		std::string token(ctx->BU_PRIO_2_4()->getText());
		if(token == "+"){
		}else if(token == "-"){
			cfg.add_IRInstr_to_current(IRInstr::Operation::neg,p);
		}
	} else {
		std::string token(ctx->U_PRIO_2()->getText());
		if(token == "~") {
			cfg.add_IRInstr_to_current(IRInstr::Operation::lnot,p);
		}else if(token == "!") {
			cfg.add_IRInstr_to_current(IRInstr::Operation::cnot,p);
		}
	}
	return 0;
	
}

antlrcpp::Any IRProducerVisitor::visitPrio3(ifccParser::Prio3Context *ctx) {
	visit(ctx->expression(0));
	vector<string> p, q;
	string tmp = symbols.getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	std::string token(ctx->B_PRIO_3()->getText());
	if (token=="*") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::mul,q);
	}else if (token=="/") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::div,q);
	}else if (token=="%") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::mod,q);
	}
	return 0;
}
antlrcpp::Any IRProducerVisitor::visitPrio4(ifccParser::Prio4Context *ctx) {
	visit(ctx->expression(0));
	vector<string> p, q;
	string tmp = symbols.getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	std::string token(ctx->BU_PRIO_2_4()->getText());
	if (token=="+") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::add,q);
	}else if (token=="-") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::sub,q);
	}
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio8(ifccParser::Prio8Context *ctx){
	visit(ctx->expression(0));
	vector<string> p, q;
	string tmp = symbols.getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	std::string token(ctx->B_PRIO_8()->getText());
	if(token=="&"){
		cfg.add_IRInstr_to_current(IRInstr::Operation::land,q);
	}
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio9(ifccParser::Prio9Context *ctx){
	visit(ctx->expression(0));
	vector<string> p, q;
	string tmp = symbols.getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	std::string token(ctx->B_PRIO_9()->getText());
	if(token=="^"){
		cfg.add_IRInstr_to_current(IRInstr::Operation::lxor,q);
	}
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio10(ifccParser::Prio10Context *ctx){
	visit(ctx->expression(0));
	vector<string> p, q;
	string tmp = symbols.getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	std::string token(ctx->B_PRIO_10()->getText());
	if(token=="|"){
		cfg.add_IRInstr_to_current(IRInstr::Operation::lor,q);
	}
	return 0;
}


antlrcpp::Any IRProducerVisitor::visitPrio6(ifccParser::Prio6Context *ctx) {
	visit(ctx->expression(0));
	vector<string> p, q;
	string tmp = symbols.getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	std::string token(ctx->B_PRIO_6()->getText());
	if (token=="<") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::cmp_lt,q);
	}
	if (token==">") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::cmp_gt,q);
	}
	if (token=="<=") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::cmp_le,q);
	}
	if (token==">=") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::cmp_ge,q);
	}
	return 0;
}


antlrcpp::Any IRProducerVisitor::visitPrio7(ifccParser::Prio7Context *ctx) {
	visit(ctx->expression(0));
	vector<string> p, q;
	string tmp = symbols.getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	std::string token(ctx->B_PRIO_7()->getText());
	if (token=="!=") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::cmp_ne,q);
	}
	if (token=="==") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::cmp_eq,q);
	}
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitPrio5(ifccParser::Prio5Context *ctx) {
	visit(ctx->expression(0));
	vector<string> p, q;
	string tmp = symbols.getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg.add_IRInstr_to_current(IRInstr::Operation::copy,p);
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	std::string token(ctx->B_PRIO_5()->getText());
	
	if (token=="<<") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::lsl,q);
	}
	if (token==">>") {
		cfg.add_IRInstr_to_current(IRInstr::Operation::lsr,q);
	}
	return 0;
}
int IRProducerVisitor::getErrors() {
	return errors;
}