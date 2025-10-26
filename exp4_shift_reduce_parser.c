/*
 * Experiment 4: Shift-Reduce Parser
 * Purpose: Implement a shift-reduce parser for a simple grammar
 * Grammar: E -> E+E | E*E | (E) | id
 * KTU S7 BTech CSE - Compiler Lab
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char stack[MAX];
int top = -1;
char input[MAX];
int i = 0;

// Function to push to stack
void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
        stack[top + 1] = '\0';
    }
}

// Function to pop from stack
char pop() {
    if (top >= 0) {
        char c = stack[top];
        stack[top--] = '\0';
        return c;
    }
    return '\0';
}

// Function to display stack and input
void display() {
    printf("%-20s %-20s\n", stack, &input[i]);
}

// Function to check for reductions
int reduce() {
    // Check for E -> id
    if (top >= 1 && stack[top] == 'd' && stack[top-1] == 'i') {
        pop(); pop();
        push('E');
        printf("%-20s %-20s REDUCE E->id\n", stack, &input[i]);
        return 1;
    }
    
    // Check for E -> (E)
    if (top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(') {
        pop(); pop(); pop();
        push('E');
        printf("%-20s %-20s REDUCE E->(E)\n", stack, &input[i]);
        return 1;
    }
    
    // Check for E -> E+E
    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '+' && stack[top-2] == 'E') {
        pop(); pop(); pop();
        push('E');
        printf("%-20s %-20s REDUCE E->E+E\n", stack, &input[i]);
        return 1;
    }
    
    // Check for E -> E*E
    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '*' && stack[top-2] == 'E') {
        pop(); pop(); pop();
        push('E');
        printf("%-20s %-20s REDUCE E->E*E\n", stack, &input[i]);
        return 1;
    }
    
    return 0;
}

int main() {
    printf("Shift-Reduce Parser - Experiment 4\n");
    printf("===================================\n\n");
    printf("Grammar:\n");
    printf("E -> E+E\n");
    printf("E -> E*E\n");
    printf("E -> (E)\n");
    printf("E -> id\n\n");
    
    printf("Enter the input string (use 'id' for identifiers):\n");
    printf("Example: id+id*id\n");
    printf("Input: ");
    scanf("%s", input);
    strcat(input, "$"); // Add end marker
    
    printf("\n%-20s %-20s ACTION\n", "STACK", "INPUT");
    printf("--------------------------------------------------------\n");
    
    push('$'); // Initialize stack with $
    display();
    
    while (1) {
        // Try to reduce
        while (reduce());
        
        // Check for acceptance
        if (top == 1 && stack[0] == '$' && stack[1] == 'E' && input[i] == '$') {
            printf("\n=== SUCCESS: String is accepted ===\n");
            break;
        }
        
        // Shift
        if (input[i] != '$') {
            push(input[i]);
            printf("%-20s %-20s SHIFT\n", stack, &input[++i]);
        } else {
            printf("\n=== ERROR: String is not accepted ===\n");
            break;
        }
    }
    
    return 0;
}
