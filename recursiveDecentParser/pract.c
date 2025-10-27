#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
E->TE'
E'->+TE'| #
T -> FT'
T'-> *FT'| #
F -> i | (E)
*/
char *input;
int i = 0;

void match(char c){
    if(input[i]==c){
        i++;
    }
}
void E();
void E_();
void T();
void T_();
void F();

void E(){
    printf("%s\t",input+i);
    printf("E->TE'\n");
    T();
    E_();
}

void E_(){
    printf("%s\t",input+i);
    if(input[i]=='+'){
        printf("E'->+TE'\n");
        match('+');
        T();
        E_();
    }
    else{
        printf("E'->#\n");
    }
}

void T(){
    printf("%s\t",input+i);
    printf("T->FT'\n");
    F();
    T_();
}

void T_(){
    printf("%s\t",input+i);
    if(input[i]=='*'){
        printf("T'->*FT'\n");
        match('*');
        F();
        T_();
    }
    else{
        printf("T'->#\n");
    }
}

void F(){
    printf("%s\t",input+i);
    if(input[i]=='i'){
        match('i'); 
        printf("F -> i\n");
    }
    else if(input[i]=='('){
        printf("F->(E)\n");
        match('(');
        E();
        if(input[i]==')'){
            match(')');
        }
    }
}

int main(){
    input = "i+i*(i*i)\0";
    E();
}
