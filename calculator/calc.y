%{
    #include <stdio.h>
    int yylex();
    int yyerror(char *s);
    extern FILE *yyin;
%}

%token NUM
%token DIV MUL
%token ADD SUB
%token LPAR RPAR

%left ADD SUB
%left MUL DIV

%%
start:
    expression  {printf("%d",$1);}
    ;

expression:
      expression ADD expression {$$ = $1 + $3;}
    | expression SUB expression {$$ = $1 - $3;}
    | expression MUL expression {$$ = $1*$3;}
    | expression DIV expression {$$ = $1/$3;}
    | LPAR expression RPAR {$$ = $2}
    | NUM {$$ = $1}
    ;
%%

int main(int argc, char *argv[]){
    FILE *fp = fopen(argv[1], "r");
    yyin = fp;
    yyparse();
}

int yyerror(char *s){
    printf("error\n");
    return 0;
}
