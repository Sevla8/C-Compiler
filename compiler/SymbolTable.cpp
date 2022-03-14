#include "SymbolTable.h"

using namespace std;

bool SymbolTable::exists(std::string id) {
	return symbols.find(id)!=symbols.end();
}

void SymbolTable::add(std::string id) {
	VDescriptor vd(var_count*4);
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