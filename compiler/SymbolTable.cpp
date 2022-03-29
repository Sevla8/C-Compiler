#include "SymbolTable.h"
#include <iostream>

using namespace std;

// Modifier pour regarder dans les blocs parents 
bool SymbolTable::existCurrent(std::string id, int blockNum) {
	std::pair<std::string, int> pair_id=make_pair(id,blockNum);
	return symbols.find(pair_id)!=symbols.end();
}

int SymbolTable::exists(std::string id) {
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

void SymbolTable::add(string id) {
	VDescriptor vd(var_count*4,currentBlock);
	++var_count;
	std::pair<std::string, int> pair_id=make_pair(id,currentBlock);
	symbols.insert(make_pair(pair_id, vd));
}

VDescriptor& SymbolTable::get(std::pair<std::string, int> id) {
	std::map<std::pair<std::string, int>, VDescriptor>::iterator it;
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
std::map<int, int> SymbolTable::getBlockTree(){
	return blockTree;
}