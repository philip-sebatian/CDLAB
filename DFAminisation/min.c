#include <stdio.h>

#define MAX 20

int nStates, nSymbols;
int dfa[MAX][MAX];
int finalState[MAX];
int table[MAX][MAX];

int isFinal(int x) {
    return finalState[x];
}

int main() {
    int i, j, k, x, y;
    
    printf("Enter number of states: ");
    scanf("%d", &nStates);
    
    printf("Enter number of input symbols: ");
    scanf("%d", &nSymbols);

    printf("\nEnter DFA transition table (state numbers start from 0):\n");
    for(i = 0; i < nStates; i++) {
        for(j = 0; j < nSymbols; j++) {
            printf("δ(%d, %c) = ", i, 'a' + j);
            scanf("%d", &dfa[i][j]);
        }
    }

    printf("\nEnter final states (1 for final, 0 for not final):\n");
    for(i = 0; i < nStates; i++) {
        printf("State %d: ", i);
        scanf("%d", &finalState[i]);
    }

    // Step 1: Mark table (initial distinguishability)
    for(i = 0; i < nStates; i++)
        for(j = 0; j < nStates; j++)
            table[i][j] = 0;

    for(i = 0; i < nStates; i++) {
        for(j = 0; j < i; j++) {
            if(isFinal(i) != isFinal(j))
                table[i][j] = 1; // Mark different finality states
        }
    }

    // Step 2: Propagation: mark pairs whose transitions lead to marked pairs
    int change;
    do {
        change = 0;
        for(i = 1; i < nStates; i++) {
            for(j = 0; j < i; j++) {
                if(table[i][j] == 0) {
                    for(k = 0; k < nSymbols; k++) {
                        x = dfa[i][k];
                        y = dfa[j][k];
                        if(x != y) {
                            int a = x > y ? x : y;
                            int b = x > y ? y : x;

                            if(table[a][b] == 1) {
                                table[i][j] = 1;
                                change = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    } while(change);

    // Step 3: Print Equivalent States (Groups)
    printf("\nEquivalent State Groups:\n");
    int grouped[MAX] = {0};
    
    for(i = 0; i < nStates; i++) {
        if(!grouped[i]) {
            printf("{ %d ", i);
            grouped[i] = 1;
            for(j = i + 1; j < nStates; j++) {
                int a = i > j ? i : j;
                int b = i > j ? j : i;
                if(table[a][b] == 0) {
                    printf(", %d ", j);
                    grouped[j] = 1;
                }
            }
            printf("}\n");
        }
    }

    return 0;
}
