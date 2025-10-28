#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ip = 0;
char *input ;
void match(char c){
    if(input[ip]==c)ip++;
}

/*
E->TE'
E'-> +TE'|#
T->FT'
T'->*FT'|#
F->id| (E)
*/


void E(){
    T();
    E_();
}

void T(){

   if(input[ip]=='+'){ 
    match('+');
    T();
    E_();
    }
    else{
        
    }
}