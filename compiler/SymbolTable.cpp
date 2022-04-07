#include "SymbolTable.h"
#include <iostream>

using namespace std;

bool SymbolTable::existCurrent(string id, int blockNum) {
	pair<string, int> pair_id=make_pair(id,blockNum);
	return symbols.find(pair_id)!=symbols.end();
}

void SymbolTable::variablesNotUsed() {
	map<pair<string, int>, VDescriptor>::iterator p;
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
	int res=-1;
	while(parent!=0){
		if(existCurrent(id,parent)){
			res=parent;

			break;
		}
	
		parent=blockTree.at(parent);
	}
	return res;
}

void SymbolTable::add(std::string id, std::string type) {
	VDescriptor::TYPE t = getTypeFromString(type);
	int vsize = 0;
	if (t==VDescriptor::TYPE::tint) {
		alignStack();
		vsize = 4;
	} else if (t==VDescriptor::TYPE::tchar) {
		vsize = 1;
	}
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
	alignStack();
	int offset = stack_size+tmp_size+4;
	tmp_size += 4;
	if (tmp_size>max_tmp) {
		max_tmp = tmp_size;
	}
	return to_string(offset);
}

void SymbolTable::clearTempSection() {
	tmp_size = 0;
	is_void = false;
}

void SymbolTable::setVoid(bool v) {
	is_void = v;
}
bool SymbolTable::isVoid() {
	return is_void;
}

int SymbolTable::getMaxStackSize() {
	return stack_size+max_tmp;
}

void SymbolTable::addBlock(){
	int parent=currentBlock;
	currentBlock=blockTree.size()+1;
	blockTree.insert(make_pair(currentBlock,parent));
}

void SymbolTable::setCurrentBlock(int numBlock){
	currentBlock=numBlock;
}

int SymbolTable::getCurrentBlock(){
	return currentBlock;
}

map<int, int> SymbolTable::getBlockTree(){
	return blockTree;
}

void SymbolTable::alignStack(){
	if (stack_size%4!=0) {
		stack_size += 4 - (stack_size%4);
	}
}