#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
int N ;
char prod[MAX_SIZE][26];
int firstset[26][26];
int followset[26][26];

void add(char c , char *set){
    if(strchr(set,c)==NULL){
        set[strlen(set)]=c;
        set[strlen(set)+1]='\0';
    }
}


void first(char c){
    for(int i =0 ; i < N;i++){
        char * rhs = &prod[i][3];
        if(prod[i][0]==c){
            if(!isupper(rhs[0])|| rhs[0]=='#'){
                add(rhs[0],firstset[c-'A']);
            }
            else{
                if(firstset[rhs[0]-'A'][0]=='\0'){
                    first(rhs[0]);
                }
                for(int j = 0 ; firstset[rhs[0]-'A'][j];j++){
                    add(rhs[0],firstset[c-'A']);
                }
            }
        }
    }
}