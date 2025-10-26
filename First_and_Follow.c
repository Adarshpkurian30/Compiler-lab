#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 50
#define MAX_LEN 50

// Global grammar info
char productions[MAX_PROD][MAX_LEN];
char non_terminals[MAX_PROD];
char terminals[MAX_PROD];
char first[MAX_PROD][MAX_LEN];
char follow[MAX_PROD][MAX_LEN];

int prod_count = 0, nt_count = 0, t_count = 0;

//---------------------- Utility Functions ----------------------------//

// Check if character is Non-terminal (A-Z)
int isNonTerminal(char c) {
    return isupper(c);
}

// Add a character to a set (avoid duplicates)
void addToSet(char *set, char c) {
    if (strchr(set, c) == NULL) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

// Get index of Non-terminal
int indexOfNonTerminal(char c) {
    for (int i = 0; i < nt_count; i++)
        if (non_terminals[i] == c)
            return i;
    return -1;
}

//---------------------- FIRST SET Computation ----------------------------//

void computeFirst(char symbol, char *result) {
    // If terminal, add it directly
    if (!isNonTerminal(symbol)) {
        addToSet(result, symbol);
        return;
    }

    // Loop through productions
    for (int i = 0; i < prod_count; i++) {
        if (productions[i][0] == symbol) {
            // If production is like A->e
            if (productions[i][2] == 'e') {
                addToSet(result, 'e');
                continue;
            }

            // Process RHS symbols
            int j = 2;
            while (productions[i][j] != '\0') {
                char temp[20] = "";
                computeFirst(productions[i][j], temp);

                // Add non-epsilon symbols
                for (int k = 0; temp[k] != '\0'; k++)
                    if (temp[k] != 'e')
                        addToSet(result, temp[k]);

                // If epsilon not in FIRST(Xj), stop
                if (strchr(temp, 'e') == NULL)
                    break;

                j++;
            }

            // If all symbols can derive epsilon
            if (productions[i][j] == '\0')
                addToSet(result, 'e');
        }
    }
}

//---------------------- FOLLOW SET Computation ----------------------------//

void computeFollow(char symbol, char *result) {
    // Rule 1: Start symbol
    if (symbol == non_terminals[0])
        addToSet(result, '$');

    for (int i = 0; i < prod_count; i++) {
        for (int j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == symbol) {
                char next = productions[i][j + 1];

                if (next != '\0') {
                    // Rule 2: A->aBb
                    char temp[20] = "";
                    computeFirst(next, temp);

                    for (int k = 0; temp[k] != '\0'; k++)
                        if (temp[k] != 'e')
                            addToSet(result, temp[k]);

                    // If epsilon in FIRST(next)
                    if (strchr(temp, 'e')) {
                        char tempFollow[20] = "";
                        computeFollow(productions[i][0], tempFollow);
                        for (int k = 0; tempFollow[k] != '\0'; k++)
                            addToSet(result, tempFollow[k]);
                    }
                } else {
                    // Rule 3: A->aB (B at end)
                    if (symbol != productions[i][0]) {
                        char tempFollow[20] = "";
                        computeFollow(productions[i][0], tempFollow);
                        for (int k = 0; tempFollow[k] != '\0'; k++)
                            addToSet(result, tempFollow[k]);
                    }
                }
            }
        }
    }
}

//---------------------- DRIVER FUNCTION ----------------------------//

void computeFirstFollow() {
    // FIRST sets
    for (int i = 0; i < nt_count; i++) {
        char result[20] = "";
        computeFirst(non_terminals[i], result);
        strcpy(first[i], result);
        printf("FIRST(%c) = { %s }\n", non_terminals[i], result);
    }

    // FOLLOW sets (with multiple passes for convergence)
    for (int iter = 0; iter < nt_count; iter++) {
        for (int i = 0; i < nt_count; i++) {
            char result[20] = "";
            computeFollow(non_terminals[i], result);
            strcpy(follow[i], result);
        }
    }

    // Print FOLLOW sets
    for (int i = 0; i < nt_count; i++)
        printf("FOLLOW(%c) = { %s }\n", non_terminals[i], follow[i]);
}

//---------------------- MAIN ----------------------------//

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &prod_count);
    getchar();

    printf("Enter the productions( A->Bce, A->e,A->b (use 'e' for epsilon)):\n");
    for (int i = 0; i < prod_count; i++) {
        fgets(productions[i], MAX_LEN, stdin);
        productions[i][strcspn(productions[i], "\n")] = '\0';

        if (indexOfNonTerminal(productions[i][0]) == -1)
            non_terminals[nt_count++] = productions[i][0];
    }

    printf("\n--- FIRST and FOLLOW Sets ---\n");
    computeFirstFollow();

    return 0;
}
