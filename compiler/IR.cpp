
#include "IR.h"

using namespace std;

void CFG::specify_function(string n, vector<string>& p) {
	name = n;
	params = p;
}
BasicBlock* CFG::create_bb() {
	BasicBlock *bb = new BasicBlock(this, name + string(".block") + to_string(nextBBnumber));
	// current_bb = bb;
	++nextBBnumber;    
	return bb;
}

void CFG::set_current_bb(BasicBlock* bb){
	current_bb=bb;
}
BasicBlock* CFG::get_current_bb(){
	return current_bb;
}
void CFG::add_bb(BasicBlock* newBB){
	bbs.push_back(newBB);
}
SymbolTable& CFG::get_table() {
	return symbols;
}
string CFG::get_name() {
	return name;
}
vector<string>& CFG::get_params() {
	return params;
}


void BasicBlock::gen_asm(ostream &o){
	o<<label<<':'<<endl;
	vector<IRInstr*>::iterator it;
	for(it=instrs.begin();it!=instrs.end();it++) {
		(*it)->gen_asm(o);
	}
	cfg->create_jumps(exit_true,exit_false,o);
}

void BasicBlock::add_IRInstr(IRInstr* instr) {
	instrs.push_back(instr);
}