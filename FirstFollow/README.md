## Core Logic Explained

### Data Structures

* `char productions[20][100]`: An array of strings to store the grammar rules (e.g., `"E=TR"`).
* `char first_sets[26][100]`: A 2D array where `first_sets[0]` stores the **FIRST** set for 'A', `first_sets[1]` for 'B', etc., as a string.
* `char follow_sets[26][100]`: Similar to `first_sets`, but for **FOLLOW** sets.
* `char non_terminals[26]`: Stores all unique non-terminals found in the grammar.

---

### FIRST Set Algorithm (Iterative)

The program loops until no new terminals are added to any **FIRST** set.

1.  **Rule 1**: If $X$ is a terminal, $FIRST(X) = \{X\}$.
2.  **Rule 2**: If $X \to \#$ (epsilon), add $`\#`$ to $FIRST(X)$.
3.  **Rule 3**: If $X \to Y_1Y_2...Y_k$:
    * Add $FIRST(Y_1) - \{\#\}$ to $FIRST(X)$.
    * If $`\#`$ is in $FIRST(Y_1)$, add $FIRST(Y_2) - \{\#\}$ to $FIRST(X)$.
    * ...and so on.
    * If $`\#`$ is in $FIRST(Y_i)$ for all $i$, add $`\#`$ to $FIRST(X)$.

The iterative approach handles dependencies (e.g., $FIRST(E)$ needs $FIRST(T)$) by re-evaluating until the sets stabilize.

---

### FOLLOW Set Algorithm (Iterative)

This also loops until no new terminals are added to any **FOLLOW** set.

1.  **Rule 1**: Add $`\$`$ (end marker) to the $FOLLOW$ set of the **Start Symbol**.
2.  **Rule 2**: For a production $A \to \alpha B \beta$:
    * Add $FIRST(\beta) - \{\#\}$ to $FOLLOW(B)$.
3.  **Rule 3**: For a production $A \to \alpha B$, or $A \to \alpha B \beta$ where $`\#`$ is in $FIRST(\beta)$:
    * Add $FOLLOW(A)$ to $FOLLOW(B)$.