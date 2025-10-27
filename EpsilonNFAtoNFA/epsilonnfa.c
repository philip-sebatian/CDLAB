#include <stdio.h>

#define MAX 10
#define ALPHABET 2   // a,b -> 0,1

int eps[MAX][MAX];   // epsilon transitions matrix
int trans[MAX][ALPHABET][MAX]; // a and b transitions
int closure[MAX][MAX];
int N;

// DFS to compute epsilon closure
void dfs(int s, int c) {
    for(int i = 0; i < N; i++) {
        if(eps[s][i] && !closure[c][i]) {
            closure[c][i] = 1;
            dfs(i, c);
        }
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &N);

    printf("\nEnter epsilon transitions (matrix):\n");
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            scanf("%d", &eps[i][j]);

    printf("\nEnter transitions for a:\n");
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            scanf("%d", &trans[i][0][j]);

    printf("\nEnter transitions for b:\n");
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            scanf("%d", &trans[i][1][j]);

    // STEP 1: Compute epsilon closure
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            closure[i][j] = (i == j);
        dfs(i, i);
    }

    // STEP 2: New transitions = closure(source) -> trans -> closure(dest)
    printf("\n=== Converted NFA Without Epsilon ===\n");
    for(int s = 0; s < N; s++) {
        for(int a = 0; a < ALPHABET; a++) {
            printf("δ(%d, %c) -> { ", s, 'a' + a);
            for(int i = 0; i < N; i++) {
                if(closure[s][i]) {
                    for(int j = 0; j < N; j++) {
                        if(trans[i][a][j]) {
                            for(int k = 0; k < N; k++) {
                                if(closure[j][k])
                                    printf("%d ", k);
                            }
                        }
                    }
                }
            }
            printf("}\n");
        }
    }

    return 0;
}
