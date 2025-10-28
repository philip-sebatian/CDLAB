%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "eval.tab.h"
%}

%option noyywrap

%%
[\t\n]+ {}
[0-9]+ {yylval = atoi(yytext);return NUM;}
"+" {return ADD;}
"-" {return  SUB;}
"(" {return LPAR;}
")" {return RPAR;}
%%