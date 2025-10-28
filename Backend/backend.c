#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Instruction {
    char result[10];
    char op1[10];
    char op2[10];
    char op;
};

int main() {
    struct Instruction code[10];
    int n, i;
    char reg[10][10];

    printf("Enter number of intermediate code instructions: ");
    scanf("%d", &n);

    printf("Enter the intermediate code in format (result = op1 operator op2)\n");
    for (i = 0; i < n; i++) {
        scanf("%s = %s %c %s", code[i].result, code[i].op1, &code[i].op, code[i].op2);
    }

    printf("\nGenerated Machine Code:\n");
    for (i = 0; i < n; i++) {
        char *r = reg[i];
        sprintf(r, "R%d", i);  // assign register name

        // Load first operand
        if (isalpha(code[i].op1[0]))
            printf("MOV %s, %s\n", r, code[i].op1);
        else
            printf("MOV %s, #%s\n", r, code[i].op1); // immediate value

        // Perform operation
        switch (code[i].op) {
            case '+': printf("ADD %s, %s\n", r, code[i].op2); break;
            case '-': printf("SUB %s, %s\n", r, code[i].op2); break;
            case '*': printf("MUL %s, %s\n", r, code[i].op2); break;
            case '/': printf("DIV %s, %s\n", r, code[i].op2); break;
        }

        // Store result
        printf("MOV %s, %s\n\n", code[i].result, r);
    }

    return 0;
}
