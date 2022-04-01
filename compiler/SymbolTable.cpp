#include "SymbolTable.h"

using namespace std;

bool SymbolTable::exists(std::string id) {
	return symbols.find(id)!=symbols.end();
}

void SymbolTable::variablesNotUsed() {
	std::map<std::string, VDescriptor>::iterator p;
	for(p = symbols.begin(); p != symbols.end(); p++)
  	{
		
		if (!p->second.getUsed())
		{
			cerr << "WARNING! Variable '" << p->first <<"' declared but never used.\n";
		}
		
  	}	
	return ;
}

void SymbolTable::add(std::string id, std::string type) {
	VDescriptor::TYPE t;
	if(type == "int"){
		t = VDescriptor::TYPE::tint;
	}else if(type == "char"){
		t = VDescriptor::TYPE::tchar;
	}
	VDescriptor vd ((int)(var_count*4), t);
	++var_count;
	symbols.insert(make_pair(id, vd));
}

VDescriptor& SymbolTable::get(std::string id) {
	std::map<std::string, VDescriptor>::iterator it;
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