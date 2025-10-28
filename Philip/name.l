%{
#include <stdio.h>
#include <string.h>
extern FILE *yyin;
%}

%option noyywrap

%%

"Philip" {printf("found");}
.   {}
%%

int main(){
    FILE *fp = fopen("input.txt","r");
    yyin = fp;
    yylex();
    return 1;

}