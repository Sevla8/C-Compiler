
#include "IR.h"

using namespace std;

void CFG::specify_function(VDescriptor::TYPE t, string n, vector<pair<VDescriptor::TYPE, string>>& p) {
	type = t;
	name = n;
	params = p;
}
BasicBlock* CFG::create_bb() {
	// Name the new basic block
	BasicBlock *bb = new BasicBlock(this, name + string(".block") + to_string(nextBBnumber));
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
VDescriptor::TYPE CFG::get_type() {
	return type;
}
vector<pair<VDescriptor::TYPE, string>>& CFG::get_params() {
	return params;
}


void BasicBlock::gen_asm(ostream &o){
	// Generate the label
	o<<label<<':'<<endl;
	vector<IRInstr*>::iterator it;
	// Generate the asm for each instruction
	for(it=instrs.begin();it!=instrs.end();it++) {
		(*it)->gen_asm(o);
	}
	// Generate the jumps
	cfg->create_jumps(exit_true,exit_false,o);
}

void BasicBlock::add_IRInstr(IRInstr* instr) {
	instrs.push_back(instr);
}