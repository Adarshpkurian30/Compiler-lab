/*
 * Experiment 2: FIRST and FOLLOW Sets
 * Purpose: Compute FIRST and FOLLOW sets for a given grammar
 * Note: This is a simplified implementation for educational purposes.
 *       It handles basic grammars but may not cover all edge cases like
 *       epsilon productions in FOLLOW set calculations.
 * KTU S7 BTech CSE - Compiler Lab
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

int n; // Number of productions
char production[MAX][MAX];
char first[MAX][MAX];
char follow[MAX][MAX];
int f_count[MAX] = {0};
int fo_count[MAX] = {0};

// Function to add element to set
void addToSet(char arr[], int *count, char ch) {
    int i;
    for (i = 0; i < *count; i++) {
        if (arr[i] == ch)
            return;
    }
    arr[(*count)++] = ch;
}

// Function to find FIRST set
void findFirst(char c, int index) {
    int i, j;
    
    // If terminal, add to FIRST
    if (!isupper(c)) {
        addToSet(first[index], &f_count[index], c);
        return;
    }
    
    // Check all productions
    for (i = 0; i < n; i++) {
        if (production[i][0] == c) {
            // If epsilon production
            if (production[i][2] == '$') {
                addToSet(first[index], &f_count[index], '$');
            }
            // If first symbol is terminal
            else if (!isupper(production[i][2])) {
                addToSet(first[index], &f_count[index], production[i][2]);
            }
            // If first symbol is non-terminal
            else {
                findFirst(production[i][2], index);
            }
        }
    }
}

// Function to find FOLLOW set
void findFollow(char c, int index) {
    int i, j;
    
    // Add $ to FOLLOW of start symbol
    if (production[0][0] == c) {
        addToSet(follow[index], &fo_count[index], '$');
    }
    
    // Check all productions
    for (i = 0; i < n; i++) {
        for (j = 2; j < strlen(production[i]); j++) {
            if (production[i][j] == c) {
                // If not at the end
                if (production[i][j + 1] != '\0') {
                    char next = production[i][j + 1];
                    
                    // If next is terminal
                    if (!isupper(next)) {
                        addToSet(follow[index], &fo_count[index], next);
                    }
                    // If next is non-terminal
                    else {
                        // Add FIRST of next to FOLLOW
                        int k;
                        for (k = 0; k < MAX; k++) {
                            if (production[k][0] == next) {
                                int m;
                                for (m = 0; m < f_count[k]; m++) {
                                    if (first[k][m] != '$') {
                                        addToSet(follow[index], &fo_count[index], first[k][m]);
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
                // If at the end, add FOLLOW of LHS
                else {
                    if (production[i][0] != c) {
                        int k;
                        for (k = 0; k < MAX; k++) {
                            if (production[k][0] == production[i][0]) {
                                int m;
                                for (m = 0; m < fo_count[k]; m++) {
                                    addToSet(follow[index], &fo_count[index], follow[k][m]);
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int i, j, choice;
    char c, ch;
    
    printf("FIRST and FOLLOW Sets Calculator - Experiment 2\n");
    printf("================================================\n\n");
    
    printf("Enter the number of productions: ");
    scanf("%d", &n);
    getchar(); // consume newline
    
    printf("\nEnter the productions (format: A=BC or A=a or A=$):\n");
    printf("Use $ for epsilon\n");
    for (i = 0; i < n; i++) {
        printf("Production %d: ", i + 1);
        scanf("%s", production[i]);
    }
    
    // Calculate FIRST sets
    printf("\n=== FIRST SETS ===\n");
    for (i = 0; i < n; i++) {
        c = production[i][0];
        
        // Check if already calculated
        int found = 0;
        for (j = 0; j < i; j++) {
            if (production[j][0] == c) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            findFirst(c, i);
            printf("FIRST(%c) = { ", c);
            for (j = 0; j < f_count[i]; j++) {
                printf("%c ", first[i][j]);
            }
            printf("}\n");
        }
    }
    
    // Calculate FOLLOW sets
    printf("\n=== FOLLOW SETS ===\n");
    for (i = 0; i < n; i++) {
        c = production[i][0];
        
        // Check if already calculated
        int found = 0;
        for (j = 0; j < i; j++) {
            if (production[j][0] == c) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            findFollow(c, i);
            printf("FOLLOW(%c) = { ", c);
            for (j = 0; j < fo_count[i]; j++) {
                printf("%c ", follow[i][j]);
            }
            printf("}\n");
        }
    }
    
    return 0;
}
