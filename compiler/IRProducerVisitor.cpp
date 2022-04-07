/*************************************************************************
                                IRProducerVisitor
    copyright            : (C) 2022 par H4224
    participants         : ALGOURDIN Benoit, ALVES Brandon, BELIAZI Léna,
						   BEYE Sellem, BROYER Maya, de LAMBERTYE Grégoire,
						   SERRANIA Tyefen, ZOUID Moustapha
*************************************************************************/

#include "IRProducerVisitor.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

/**
 * Visit the item function defined in the grammar
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitFunction(ifccParser::FunctionContext *ctx)
{
	// Set the number of block to 0
	block_visited = 0;
	// Find the CFG and the symbol table corresponding to the function
	cfg = cfgTable.find(ctx->IDENTIFIER()->getText())->second;
	symbols = &cfg->get_table();
	// Creation of the first basic block to write instructions
	BasicBlock* first_bb=cfg->create_bb();
	cfg->add_bb(first_bb);

	cfg->set_current_bb(first_bb);
	visitChildren(ctx);
	return 0;
}

/**
 * Visit the item block defined in the grammar
 * 
 * A block corresponds to a portion in the program which is defined between '{ }'
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitBlock(ifccParser::BlockContext *ctx) {
	// Memorize the number of the previous block visited
	int previous_block=block_visited;
	// Increase the number of block visited
	block_visited++;
	// Change the number of the current block and visit all children of this block
	symbols->setCurrentBlock(block_visited);
	visitChildren(ctx);
	// Retrieve the previous number of the block 
	symbols->setCurrentBlock(previous_block);
	return 0;
}

/**
 * Visit the item instruction defined in the grammar
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitInstruction(ifccParser::InstructionContext *ctx) {
	visitChildren(ctx);
	// Treat the special case of an instruction return which could be anywhere
	if (ctx->RETURN() != nullptr) {
		vector<string> p;
		cfg->add_IRInstr_to_current(IRInstr::Operation::ret,p);
	}
	return 0;
}

/**
 * Visit the item condition defined in the grammar
 * 
 * A condition is composed of an 'if' and optionnaly 'else if' or 'else'
 * To code a condition in assembly we have to switch block depending on the result of the 
 * condition
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitCondition(ifccParser::ConditionContext *ctx)
{
	// Creation of the 3 new basic blocks corresponding to the step of the condition
	BasicBlock* bb_then=cfg->create_bb();
	BasicBlock* bb_else=cfg->create_bb();
	BasicBlock* bb_endif=cfg->create_bb();

	BasicBlock* cur_bb=cfg->get_current_bb();
	// Define the next block to reach following the result of the condition test
	bb_then->exit_true=bb_endif;
	bb_then->exit_false=bb_endif;

	bb_else->exit_true=bb_endif;
	bb_else->exit_false=bb_endif;
	
	bb_endif->exit_true=cur_bb->exit_true;
	bb_endif->exit_false=cur_bb->exit_false;

	cur_bb->exit_true=bb_then;
	cur_bb->exit_false=bb_else;

	if(ctx->expression()!=nullptr){
		// Visit the expression corresponding to the condition in the 'if'
		visit(ctx->expression());
		// Add the instruction to check the result
		vector<string> p;
		p.push_back("!reg");
		cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_z,p);
		// Add the basic block 'then' and set it as the current
		cfg->add_bb(bb_then);	
		cfg->set_current_bb(bb_then);
		// Visit children which constitue the program after the if
		visit(ctx->branch(0));
		
		// Add the basic block 'else'
		cfg->add_bb(bb_else);
		
		if(ctx->branch(1)!=nullptr){	
			// Set the basic block as current
			cfg->set_current_bb(bb_else);
			// Visit the code written under the else
			visit(ctx->branch(1));
		}
	}
	// Add the last block 'endif' and set it as the current. It's the block where 
	// the rest of the program will be written
	cfg->add_bb(bb_endif);
	cfg->set_current_bb(bb_endif);
	return 0;
}

/**
 * Visit the item loop defined in the grammar
 * 
 * A loop is defined with a 'while'. To implement it we have to switch of block
 * depending of the expression for the loop.
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitLoop(ifccParser::LoopContext *ctx)
{
	// Creation of 3 new basic blocks
	BasicBlock* bb_check=cfg->create_bb();
	BasicBlock* bb_body=cfg->create_bb();
	BasicBlock* bb_endwhile=cfg->create_bb();

	BasicBlock* cur_bb=cfg->get_current_bb();
	// Define the next block to reach following the result of the condition test
	bb_check->exit_true=bb_body;
	bb_check->exit_false=bb_endwhile;

	bb_body->exit_true=bb_check;
	bb_body->exit_false=bb_check;
	
	bb_endwhile->exit_true=cur_bb->exit_true;
	bb_endwhile->exit_false=cur_bb->exit_false;

	cur_bb->exit_true=bb_check;
	cur_bb->exit_false=bb_check;

	if(ctx->expression()!=nullptr){
		// Set as current and add the bb_check to the CFG
		cfg->set_current_bb(bb_check);
		cfg->add_bb(bb_check);
		// Visit the expression corresponding to the condition of the loop
		visit(ctx->expression());
		// Add instructions to check the result of the test
		vector<string> p;
		p.push_back("!reg");
		cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_z,p);
		// Add and set as current the bb_body to the CFG
		cfg->add_bb(bb_body);	
		cfg->set_current_bb(bb_body);
		// Visit the code in the body of the loop
		visit(ctx->branch());
	}
	// Add and set as current the bb_endwhile to the CFG
	cfg->add_bb(bb_endwhile);
	cfg->set_current_bb(bb_endwhile);
	return 0;
}

/**
 * Visit the item declstatement defined in the grammar
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitDeclstatement(ifccParser::DeclstatementContext *ctx) {
	if (ctx->expression()!=nullptr) {
		// Visit the expression associated to an identifier
		visit(ctx->expression());
		// Add instructions to copy the value in the good variable
		vector<string> p;
		p.push_back(ctx->IDENTIFIER()->getText());
		p.push_back("!reg");
		cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	}
	return 0;
}

/**
 * Visit the item value defined in the grammar
 * 
 * A value is defined as an integer
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitValue(ifccParser::ValueContext *ctx) {
	// Add instructions to the CFG
	vector<string> p;
	p.push_back("!reg");
	p.push_back(ctx->CONST()->getText());
	cfg->add_IRInstr_to_current(IRInstr::Operation::ldconst,p);
	return 0;
}

/**
 * Visit the item varValue defined in the grammar
 * 
 * A varValue is defined as an identifier of a variable
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitVarvalue(ifccParser::VarvalueContext *ctx) {
	// Add instructions to the CFG
	vector<string> p;
	p.push_back("!reg");
	p.push_back(ctx->IDENTIFIER()->getText());
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	return 0;
}

/**
 * Visit the item char defined in the grammar
 * 
 * A char is defined as a character bewteen quotes, such as 'a'
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitChar(ifccParser::CharContext *ctx) {
	// Add instructions to the CFG 
    vector<string> p;
    p.push_back("!reg");
	// Get the representation of a char as an integer, its ASCII code
    int temp = (int) ctx->CHAR()->getText()[1]; 
    p.push_back(to_string(temp));
    cfg->add_IRInstr_to_current(IRInstr::Operation::ldconst,p);
    return 0;
} 

/**
 * Visit the item call defined in the grammar
 * 
 * A call is defined when in the code there is an utilisation of a method defined previously
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitCall(ifccParser::CallContext *ctx) {
	// Get the CFG corresponding to the function called
	CFG* func = cfgTable.find(ctx->IDENTIFIER()->getText())->second;
	vector<string> p;
	p.push_back(func->get_name());
	// Get parameters of the function
	vector<string>* previous = params;
	params = &p;
	visitChildren(ctx);
	// Check of the number of parameters defined in the call which could be superior but not inferior
	// to the number of parameters defined in the declaration of the function
	if (p.size()<func->get_params().size()+1) {
		cerr << "Functions don't have the same number of parameters" << endl;
		errors += 1;
	}
	// Add instructions to call the function with parameters
	cfg->add_IRInstr_to_current(IRInstr::Operation::call,p);
	params = previous;
	return 0;
}

/**
 * Visit the item callArg defined in the grammar
 * 
 * A callArg is an argument in a function which is an expression
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitCallarg(ifccParser::CallargContext *ctx) {
	// Visit of all children
	visitChildren(ctx);
	// Add instructions to the CFG
	string tmp = symbols->getTempVariable();
	vector<string> p;
	p.push_back(tmp);
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	params->push_back(tmp);
	return 0;
}

/**
 * Visit the item prio14 defined in the grammar
 * 
 * The prio14 corresponds which link a variable identifier and an expression with operators
 * such as : '=', '-=', '+=', '*='...
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio14(ifccParser::Prio14Context *ctx) {
	// Visit the expression and store the result at the top of the stack 
	visit(ctx->expression());
	vector<string> p, q;
	// If the operator is an '='
	if (ctx->EQ() != nullptr) {
		// Add instructions to copy the expression previsouly visited in a variable
		p.push_back(ctx->IDENTIFIER()->getText());
		p.push_back("!reg");
		cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	}
	else if (ctx->B_PRIO_14() != nullptr) {
		// Depending on the token of the operation
		string token(ctx->B_PRIO_14()->getText());
		// Add instructions to the CFG to add, substract... the expression to a variable identified
		if (token == "+=") {
			p.push_back(ctx->IDENTIFIER()->getText());
			p.push_back(ctx->IDENTIFIER()->getText());
			p.push_back("!reg");
			cfg->add_IRInstr_to_current(IRInstr::Operation::add,p);
		}
		else if (token == "-=") {
			p.push_back(ctx->IDENTIFIER()->getText());
			p.push_back(ctx->IDENTIFIER()->getText());
			p.push_back("!reg");
			cfg->add_IRInstr_to_current(IRInstr::Operation::sub,p);
		}
		q.push_back("!reg");
		q.push_back(ctx->IDENTIFIER()->getText());
		cfg->add_IRInstr_to_current(IRInstr::Operation::copy,q);
	}

	return 0;
}

/**
 * Visit the item prio2 defined in the grammar
 * 
 * The prio2 corresponds to the operation unary 'NOT' and unary/binary '+', '-'
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio2(ifccParser::Prio2Context *ctx) {
	// Visit the expression and store the result at the top of the stack
	visit(ctx->expression());
	vector<string> p;

	p.push_back("!reg");
	p.push_back("!reg");
	// Identification of the operation '+', '-'
	if (ctx->BU_PRIO_2_4()!=nullptr) {
		// Identification more precisely of the operation
		string token(ctx->BU_PRIO_2_4()->getText());
		// Add instructions to the CFG following the case
		if(token == "+"){
		}else if(token == "-"){
			cfg->add_IRInstr_to_current(IRInstr::Operation::neg,p);
		}
	// Identification of the operation '!', '~'
	} else {
		// Identification more precisely of the operation
		string token(ctx->U_PRIO_2()->getText());
		// Add instructions to the CFG following the case
		if(token == "~") {
			cfg->add_IRInstr_to_current(IRInstr::Operation::lnot,p);
		}else if(token == "!") {
			cfg->add_IRInstr_to_current(IRInstr::Operation::cnot,p);
		}
	}
	return 0;
	
}

/**
 * Visit the item prio3 defined in the grammar
 * 
 * The prio3 corresponds to an arithmetic operation between 2 expressions 
 * such as : '*', '/' and '%' 
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio3(ifccParser::Prio3Context *ctx) {
	// Visit the first expression and store the result at the top of the stack
	visit(ctx->expression(0));
	// Add instructions to copy this result in a temporary register
	vector<string> p, q;
	string tmp = symbols->getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	// Visit the second expression and store the result at the top of the stack
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	// Identification of the operation
	string token(ctx->B_PRIO_3()->getText());
	// Add instructions to the CFG to compute the operation between the 2 expressions
	if (token=="*") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::mul,q);
	}else if (token=="/") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::div,q);
	}else if (token=="%") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::mod,q);
	}
	return 0;
}

/**
 * Visit the item prio4 defined in the grammar
 * 
 * The prio4 corresponds to an arithmetic operation between 2 expressions 
 * such as : '+' and '-' 
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio4(ifccParser::Prio4Context *ctx) {
	// Visit the first expression and store the result at the top of the stack
	visit(ctx->expression(0));
	// Add instructions to copy this result in a temporary register
	vector<string> p, q;
	string tmp = symbols->getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	// Visit the second expression and store the result at the top of the stack
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	// Identification of the operation
	string token(ctx->BU_PRIO_2_4()->getText());
	// Add instructions to the CFG to compute the operation between the 2 expressions
	if (token=="+") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::add,q);
	}else if (token=="-") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::sub,q);
	}
	return 0;
}

/**
 * Visit the item prio8 defined in the grammar
 * 
 * The prio 8 corresponds to the binary operation 'AND' between 2 expressions
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio8(ifccParser::Prio8Context *ctx){
	// Visit the first expression and store the result at the top of the stack
	visit(ctx->expression(0));
	// Add instructions to copy this result in a temporary register
	vector<string> p, q;
	string tmp = symbols->getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	// Visit the second expression and store the result at the top of the stack
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	// Identification of the operator
	string token(ctx->B_PRIO_8()->getText());
	// Add instructions to the CFG to compute the operation between the 2 expressions
	if(token=="&"){
		cfg->add_IRInstr_to_current(IRInstr::Operation::land,q);
	}
	return 0;
}

/**
 * Visit the item prio9 defined in the grammar
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio9(ifccParser::Prio9Context *ctx){
	// Visit the first expression and store the result at the top of the stack
	visit(ctx->expression(0));
	// Add instructions to copy this result in a temporary register
	vector<string> p, q;
	string tmp = symbols->getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	// Visit the second expression and store the result at the top of the stack
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	// Identification of the operator
	string token(ctx->B_PRIO_9()->getText());
	// Add instructions to the CFG to compute the operation between the 2 expressions
	if(token=="^"){
		cfg->add_IRInstr_to_current(IRInstr::Operation::lxor,q);
	}
	return 0;
}

/**
 * Visit the item prio10 defined in the grammar
 * 
 * The prio10 corresponds to the binary operation 'OR' between 2 expressions
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio10(ifccParser::Prio10Context *ctx){
	// Visit the first expression and store the result at the top of the stack
	visit(ctx->expression(0));
	// Add instructions to copy this result in a temporary register
	vector<string> p, q;
	string tmp = symbols->getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	// Visit the second expression and store the result at the top of the stack
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	// Identification of the operator
	string token(ctx->B_PRIO_10()->getText());
	// Add instructions to the CFG to compute the operation between the 2 expressions
	if(token=="|"){
		cfg->add_IRInstr_to_current(IRInstr::Operation::lor,q);
	}
	return 0;
}

/**
 * Visit the item prio6 defined in the grammar
 * 
 * The prio6 corresponds to comparison between 2 expressions
 * such as : '<', '>', '<=' and '>='
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio6(ifccParser::Prio6Context *ctx) {
	// Visit the first expression and store the result at the top of the stack
	visit(ctx->expression(0));
	// Add instructions to copy this result in a temporary register
	vector<string> p, q;
	string tmp = symbols->getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	// Visit the second expression and store the result at the top of the stack
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	// Identification of the operator
	string token(ctx->B_PRIO_6()->getText());
	// Add instructions to the CFG to compute the comparison between the 2 expressions
	if (token=="<") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_lt,q);
	}
	if (token==">") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_gt,q);
	}
	if (token=="<=") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_le,q);
	}
	if (token==">=") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_ge,q);
	}
	return 0;
}

/**
 * Visit the item prio7 defined in the grammar
 * 
 * The prio7 correpsonds to an equality comparison between 2 expressions,
 * such as : '==' and '!=' 
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio7(ifccParser::Prio7Context *ctx) {
	// Visit the first expression and store the result at the top of the stack
	visit(ctx->expression(0));
	// Add instructions to copy this result in a temporary register
	vector<string> p, q;
	string tmp = symbols->getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	// Visit the second expression and store the result at the top of the stack
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	// Identification of the operator
	string token(ctx->B_PRIO_7()->getText());
	// Add instructions to the CFG to compute the comparison between the 2 expressions
	if (token=="!=") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_ne,q);
	}
	if (token=="==") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_eq,q);
	}
	return 0;
}

/**
 * Visit the item prio5 defined in the grammar
 * 
 * The prio5 corresponds to the binary operation 'SHIFT' between 2 expressions
 * such as : '<<' and '>>'
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio5(ifccParser::Prio5Context *ctx) {
	// Visit the first expression and store the result at the top of the stack
	visit(ctx->expression(0));
	// Add instructions to copy this result in a temporary register
	vector<string> p, q;
	string tmp = symbols->getTempVariable();
	p.push_back(tmp);
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::copy,p);
	// Visit the second expression and store the result at the top of the stack
	visit(ctx->expression(1));
	q.push_back("!reg");
	q.push_back(tmp);
	q.push_back("!reg");
	// Identification of the operator
	string token(ctx->B_PRIO_5()->getText());
	// Add instructions to the CFG to compute the operation between the 2 expressions
	if (token=="<<") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::lsl,q);
	}
	if (token==">>") {
		cfg->add_IRInstr_to_current(IRInstr::Operation::lsr,q);
	}
	return 0;
}

/**
 * Visit the item prio12 defined in the grammar
 * 
 * The prio12 corresponds to the logical 'OR' between 2 expressions,
 * such as : '||'
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio12(ifccParser::Prio12Context *ctx) {
	//create 2 block :  second_member_bb , end_test_bb
	BasicBlock* bb_second_member=cfg->create_bb();
	BasicBlock* bb_end_ou_paresseux=cfg->create_bb();
	BasicBlock* cur_bb=cfg->get_current_bb();
	bb_second_member->exit_true=bb_end_ou_paresseux;
	bb_second_member->exit_false=bb_end_ou_paresseux;
	
	bb_end_ou_paresseux->exit_true=cur_bb->exit_true;
	bb_end_ou_paresseux->exit_false=cur_bb->exit_false;

	cur_bb->exit_false=bb_second_member;
	cur_bb->exit_true=bb_end_ou_paresseux;
	visit(ctx->expression(0));
	vector<string> p;
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_z,p);
	
	cfg->add_bb(bb_second_member);	
	cfg->set_current_bb(bb_second_member);
	visit(ctx->expression(1));

	//mais on a pas defini qu'est ce qui se passe dans le bloc bb_end_ou_paresseux
	cfg->add_bb(bb_end_ou_paresseux);
	cfg->set_current_bb(bb_end_ou_paresseux);
	cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_zs,p);


	return 0;
}

/**
 * Visit the item prio11 defined in the grammar
 * 
 * The prio12 corresponds to the logical 'AND' between 2 expressions,
 * such as : '&&'
 * 
 * @param ctx 
 * @return antlrcpp::Any 
 */
