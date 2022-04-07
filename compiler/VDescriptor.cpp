#include "VDescriptor.h"

using namespace std;

int VDescriptor::getOffset() {
	/**
	 * Return the attribut offset
	 *
	 * @param none.
	 * @return offest (int, attribut).
	 */
	return offset;
}

bool VDescriptor::getUsed() {
	/**
	 * Return the attribut used
	 *
	 * @param none.
	 * @return used (bool, attribut).
	 */
	return used;
}

void VDescriptor::setUsed(bool v) {
	/**
	 * Set the attribut used
	 *
	 * @param bool: v, new value of used.
	 * @return void.
	 */
	used = v;
}

int VDescriptor::getBlockNumber() {
	/**
	 * Return the attribut blockNumber
	 *
	 * @param none.
	 * @return blockNumber (int, attribut).
	 */
	return blockNumber;
}

VDescriptor::TYPE getTypeFromString(string type) {
	/**
	 * Return the enum_type that corrsepond to the string_type gave in parametter 
	 *
	 * @param type:string, type of the variable (int, char).
	 * @return t (TYPE).
	 */
	VDescriptor::TYPE t = VDescriptor::TYPE::tvoid; //We use an public ENUM TYPE to set the type 
	if(type == "int"){
		t = VDescriptor::TYPE::tint;
	}else if(type == "char"){
		t = VDescriptor::TYPE::tchar;
	}
	return t;
}