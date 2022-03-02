grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' instruction* RETURN expression ';' '}' ;

instruction : (declaration | expression) ';';
declaration : TYPE IDENTIFIER ('=' expression)?; 
expression : assignment | value | varvalue;
assignment : IDENTIFIER '=' expression;
value : CONST;
varvalue : IDENTIFIER;

RETURN : 'return';
TYPE : 'int';
IDENTIFIER : [A-Za-z_][A-Za-z0-9_]*;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
