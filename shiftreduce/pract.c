#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;
int ip=0;
/*
E->E+T|T
T->T*F|F
F->i| (E)
*/

void push(char c) {
    stack[++top] = c;
}

int reduce() {
    if(top >= 2 && stack[top]==')' && stack[top-1]=='E' && stack[top-2]=='(') {
        top -= 2;
        stack[top] = 'F';
        return 1;
    }

    if(stack[top] == 'i') {
        stack[top] = 'F';
        return 1;
    }

    if(top >= 2 && stack[top]=='F' && stack[top-1]=='*' && stack[top-2]=='T') {
        top -= 2;
        stack[top] = 'T';
        return 1;
    }

    if(stack[top]=='F') {
        stack[top]='T';
        return 1;
    }
    if(top >= 2 && stack[top]=='T' && stack[top-1]=='+' && stack[top-2]=='E') {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }
    if(stack[top]=='T') {
        stack[top]='E';
        return 1;
    }
    return 0;
}


int main(){
    char *input = "i+i*(i+i)$";
    while(1){
        while(reduce());
        if(stack[top]=='E' && input[ip]=='$'){
            printf("accept");
            return 0;
        }
        printf("shift\n");
        push(input[ip++]);

    }
    return 0;
}