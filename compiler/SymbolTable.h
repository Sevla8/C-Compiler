#pragma once

/**
 * \file SymbolTable.h
 * \brief The symbol table of one function
 * \author H4224
 *
 */

//-------------------------------------------------------- Include system
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

//-------------------------------------------------------- Include personnal
#include "VDescriptor.h"

/**
 * \class SymbolTable
 *  
 * \brief Class defining the symbol table structure associated to one function
 */
class SymbolTable {
public:

  SymbolTable() {
    blockTree.push_back(0);
  }
  /**
   * \brief find in which block the symbol exists, in the current block or its parents
   * 
   * \param id identifier of the variable
   * \return int the most recent parent block where the variable is defined (-1 if in no parent)
   */
  int exists(string id);

  /**
   * \brief prints non-used variables
   * 
   */
  void variablesNotUsed();

  /**
   * \brief add a symbol to the current block
   * 
   * \param id identifier of the variable
   * \param type of the variable
   */
  void add(string id, string type);

  /**
   * \brief get the variable descriptor associated to an identifier
   * 
   * \param id a pair <identifier, block> identifying a unique descriptor
   * \return VDescriptor& the descriptor
   */
  VDescriptor& get(pair<string, int> id);

  /**
   * \brief Allocates a temporary variable and returns its identifier
   * 
   * \return string the identifier of the temporary variable
   */
  string getTempVariable();

  /**
   * \brief Clears the temporary variables allocated
   * 
   */
  void clearTempSection();

  /**
   * \brief Gets the maximum size to allocated all permanent and temporary variables
   * 
   * \return int size allocated on stack
   */
  int getMaxStackSize();

  /**
   * \brief Adds a new block as a child of the current one
   * 
   */
  void addBlock();

  /**
   * \brief Set the current block
   * 
   * \param block the new current block
   */
  void setCurrentBlock(int block);

  /**
   * \brief Get the current block
   * 
   * \return int the current block
   */
  int getCurrentBlock();

  /**
   * \brief Gets the parent of a block
   * 
   * \param block a given block
   * \return int its parent
   */
  int getParentBlock(int block);

  /**
   * \brief Check if the identifier exists in a given block
   * 
   * \param id the identifier
   * \param block the block
   * \return true it exists
   * \return false it doesn't exist
   */
  bool existCurrent(string id,int block);

protected:
  /**
   * \brief Aligns the stack properly for the next allocated variable
   * 
   */
  void alignStack();

  
  /** \brief The map storing all the symbols, of format <identifier, block> -> descriptor */
  map<pair<string, int>, VDescriptor> symbols;
  
  /** \brief The current size of the declared variable in the stack */
  int stack_size = 0;
  
  /** \brief The current size of the temporary variables */
  int tmp_size = 0;
  
  /** \brief The maximum size of the temporary variables */
  int max_tmp = 0;
  
  /** \brief The current block we are looking in the symbol table */
  int currentBlock = 0;
  
  /** \brief The block tree, of format block -> parentBlock */
  vector<int> blockTree;
};

