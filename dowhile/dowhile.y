%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    extern FILE *yyin;
%}

%%token ID NUM ADD SUB MUL DIV ASSIGN RELOP LBRACE RBRACE LPAR RPAR DO WHILE

%%
start:
    statment_list
    ;
statment_list:
    DO LPAR expression RPAR
