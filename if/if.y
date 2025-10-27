%{
    #include <stdio.h>
    int yylex();
    void yyerror(char *s);
%}

/* Tokens */
%token IF ELSE
%token LPAR RPAR LBRACE RBRACE SEMICOLON
%token ID NUM ASSIGN

/* Fix dangling-else: ELSE has higher precedence */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

program:
    statement_list {printf("valid")};
    ;

statement_list:
      statement
    | statement_list statement
    ;

statement:
      if_statement
    | simple_statement
    | compound_statement
    ;

simple_statement:
      expression SEMICOLON
    ;

compound_statement:
      LBRACE statement_list RBRACE
    ;

if_statement:
      IF LPAR expression RPAR statement %prec LOWER_THAN_ELSE
    | IF LPAR expression RPAR statement ELSE statement
    ;

expression:
      ID
    | NUM
    | ID ASSIGN expression
    ;
%%

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    return yyparse();
}
