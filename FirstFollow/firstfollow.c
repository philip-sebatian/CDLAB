#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

int n;
char prod[MAX][20];
char first[26][20];
char follow[26][20];
char nonterminals[26];
int n_nt = 0;

// Utility: add a symbol to a set if not already present
void add(char *set, char c) {
    if (c == '\0') return;
    if (strchr(set, c) == NULL) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

// Collect all unique nonterminals
void findNonTerminals() {
    for (int i = 0; i < n; i++) {
        char nt = prod[i][0];
        if (isupper(nt) && strchr(nonterminals, nt) == NULL)
            nonterminals[n_nt++] = nt;
    }
}

// Recursive function to compute FIRST
void findFirst(char nt) {
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == nt) {
            char *rhs = &prod[i][3]; // skip "A->"
            if (!isupper(rhs[0])) {
                add(first[nt - 'A'], rhs[0]); // terminal or #
            } else {
                // FIRST of another nonterminal
                if (first[rhs[0] - 'A'][0] == '\0')
                    findFirst(rhs[0]);
                for (int j = 0; first[rhs[0] - 'A'][j]; j++)
                    add(first[nt - 'A'], first[rhs[0] - 'A'][j]);
            }
        }
    }
}

// Recursive function to compute FOLLOW
void findFollow(char nt) {
    // Rule 1: Add '$' to FOLLOW(start symbol)
    if (nt == prod[0][0])
        add(follow[nt - 'A'], '$');

    for (int i = 0; i < n; i++) {
        char *rhs = &prod[i][3];
        for (int j = 0; rhs[j]; j++) {
            if (rhs[j] == nt) {
                if (rhs[j + 1] == '\0') {
                    // Rule 2: if B is at end -> add FOLLOW(A)
                    if (follow[prod[i][0] - 'A'][0] == '\0')
                        findFollow(prod[i][0]);
                    for (int k = 0; follow[prod[i][0] - 'A'][k]; k++)
                        add(follow[nt - 'A'], follow[prod[i][0] - 'A'][k]);
                } 
                else if (!isupper(rhs[j + 1])) {
                    // Rule 3: terminal follows B
                    add(follow[nt - 'A'], rhs[j + 1]);
                } 
                else {
                    // Rule 4: nonterminal follows B
                    char next = rhs[j + 1];
                    if (first[next - 'A'][0] == '\0')
                        findFirst(next);
                    int hasEpsilon = 0;
                    for (int k = 0; first[next - 'A'][k]; k++) {
                        if (first[next - 'A'][k] == '#')
                            hasEpsilon = 1;
                        else
                            add(follow[nt - 'A'], first[next - 'A'][k]);
                    }
                    // if epsilon in FIRST(next) → add FOLLOW(A)
                    if (hasEpsilon) {
                        if (follow[prod[i][0] - 'A'][0] == '\0')
                            findFollow(prod[i][0]);
                        for (int k = 0; follow[prod[i][0] - 'A'][k]; k++)
                            add(follow[nt - 'A'], follow[prod[i][0] - 'A'][k]);
                    }
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter productions (e.g., E->TR, R->+TR, R->#):\n");
    for (int i = 0; i < n; i++) {
        printf("P[%d]: ", i);
        fgets(prod[i], 20, stdin);
        prod[i][strcspn(prod[i], "\n")] = '\0';
    }

    findNonTerminals();

    // Compute FIRST sets
    for (int i = 0; i < n_nt; i++)
        findFirst(nonterminals[i]);

    printf("\n--- FIRST Sets ---\n");
    for (int i = 0; i < n_nt; i++) {
        printf("FIRST(%c) = { ", nonterminals[i]);
        for (int j = 0; first[nonterminals[i] - 'A'][j]; j++)
            printf("%c ", first[nonterminals[i] - 'A'][j]);
        printf("}\n");
    }

    // Compute FOLLOW sets
    for (int i = 0; i < n_nt; i++)
        findFollow(nonterminals[i]);

    printf("\n--- FOLLOW Sets ---\n");
    for (int i = 0; i < n_nt; i++) {
        printf("FOLLOW(%c) = { ", nonterminals[i]);
        for (int j = 0; follow[nonterminals[i] - 'A'][j]; j++)
            printf("%c ", follow[nonterminals[i] - 'A'][j]);
        printf("}\n");
    }

    return 0;
}
