#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- Globals ---
char stack[100];
int top = -1;

// The precedence table
// Rows: Stack Top [+, *, (, ), a, $]
// Cols: Input     [+, *, (, ), a, $]
char prec_table[6][6] = {
    //  +    * (    )    a    $
    { '>', '<', '<', '>', '<', '>' }, // +
    { '>', '>', '<', '>', '<', '>' }, // *
    { '<', '<', '<', '=', '<', 'E' }, // (
    { '>', '>', 'E', '>', 'E', '>' }, // )
    { '>', '>', 'E', '>', 'E', '>' }, // a (id)
    { '<', '<', '<', 'E', '<', 'A' }  // $
};

// --- Stack Functions ---
void push(char c) {
    if (top >= 99) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

// --- Helper Functions ---

/**
 * @brief Gets the table index for a given terminal character.
 */
int get_index(char c) {
    switch (c) {
        case '+': return 0;
        case '*': return 1;
        case '(': return 2;
        case ')': return 3;
        case 'a': return 4; // 'a' represents 'id'
        case '$': return 5;
        default:  return -1; // Error
    }
}

/**
 * @brief Displays the current state of the stack.
 */
void display_stack() {
    printf("\t");
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
}

/**
 * @brief Displays the remaining portion of the input string.
 */
void display_input(char *input, int ip) {
    printf("\t\t");
    for (int i = ip; input[i] != '\0'; i++) {
        printf("%c", input[i]);
    }
}

// --- Main Parser Logic ---
int main() {
    char input[100];
    char a, b; // a: current input symbol, b: top of stack
    char relation;
    int ip = 0; // Input pointer
    int stack_idx, input_idx;

    // Get input from user
    printf("Enter the input string (use 'a' for id, e.g., a+a*a): ");
    scanf("%s", input);

    // Append '$' to mark the end of the input
    strcat(input, "$");

    // Initialize stack with '$'
    push('$');

    printf("\n--- Parsing Steps ---\n");
    printf("STACK\t\tINPUT\t\tRELATION\tACTION\n");
    printf("----------------------------------------------------------------\n");

    // The main parsing loop
    while (1) {
        // 1. Get current input symbol
        a = input[ip];

        // 2. Get top-most terminal from stack
        // (In this simple version, we assume only terminals are on the stack)
        b = stack[top];

        // 3. Get table indices
        stack_idx = get_index(b);
        input_idx = get_index(a);

        if (stack_idx == -1 || input_idx == -1) {
            printf("\nError: Invalid character in input or stack.\n");
            exit(1);
        }

        // 4. Find precedence relation
        relation = prec_table[stack_idx][input_idx];

        // 5. Print current state
        display_stack();
        display_input(input, ip);
        printf("\t\t%c", relation);

        // 6. Decide action based on relation
        if (relation == '<' || relation == '=') {
            // SHIFT
            printf("\t\tSHIFT %c\n", a);
            push(a);
            ip++; // Advance input pointer
        } 
        else if (relation == '>') {
            // REDUCE
            // In this simple parser, we just pop the "handle".
            // A full parser would replace the handle with a non-terminal.
            char popped = pop();
            printf("\t\tREDUCE %c\n", popped);
            // DO NOT advance input pointer, loop again
        }
        else if (relation == 'A') {
            // ACCEPT
            printf("\t\tACCEPT\n");
            break;
        }
        else {
            // ERROR
            printf("\n\nError: Syntax error. No valid relation.\n");
            printf("Stack top: %c, Input: %c\n", b, a);
            exit(1);
        }
    }

    printf("\n--- String successfully parsed! ---\n");
    return 0;
}