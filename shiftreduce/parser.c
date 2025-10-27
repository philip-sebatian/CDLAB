#include <stdio.h>
#include <string.h>

char stack[50];
int top = -1;

char input[50];
int ip = 0;

// Helper push to stack
void push(char c) {
    stack[++top] = c;
}

// Helper display state
void display() {
    printf("\nStack: ");
    for (int i = 0; i <= top; i++) printf("%c", stack[i]);
    printf("\tInput: %s", input + ip);
}

// Try reduce when grammar matches top of stack
int try_reduce() {
    // F → i
    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'F';
        printf("\tReduce F→i");
        return 1;
    }

    // T → T * F
    if (top >= 2 && stack[top] == 'F' && stack[top - 1] == '*' && stack[top - 2] == 'T') {
        top -= 2;
        stack[top] = 'T';
        printf("\tReduce T→T*F");
        return 1;
    }

    // T → F
    if (top >= 0 && stack[top] == 'F') {
        stack[top] = 'T';
        printf("\tReduce T→F");
        return 1;
    }

    // E → E + T
    if (top >= 2 && stack[top] == 'T' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
        top -= 2;
        stack[top] = 'E';
        printf("\tReduce E→E+T");
        return 1;
    }

    // E → T
    if (top >= 0 && stack[top] == 'T') {
        stack[top] = 'E';
        printf("\tReduce E→T");
        return 1;
    }

    // F → (E)
    if (top >= 2 && stack[top] == ')' && stack[top - 2] == '(' && stack[top - 1] == 'E') {
        top -= 2;
        stack[top] = 'F';
        printf("\tReduce F→(E)");
        return 1;
    }

    return 0;
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);

    strcat(input, "$"); // mark end
    printf("\nShift Reduce Parsing:\n");

    while (1) {
        display();

        if (stack[top] == 'E' && input[ip] == '$') {
            printf("\nACCEPT\n");
            break;
        }

        // SHIFT
        printf("\tShift");
        push(input[ip++]);

        // Try reducing as much as possible
        while (try_reduce());
    }

    return 0;
}
