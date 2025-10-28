%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int yylex();
    void yyerror(char *c);
    extern FILE *yyin;
%}

%token NUM
%token ADD SUB
%token LPAR RPAR

%%
start:
    expression  {$$=$1;printf("%d",$$);}
    ;
expression:
    expression ADD term {$$=$1+$3;}
    | term  {$$=$1;}
    ;
term:
    term SUB id {$$=$1 - $3;}
    | id    {$$ = $1;}
    ;
id:
    NUM {$$=$1;}
    | LPAR expression RPAR {$$=$2;}
    ;
%%
void yyerror(char *s){
    printf("error");
}
int main(){
    FILE *fp = fopen("input.txt","r");
    yyin = fp;
    yyparse();

}
