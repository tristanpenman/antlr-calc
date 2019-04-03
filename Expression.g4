grammar Expression;

main: expr EOF;
expr: expr op=(MUL|DIV) expr  # multiplicativeExpr
    | expr op=(ADD|SUB) expr  # additiveExpr
    | LITERAL                 # literalExpr
    | LPAREN expr RPAREN      # bracketedExpr
    ;

ADD : '+' ;
DIV : '/' ;
MUL : '*' ;
SUB : '-' ;

LPAREN : '(' ;
RPAREN : ')' ;

LITERAL : '-'?('0'..'9')+('.'('0'..'9')+)? ;

WS : [ \r\n\t] + -> skip ;
