#include "VDescriptor.h"

using namespace std;

int VDescriptor::getOffset() {
	return offset;
}

bool VDescriptor::getUsed() {
	return used;
}

void VDescriptor::setUsed(bool v) {
	used = v;
}

int VDescriptor::getBlockNumber() {
	return blockNumber;
}

VDescriptor::TYPE getTypeFromString(string type) {
	VDescriptor::TYPE t = VDescriptor::TYPE::tvoid;
	if(type == "int"){
		t = VDescriptor::TYPE::tint;
	}else if(type == "char"){
		t = VDescriptor::TYPE::tchar;
	}
	return t;
}