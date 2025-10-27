#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0;
int error = 0;

void E(); 
void E_();
void T();
void T_();
void F();

void match(char c) {
    if (input[pos] == c) {
        pos++;
    } else {
        error = 1;
    }
}

void E() {
    printf("E -> T E'\n");
    T();
    E_();
}

void E_() {
    if (input[pos] == '+') {
        printf("E' -> + T E'\n");
        match('+');
        T();
        E_();
    } else {
        printf("E' -> #\n");
    }
}

void T() {
    printf("T -> F T'\n");
    F();
    T_();
}

void T_() {
    if (input[pos] == '*') {
        printf("T' -> * F T'\n");
        match('*');
        F();
        T_();
    } else {
        printf("T' -> #\n");
    }
}

void F() {
    if (strncmp(&input[pos], "id", 2) == 0) {
        printf("F -> id\n");
        pos += 2;
    } 
    else if (input[pos] == '(') {
        printf("F -> ( E )\n");
        match('(');
        E();
        if (input[pos] == ')')
            match(')');
        else
            error = 1;
    } 
    else {
        error = 1;
    }
}

int main() {
    printf("Enter the input string: ");
    scanf("%s", input);

    E();

    if (pos == strlen(input) && error == 0)
        printf("\n Parsing Successful: Valid Syntax\n");
    else
        printf("\n Parsing Failed: Invalid Syntax\n");

    return 0;
}
