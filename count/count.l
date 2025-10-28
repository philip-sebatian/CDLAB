%{
    #include <stdio.h>
    #include <string.h>
    extern FILE *yyin;
    int countw = 0;
    int countc = 0;
    int countn = 0;

%}

%option noyywrap

%%
[\n]+ {countn++;}
[a-zA-Z]+   {countc+=strlen(yytext);countw+=1;}

%%

int main(){
    FILE *fp = fopen("input.txt","r");
    yyin = fp;
    yylex();
    printf("Number of lines %d \n",countn);
    printf("Number of word %d \n",countw);
    printf("Number of character %d \n",countc);
}