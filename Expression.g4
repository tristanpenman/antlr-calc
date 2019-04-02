grammar Expression;

main: expr EOF;
expr: expr ('*'|'/') expr
    | expr ('+'|'-') expr
    | INT
    | '(' expr ')'
    ;

INT : [0-9]+ ;
