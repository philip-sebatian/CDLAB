#include <stdio.h>
#include <string.h>

#define MAX 10
#define ALPHABET 2  // a,b

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

    printf("Enter transitions for 'a':\n");
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            scanf("%d", &trans[i][0][j]);

    printf("Enter transitions for 'b':\n");
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            scanf("%d", &trans[i][1][j]);

    int queue[1<<MAX], front = 0, rear = 0;

    int start = 1<<0; // State {0} as start
    queue[rear++] = start;
    visited[start] = 1;

    printf("\nDFA Transitions:\n----------------\n");

    while(front < rear) {
        int current = queue[front++];

        print_set(current);
        printf(":\n");

        for(int a = 0; a < ALPHABET; a++) {
            int next = 0;
            for(int s = 0; s < N; s++) {
                if(current & (1<<s)) {
                    for(int t = 0; t < N; t++) {
                        if(trans[s][a][t])
                            next |= 1<<t;
                    }
                }
            }

            dfa[current][a] = next;

            printf("  on '%c' -> ", 'a'+a);
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
