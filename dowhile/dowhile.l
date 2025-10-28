%{
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "dowhile.tab.h"

%}

%option noyywrap

%%
[ \t\n]+ {}
"do" {return DO;}
"while" {return WHILE;}
[0-9]+ {return NUM;}
[a-zA-Z][a-zA-Z_]* {return ID;}
"+" {return ADD;}
"-" {return SUB;}
"*" {return MUL;}
"/" {return DIV;}
"==" {return RELOP;}
"=" {return ASSIGN;}
">" {return RELOP;}
"<" {return RELOP;}
"(" {return LPAR;}
")" {return RPAR;}
"{" {return LBRACE;}
"}" {return RBRACE;}
";" {return SEMICOLON;}
. {printf("invalid\n");}
%%