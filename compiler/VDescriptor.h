#pragma once

/**
 * \file VDescriptor.h
 * \brief Definition of a variable for the symbol table
 * \author H4224
 *
 */

//-------------------------------------------------------- Include system
#include <string>
using namespace std;

/**
 * \class VDescriptor
 *  
 * \brief Class defining the variable caracteristic for the symbol table
 */
class VDescriptor {
public:
  /**
   *\enum TYPE 
   * 
   * \brief enum describing a type (int void char)
   * 
   */
  enum TYPE {
    tvoid = 0,
    tint = 1,
    tchar = 2,
  };
   /**
   * \brief Construct a new VDescriptor object
   * 
   * \param off offset of the variable, leads to the storage location
   * \param t type of the variable  
   * \param blockNum id of the block the variable belong to  
   */
  VDescriptor(int off, TYPE t,int blockNum) : offset(off),type(t),blockNumber(blockNum) {}
  
  /**
	 * \brief get the variable offset
	 * 
	 * \return offset
	 */
  int getOffset();

  /**
	 * \brief watch if the variable have already been used
	 * 
	 * \return used
	 */
  bool getUsed();

  /**
	 * \brief set the used attribut (it watch if the variable have already been used)
	 */
  void setUsed(bool v);

  /**
   * \brief return the block number the variable belong to 
   * 
   * \return blockNumber
   */
  int getBlockNumber();

  /**
   * \brief return the variable type using TYPE enum
   * 
   * \return type
   */
  TYPE getType() {return type;};
  
protected:
  TYPE type; 
  int offset;
  bool used= false;
  int blockNumber;
};

VDescriptor::TYPE getTypeFromString(string type);