#include "IRProducerVisitor.h"

using namespace std;

antlrcpp::Any IRProducerVisitor::visitProg(ifccParser::ProgContext *ctx)
{
	BasicBlock* first_bb=cfg.create_bb();
	cfg.add_bb(first_bb);

	cfg.set_current_bb(first_bb);
	visitChildren(ctx);
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitBlock(ifccParser::BlockContext *ctx) {
	int previous_block=block_visited;
	block_visited++;
	symbols.setCurrentBlock(block_visited);
	visitChildren(ctx);
	symbols.setCurrentBlock(previous_block);
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitCondition(ifccParser::ConditionContext *ctx)
{
	BasicBlock* bb_then=cfg.create_bb();
	BasicBlock* bb_else=cfg.create_bb();
	BasicBlock* bb_endif=cfg.create_bb();

	BasicBlock* cur_bb=cfg.get_current_bb();
	
	bb_then->exit_true=bb_endif;
	bb_then->exit_false=bb_endif;

	bb_else->exit_true=bb_endif;
	bb_else->exit_false=bb_endif;
	
	bb_endif->exit_true=cur_bb->exit_true;
	bb_endif->exit_false=cur_bb->exit_false;

	cur_bb->exit_true=bb_then;
	cur_bb->exit_false=bb_else;

	if(ctx->expression()!=nullptr){
		visit(ctx->expression());

		vector<string> p;
		p.push_back("!reg");
		cfg.add_IRInstr_to_current(IRInstr::Operation::cmp_z,p);

		cfg.add_bb(bb_then);	
		cfg.set_current_bb(bb_then);
		visit(ctx->branch(0));
		
		cfg.add_bb(bb_else);
		
		if(ctx->branch(1)!=nullptr){	
			cfg.set_current_bb(bb_else);
			visit(ctx->branch(1));
		}
	}

	cfg.add_bb(bb_endif);
	cfg.set_current_bb(bb_endif);
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitLoop(ifccParser::LoopContext *ctx)
{
	BasicBlock* bb_check=cfg.create_bb();
	BasicBlock* bb_body=cfg.create_bb();
	BasicBlock* bb_endwhile=cfg.create_bb();

	BasicBlock* cur_bb=cfg.get_current_bb();
	
	bb_check->exit_true=bb_body;
	bb_check->exit_false=bb_endwhile;

	bb_body->exit_true=bb_check;
	bb_body->exit_false=bb_check;
	
	bb_endwhile->exit_true=cur_bb->exit_true;
	bb_endwhile->exit_false=cur_bb->exit_false;

	cur_bb->exit_true=bb_check;
	cur_bb->exit_false=bb_check;

	if(ctx->expression()!=nullptr){
		cfg.set_current_bb(bb_check);
		cfg.add_bb(bb_check);
		visit(ctx->expression());

		vector<string> p;
		p.push_back("!reg");
		cfg.add_IRInstr_to_current(IRInstr::Operation::cmp_z,p);

		cfg.add_bb(bb_body);	
		cfg.set_current_bb(bb_body);
		visit(ctx->branch());
	}

	cfg.add_bb(bb_endwhile);
	cfg.set_current_bb(bb_endwhile);
	return 0;
}

antlrcpp::Any IRProducerVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
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
	std::string token(ctx->BU_PRIO_2_4()->getText());
	vector<string> p;
	if(token == "+"){
	}else if(token == "-"){
		p.push_back("!reg");
		p.push_back("!reg");
		cfg.add_IRInstr_to_current(IRInstr::Operation::neg,p);
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