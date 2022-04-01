grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' block ;

block :'{' (declaration ';' | branch)* '}'  ;

condition : 'if' '(' expression ')' branch ('else' branch)? ;

branch : instruction | block | condition | loop;

loop: 'while' '(' expression ')' branch;

instruction : (RETURN? expression)? ';';

declaration : TYPE IDENTIFIER (EQ expression)?;
expression : '(' expression ')' #prio1
| BU_PRIO_2_4 expression #prio2
| expression B_PRIO_3 expression #prio3
| expression BU_PRIO_2_4 expression #prio4
| expression B_PRIO_5 expression #prio5
| expression B_PRIO_6 expression #prio6
| expression B_PRIO_7 expression #prio7
| expression B_PRIO_8 expression #prio8
| expression B_PRIO_9 expression #prio9
| expression B_PRIO_10 expression #prio10
| expression B_PRIO_11 expression #prio11
| expression B_PRIO_12 expression #prio12
| expression '?' expression ':' expression #prio13
| IDENTIFIER (EQ|B_PRIO_14) expression #prio14
| CONST #value
| IDENTIFIER #varvalue;

EQ : '=';
B_PRIO_3 : '*' | '/' | '%';
BU_PRIO_2_4 : '+' | '-';
B_PRIO_5 : '<<' | '>>';
B_PRIO_6 : '<' | '>' | '<=' | '>=';
B_PRIO_7 : '==' | '!=';
B_PRIO_8 : '&';
B_PRIO_9 : '^';
B_PRIO_10 : '|';
B_PRIO_11 : '&&';
B_PRIO_12 : '||';
B_PRIO_14 : '+=' | '-=' | '*=' | '/=' | '%=' | '<<=' | '>>=' | '&=' | '^=' | '|=';
RETURN : 'return';
TYPE : 'int';
IDENTIFIER : [A-Za-z_][A-Za-z0-9_]*;
CONST : [0-9]+ ;
COMMENT : (('/*' .*? '*/')| ('//' .*? '\n')) -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
