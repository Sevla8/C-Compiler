#include "SymbolTable.h"
#include <iostream>

using namespace std;

bool SymbolTable::existCurrent(string id, int block) {
	pair<string, int> pair_id=make_pair(id,block);
	return symbols.find(pair_id)!=symbols.end();
}

void SymbolTable::variablesNotUsed() {
	map<pair<string, int>, VDescriptor>::iterator p;
	// Loop on all the symbols and to find which ones weren't used
	for(p = symbols.begin(); p != symbols.end(); p++)
  	{
		if (!p->second.getUsed())
		{
			cerr << "WARNING! Variable '" << p->first.first <<"' declared but never used.\n";
		}
		
  	}
	return ;
}

int SymbolTable::exists(string id) {
	int parent=currentBlock;
	int res=-1; // default value
	while(parent!=0){
		//check if the variable exist in this parent block
		if(existCurrent(id,parent)){
			res=parent;
			break;
		}
	
		parent=blockTree[parent];
	}
	return res;
}

void SymbolTable::add(std::string id, std::string type) {
	// Check the type size
	VDescriptor::TYPE t = getTypeFromString(type);
	int vsize = 0;
	if (t==VDescriptor::TYPE::tint) {
		// Align the stack for 4 bytes variables
		alignStack();
		vsize = 4;
	} else if (t==VDescriptor::TYPE::tchar) {
		vsize = 1;
	}
	// Insert the descriptor in the symbol table
	VDescriptor vd (stack_size+vsize, t, currentBlock);
	stack_size += vsize;
	pair<string, int> pair_id=make_pair(id,currentBlock);
	symbols.insert(make_pair(pair_id, vd));
}

VDescriptor& SymbolTable::get(pair<string, int> id) {
	map<pair<string, int>, VDescriptor>::iterator it;
	it = symbols.find(id);
	return it->second;
}

string SymbolTable::getTempVariable() {
	// Align the stack first
	alignStack();
	int offset = stack_size+tmp_size+4;
	tmp_size += 4;
	// Increase the max temporary size if we reached the limit
	if (tmp_size>max_tmp) {
		max_tmp = tmp_size;
	}
	return to_string(offset);
}

void SymbolTable::clearTempSection() {
	tmp_size = 0;
}

int SymbolTable::getMaxStackSize() {
	return stack_size+max_tmp;
}

void SymbolTable::addBlock(){
	int parent=currentBlock;
	currentBlock=blockTree.size();
	blockTree.push_back(parent);
}

void SymbolTable::setCurrentBlock(int block){
	currentBlock=block;
}

int SymbolTable::getCurrentBlock(){
	return currentBlock;
}

int SymbolTable::getParentBlock(int block){
	return blockTree[block];
}

void SymbolTable::alignStack(){
	if (stack_size%4!=0) {
		stack_size += 4 - (stack_size%4);
	}
}