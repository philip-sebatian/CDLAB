%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    extern FILE *yyin;
    int yylex();
    void yyerror(char *s);
%}

%token ID NUM ADD SUB MUL DIV ASSIGN RELOP LBRACE RBRACE LPAR RPAR DO WHILE SEMICOLON

%%
start:
    dowhile {printf("valid\n");}
    ;
dowhile:
    DO LBRACE statment_list RBRACE while
    ;

while:
    WHILE LPAR expression RPAR
    ;

expression:
    ID RELOP ID
    | ID RELOP NUM
    |ID ASSIGN NUM
    ;
statment_list:
    expression SEMICOLON
    | expression SEMICOLON statment_list
    ;
%%
void yyerror(char *s){
    printf("error\n");
}
int main(){
    FILE *fp = fopen("input.txt","r");
    yyin = fp;
    yyparse();
}

