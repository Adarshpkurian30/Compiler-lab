/*
 * Experiment 6: Code Optimization
 * Purpose: Demonstrate basic code optimization techniques
 *          - Constant Folding
 *          - Constant Propagation
 *          - Dead Code Elimination
 * KTU S7 BTech CSE - Compiler Lab
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 50

typedef struct {
    char op[10];
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

Quadruple code[MAX];
int n;

// Function to check if string is a number
int isNumber(char *str) {
    if (str[0] == '\0') return 0;
    int start = 0;
    // Check for optional minus sign at the beginning
    if (str[0] == '-') {
        if (str[1] == '\0') return 0; // Just a minus sign
        start = 1;
    }
    for (int i = start; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

// Function to perform constant folding
void constantFolding() {
    printf("\n=== Constant Folding ===\n");
    
    for (int i = 0; i < n; i++) {
        if (isNumber(code[i].arg1) && isNumber(code[i].arg2)) {
            int a = atoi(code[i].arg1);
            int b = atoi(code[i].arg2);
            int result;
            
            if (strcmp(code[i].op, "+") == 0) {
                result = a + b;
                printf("Optimizing: %s = %d + %d => %s = %d\n", 
                       code[i].result, a, b, code[i].result, result);
                sprintf(code[i].arg1, "%d", result);
                strcpy(code[i].arg2, "");
                strcpy(code[i].op, "=");
            }
            else if (strcmp(code[i].op, "-") == 0) {
                result = a - b;
                printf("Optimizing: %s = %d - %d => %s = %d\n", 
                       code[i].result, a, b, code[i].result, result);
                sprintf(code[i].arg1, "%d", result);
                strcpy(code[i].arg2, "");
                strcpy(code[i].op, "=");
            }
            else if (strcmp(code[i].op, "*") == 0) {
                result = a * b;
                printf("Optimizing: %s = %d * %d => %s = %d\n", 
                       code[i].result, a, b, code[i].result, result);
                sprintf(code[i].arg1, "%d", result);
                strcpy(code[i].arg2, "");
                strcpy(code[i].op, "=");
            }
            else if (strcmp(code[i].op, "/") == 0 && b != 0) {
                result = a / b;
                printf("Optimizing: %s = %d / %d => %s = %d\n", 
                       code[i].result, a, b, code[i].result, result);
                sprintf(code[i].arg1, "%d", result);
                strcpy(code[i].arg2, "");
                strcpy(code[i].op, "=");
            }
        }
    }
}

// Function to eliminate dead code
void deadCodeElimination() {
    printf("\n=== Dead Code Elimination ===\n");
    int used[MAX] = {0};
    
    // Mark all variables that are used
    for (int i = 0; i < n; i++) {
        if (strlen(code[i].arg1) > 0 && !isNumber(code[i].arg1)) {
            for (int j = 0; j < n; j++) {
                if (strcmp(code[j].result, code[i].arg1) == 0) {
                    used[j] = 1;
                }
            }
        }
        if (strlen(code[i].arg2) > 0 && !isNumber(code[i].arg2)) {
            for (int j = 0; j < n; j++) {
                if (strcmp(code[j].result, code[i].arg2) == 0) {
                    used[j] = 1;
                }
            }
        }
    }
    
    // Mark the last statement as used (output)
    used[n-1] = 1;
    
    // Remove unused code
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            printf("Eliminating dead code at line %d: %s = %s %s %s\n", 
                   i+1, code[i].result, code[i].arg1, code[i].op, code[i].arg2);
        }
    }
}

// Function to display code
void displayCode() {
    printf("\n%-10s %-10s %-10s %-10s\n", "Result", "Arg1", "Op", "Arg2");
    printf("---------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10s %-10s %-10s %-10s\n", 
               code[i].result, code[i].arg1, code[i].op, code[i].arg2);
    }
}

int main() {
    printf("Code Optimization - Experiment 6\n");
    printf("=================================\n\n");
    
    printf("Enter number of statements: ");
    scanf("%d", &n);
    
    printf("\nEnter the three-address code:\n");
    printf("Format: result arg1 op arg2\n");
    printf("Example: t1 a + b\n");
    printf("For assignment: result arg1 = (leave op empty)\n\n");
    
    for (int i = 0; i < n; i++) {
        printf("Statement %d: ", i+1);
        scanf("%s %s %s", code[i].result, code[i].arg1, code[i].op);
        if (strcmp(code[i].op, "=") != 0) {
            scanf("%s", code[i].arg2);
        } else {
            strcpy(code[i].arg2, "");
        }
    }
    
    printf("\n=== Original Code ===");
    displayCode();
    
    constantFolding();
    
    printf("\n=== Optimized Code ===");
    displayCode();
    
    deadCodeElimination();
    
    return 0;
}
