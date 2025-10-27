%{
    #include <stdio.h>
    #include "calc.tab.h"
%}

%option noyywrap

%%
[ \t\n] {}
[0-9]+ { yylval = atoi(yytext); return NUM;}
"+" {return ADD;}
"-" {return SUB;}
"*" {return MUL;}
"/" {return DIV;}
"(" {return LPAR;}
")" {return RPAR;}
. {printf(" logic error");}
%%