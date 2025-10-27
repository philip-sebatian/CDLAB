%{
    #include <stdio.h>
    #include "if.tab.h"
%}
%option noyywrap
%%
[\t\n]+ {}
"if"    {return IF;}
"else"  {return ELSE;}
[a-zA-Z_][a-zA-Z0-9_]* {return ID;}
[0-9]+  {return NUM;}
"("     {return LPAR;}
")"     {return RPAR;}
"{"     {return LBRACE;}
"}"     {return RBRACE;}
";"     {return SEMICOLON;}
"="     {return ASSIGN;}
.       {printf("lexical error");}
%%