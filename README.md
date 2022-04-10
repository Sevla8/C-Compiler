# C compiler with antlr4/c++

## Instructions

This contains a basic C compiler using
Antlr4 for C++. The compiler can deal with single C files
containing int or char variables, one-dimensional arrays,
functions and while/if else structures, 
as well as arithmetic, binary and logical operators. 

## Prerequisites
  Before building your  compiler, you should install  antlr using your
  distribution's  package manager,  or by  running the  provided shell
  script:   `cd  .. ; ./install-antlr.sh`. 
  
## Source Files
Examples of C files that can be compiled are in tests/testfiles.

run `make` to make the ifcc compiler in `compiler` for debian distributions.
(`make ubuntu` and `make fedora` are available for other distributions)
run `make test` to run the tests
run `make clean` to clean compiled files and tests outputs.