#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// ===== Stack for characters (used in infix to postfix) =====
char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

// ===== Convert infix expression to postfix =====
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char c;
    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];
        if (isalnum(c)) { // operand
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();
            pop(); // pop '('
        } else { // operator
            while (top != -1 && precedence(stack[top]) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }
    while (top != -1)
        postfix[k++] = pop();
    postfix[k] = '\0';
}

// ===== Generate code (Operator, Destn, Op1, Op2 format) =====
void generateCode(char postfix[]) {
    char tempStack[MAX][10];
    int tempTop = -1;
    char tempReg = 'Z'; // Registers from Z, Y, X...
    char op1[10], op2[10], temp[10];

    printf("\nOprtr\tDestn\tOp1\tOp2\n");

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isalnum(c)) {
            char operand[2] = {c, '\0'};
            strcpy(tempStack[++tempTop], operand);
        } else {
            // Pop two operands
            strcpy(op2, tempStack[tempTop--]);
            strcpy(op1, tempStack[tempTop--]);

            sprintf(temp, "%c", tempReg);

            // Print in same format as your original code
            printf("%c\t%c\t%s\t%s\n", c, tempReg, op1, op2);

            // Push result register back to stack
            strcpy(tempStack[++tempTop], temp);
            tempReg--;
        }
    }
}

// ===== Main =====
int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("\nPostfix Expression: %s\n", postfix);

    generateCode(postfix);

    return 0;
}
