# C compiler with antlr4/c++

## Instructions

This contains a basic C compiler using
Antlr4 for C++. The compiler can deal with single C files
containing int or char variables, one-dimensional arrays,
functions and while/if else structures, 
as well as arithmetic, binary and logical operators. 

## Source Files
- `ifcc.g4` contains the grammar in antlr4 format.
- `main.cpp` contains the C++ code to call the antlr4-generated parser.
  on the file name provided in the command line.
- `VariableAnalyserVisitor.h` analyses the code and allocates memory space for all variables.
- `IRProducerVisitor.h` produces the IR of the assembly code.
- `IR.h` is a generic version of the IR, which can be specified for each targeted architecture.
- `IRx86.h` is an implementation of IR.h for the x86 architecture.
- `SymbolTable.h` encapsulates the symbol table.
- `VDescriptor.h` encapsulates a variable descriptor for the symbol table.

## Prerequisites
  Before building your  compiler, you should install  antlr using your
  distribution's  package manager,  or by  running the  provided shell
  script:   `cd  .. ; ./install-antlr.sh`. 
    
## Compilation scripts
- `Makefile` contains  the actual build  logic. Please read  this file
  and ask questions on parts you do not understand.
  The  Makefile uses  3  variables (ANTLRJAR,  ANTLRINC and  ANTLRLIB)
  indicating the location of various parts of the Antlr suite. 
  You can (should)  change  those values to suit your installation, either
  by editing the  Makefile and/or on the command  line, as illustrated
  by the `runmake_*` scripts.
- `runmake_fedora.sh` and `runmake_ubuntu.sh` are examples of such a script. it shows how
  makefile variables can be overriden from the command-line.

