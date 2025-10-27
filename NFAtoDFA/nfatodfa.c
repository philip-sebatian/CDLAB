#include <stdio.h>
#include <string.h>

#define MAX 10
#define ALPHABET 2  // a, b

int N; // number of NFA states
int trans[MAX][ALPHABET][MAX]; // transition table

int dfa[1<<MAX][ALPHABET]; // DFA transitions
int visited[1<<MAX];

void print_set(int state) {
    printf("{ ");
    for (int i = 0; i < N; i++)
        if (state & (1<<i))
            printf("%d ", i);
    printf("}");
}

int main() {
    printf("Enter number of NFA states: ");
    scanf("%d", &N);

    // ✅ Improved user-friendly input
    printf("\nEnter NFA transitions:\n");
    for(int i = 0; i < N; i++) {
        for(int a = 0; a < ALPHABET; a++) {
            for(int j = 0; j < N; j++) {
                printf("Is there a transition from q%d to q%d on '%c'? (0/1): ",
                       i, j, 'a' + a);
                scanf("%d", &trans[i][a][j]);
            }
        }
    }

    memset(visited, 0, sizeof(visited));

    int queue[1<<MAX], front = 0, rear = 0;

    int start = 1<<0; // Start state = {0}
    queue[rear++] = start;
    visited[start] = 1;

    printf("\nDFA Transitions:\n----------------\n");

    while(front < rear) {
        int current = queue[front++];

        print_set(current);
        printf(":\n");

        // Compute transitions for current DFA state
        for(int a = 0; a < ALPHABET; a++)
            dfa[current][a] = 0;

        for(int s = 0; s < N; s++) {
            if(current & (1<<s)) {
                for(int a = 0; a < ALPHABET; a++) {
                    for(int t = 0; t < N; t++) {
                        if(trans[s][a][t])
                            dfa[current][a] |= (1 << t);
                    }
                }
            }
        }

        for(int a = 0; a < ALPHABET; a++) {
            int next = dfa[current][a];
            printf("  on '%c' -> ", 'a' + a);
            print_set(next);
            printf("\n");

            if(!visited[next]) {
                visited[next] = 1;
                queue[rear++] = next;
            }
        }
        printf("\n");
    }

    return 0;
}
