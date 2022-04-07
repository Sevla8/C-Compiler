grammar ifcc;

axiom : prog ;

prog : function+ EOF;

function : type=('int' | 'char' | 'void') IDENTIFIER '(' arguments? ')' block ;

arguments : arguments ',' arguments #funcsplit
| type=('int' | 'char') IDENTIFIER #funcarg;

block :'{' (declaration ';' | branch)* '}'  ;

condition : 'if' '(' expression ')' branch ('else' branch)? ;

branch : instruction | block | condition | loop;

loop: 'while' '(' expression ')' branch;

instruction : RETURN? expression? ';';
declaration : type=('int' | 'char') decllist;

decllist : declstatement ',' decllist | declstatement;
declstatement : IDENTIFIER (EQ expression)?;

expression : '(' expression ')' #prio1
| IDENTIFIER '(' callarglist? ')' #call
| (U_PRIO_2|BU_PRIO_2_4) expression #prio2
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
| IDENTIFIER #varvalue
| CHAR #char;  // pour décrire les expressions

callarglist : callarglist ',' callarglist #callsplit
| expression #callarg;

CHAR : '\''[ -~] '\'';  // dans la partie REGEX
EQ : '=';
U_PRIO_2 : '!' | '~';
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
IDENTIFIER : [A-Za-z_][A-Za-z0-9_]*;
CONST : [0-9]+ ;
COMMENT : (('/*' .*? '*/')| ('//' .*? '\n')) -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
