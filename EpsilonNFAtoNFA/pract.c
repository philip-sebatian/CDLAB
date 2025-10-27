#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SIZE 100

int closure[MAX_SIZE][MAX_SIZE];
int trans[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int eps[MAX_SIZE][MAX_SIZE];
const int  N = 3;
int Alpha =  2;
void dfs(int s , int c){
    for(int i = 0 ; i<N;i++){
        if(!closure[c][i] && eps[s][i]){
            closure[c][i]=1;
            dfs(i,c);
        }
    }
}
int main(){
    

    // Clear all to 0
    memset(closure, 0, sizeof(closure));
    memset(trans, 0, sizeof(trans));
    memset(eps, 0, sizeof(eps));

    // Transition on 'a' (0)
    trans[0][0][1] = 1; // 0 --a--> 1
    trans[2][0][2] = 1; // 2 --a--> 2

    // Transition on 'b' (1)
    trans[1][1][2] = 1; // 1 --b--> 2

    // Epsilon transitions
    eps[0][2] = 1; // 0 --ε--> 2
    eps[1][0] = 1; // 1 --ε--> 0

    for(int i =  0;i<N;i++){
        for(int j = 0 ; j<N;j++){
            closure[i][j]=(i==j);
        }
        dfs(i,i);
    }
    
    for(int i = 0;i<N;i++){
        int result[MAX_SIZE] = {0};
        printf("%d - {",i);
        for(int a = 0 ; a < Alpha;a++){
            for(int j = 0;j<N;j++){
                if(closure[i][j]){
                    for(int k = 0 ; k<N;k++){
                        if(trans[j][a][k]){
                            for(int k2 = 0 ;k2<N;k2++){
                                if(closure[k][k2]){
                                    result[k2]=1;
                                }
                            }
                        }
                    }
                }
            }

        }
        for(int c = 0;c<N;c++){
            if( result[c]==1){
                printf("%d,\t",c);
            }
        }
        printf("}\n");
    }
}