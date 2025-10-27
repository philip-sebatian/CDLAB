#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


#define MAX_SIZE 100
char stack[MAX_SIZE];
int top = -1;
int i = 0;
char input[100];
void push(char c){
    stack[++top]=c;
}


/*
E->E+T
T->T*F
F->i|(E)
*/
int reduce(){
    
    
    if(stack[top]=='F' && stack[top-1]=='*' && stack[top-2]=='T'){
        printf("T->T*F\n");
        top-=2;
        stack[top]='T';
        return 1;
    }
    else if(stack[top]=='T' && stack[top-1]=='+' && stack[top-2]=='E'){
        printf("E->E+T\n");
        top-=2;
        stack[top]='E';
        return 1;
    }
    if(stack[top]=='i'){
        printf("F->i\n");
        stack[top]='F';
        return 1;
    }

    if( stack[top]== 'T'){
        stack[top]='E';
        return 1;
    }
    if(stack[top]=='F'){
        stack[top]='T';
        return 1;
    }
    else if(stack[top]==')' && stack[top-1]=='E' && stack[top-2]=='('){
        printf("F->(E)\n");
        top-=2;
        stack[top]='F';
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);

    strcat(input, "$"); // mark end
    printf("%s\n",input);
    printf("\nShift Reduce Parsing:\n");

    while (1) {

        if (stack[top] == 'E' && input[i] == '$') {
            printf("\nACCEPT\n");
            break;
        }

        // SHIFT
        printf("\tShift");
        push(input[i++]);

        // Try reducing as much as possible
        while (reduce());
    }

    return 0;
}