antlrcpp::Any IRProducerVisitor::visitPrio11(ifccParser::Prio11Context *ctx) {
	//create 2 block :  second_member_bb , end_test_bb
	BasicBlock* bb_second_member=cfg->create_bb();
	BasicBlock* bb_end_and_paresseux=cfg->create_bb();
	BasicBlock* cur_bb=cfg->get_current_bb();
	bb_second_member->exit_true=bb_end_and_paresseux;
	bb_second_member->exit_false=bb_end_and_paresseux;
	
	bb_end_and_paresseux->exit_true=cur_bb->exit_true;
	bb_end_and_paresseux->exit_false=cur_bb->exit_false;

	cur_bb->exit_false=bb_end_and_paresseux;
	cur_bb->exit_true=bb_second_member;
	visit(ctx->expression(0));
	vector<string> p, q;
	string tmp = symbols->getTempVariable();
	p.push_back("!reg");
	cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_z,p);
	
	cfg->add_bb(bb_second_member);	
	cfg->set_current_bb(bb_second_member);
	visit(ctx->expression(1));

// ------------idem en terme de def
	cfg->add_bb(bb_end_and_paresseux);
	cfg->set_current_bb(bb_end_and_paresseux);
	cfg->add_IRInstr_to_current(IRInstr::Operation::cmp_zs,p);


	return 0;
}

/**
 * Return the number of errors 
 * 
 * @return int 
 */
int IRProducerVisitor::getErrors() {
	return errors;
}