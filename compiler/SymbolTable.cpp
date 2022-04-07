#include "SymbolTable.h"
#include <iostream>

using namespace std;

// Modifier pour regarder dans les blocs parents 
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
	VDescriptor::TYPE t;
	if(type == "int"){
		t = VDescriptor::TYPE::tint;
	}else if(type == "char"){
		t = VDescriptor::TYPE::tchar;
	}
	VDescriptor vd ((int)(var_count*4), t, currentBlock);
	++var_count;
	pair<string, int> pair_id=make_pair(id,currentBlock);
	symbols.insert(make_pair(pair_id, vd));
}

VDescriptor& SymbolTable::get(pair<string, int> id) {
	map<pair<string, int>, VDescriptor>::iterator it;
	it = symbols.find(id);
	return it->second;
}

string SymbolTable::getTempVariable() {
	int offset = var_count*4;
	++var_count;
	++tmp_count;
	if (tmp_count>max_tmp) {
		max_tmp = tmp_count;
	}
	return to_string(offset);
}

void SymbolTable::clearTempVariable() {
	var_count -= tmp_count;
	tmp_count = 0;
}

int SymbolTable::getMaxStackSize() {
	return (var_count+max_tmp)*4;
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