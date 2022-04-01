#include "VDescriptor.h"

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