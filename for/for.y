%{
    #include <stdio.h>
    extern FILE *yyin;
    int yylex();
    void yyerror(char *s);
%}

/* All your tokens */
%token FOR
%token LPAR RPAR LBRACE RBRACE SEMICOLON
%token ID NUM
%token RELOP ASSIGN
%token ADD MINUS
%token MULT DIV

/* Operator precedence and associativity (lowest to highest) */
%right ASSIGN
%left RELOP
%left ADD MINUS
%left MULT DIV

%%
start:
    statement_list {printf("Parse successful: valid\n");}
    ;
statement_list:
    statement
    | statement_list statement
    ;
statement:
    for_statement
    | compound_statement
    | simple_statement
    ;
for_statement:
    FOR LPAR expression SEMICOLON expression SEMICOLON expression RPAR statement
    ;

/* CORRECTED: Allows both empty {} and { ... } */
compound_statement:
    LBRACE RBRACE
    | LBRACE statement_list RBRACE
    ;

/* CORRECTED: Allows "i=1;" and also just ";" */
simple_statement:
    expression SEMICOLON
    | SEMICOLON
    ;

/*
 *
 * THIS IS THE MOST IMPORTANT FIX
 * Your expression grammar must have ALL of these rules
 *
 */
expression:
    /* Assignment */
    ID ASSIGN expression

    /* Relational */
    | expression RELOP expression

    /* Arithmetic */
    | expression ADD expression
    | expression MINUS expression
    | expression MULT expression
    | expression DIV expression

    /* Terminals */
    | ID
    | NUM
    ;
%%

int main(int argc, char *argv[]){
    if(argc > 1){
        FILE *fp = fopen(argv[1], "r");
        if(!fp){
            printf("Error: Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = fp;
        printf("Parsing file: %s\n", argv[1]);
    } else {
        printf("Enter code (Ctrl+D to parse):\n");
    }
    yyparse();
    return 0;
}
void yyerror(char * s){
    /* This message is more helpful */
    printf("Parser error: invalid syntax\n");
}