#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_SIZE 10
#define ALPHA 2 
int trans[MAX_SIZE][ALPHA][MAX_SIZE];
int dfa[1<<MAX_SIZE][MAX_SIZE];
visited[1<<MAX_SIZE];

int main(){
    int N;

    int queue[1<<MAX_SIZE];
    int front = 0;
    int rear = 0;
    queue[rear++] = 1<<0;
    while(rear>front){
        int current = queue[front++];
        int next = 0;
        for(int a = 0 ; a<ALPHA;a++){
            for(int s=0;s<N;s++){
                if(current & 1<<s){
                    for(int j = 0 ; j<N;j++){
                        if(trans[s][a][j]){
                            next |= 1<<j;
                        }
                    
                    }
                }
            }
        }
        for(int a = 0; a<ALPHA;a++){
            dfa[current][a]=next;
            if(!visited[next]){
                visited[next]=1;
                queue[rear++]=next;
            }
        }
        

    }

}
