%{
    #include <stdio.h>
    #include "for.tab.h"
%}
%option noyywrap
%%
[ \t\n]+ {}
"for" {return FOR;}
[a-zA-Z_][a-zA-Z0-9_]* {return ID;}
[0-9]+ {return NUM;}
";" {return SEMICOLON;}
"(" {return LPAR;}
")" {return RPAR;}
"{" {return LBRACE;}
"}" {return RBRACE;}
"==" {return RELOP;}
">=" {return RELOP;}
"<=" {return RELOP;}
">" {return RELOP;}
"<" {return RELOP;}
"=" {return ASSIGN;}
"+" {return ADD;}
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}
. {printf("syntax error");}
%%


