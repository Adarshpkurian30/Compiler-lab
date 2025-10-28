/*
 * Experiment 5: Operator Precedence Parser
 * Purpose: Parse expressions using operator precedence relations
 * Grammar: E -> E+E | E*E | id
 * KTU S7 BTech CSE - Compiler Lab
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Precedence table
// Rows: +, *, id, $
// Cols: +, *, id, $
char precedence[4][4] = {
    {'>', '<', '<', '>'},  // +
    {'>', '>', '<', '>'},  // *
    {'>', '>', ' ', '>'},  // id
    {'<', '<', '<', '='}   // $
};

// Function to get index for precedence table
int getIndex(char c) {
    switch(c) {
        case '+': return 0;
        case '*': return 1;
        case 'i': return 2; // for id
        case '$': return 3;
        default: return -1;
    }
}

// Function to push to stack
void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    }
}

// Function to pop from stack
char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}

// Function to get top of stack
char peek() {
    if (top >= 0) {
        return stack[top];
    }
    return '\0';
}

// Function to reduce
void reduce() {
    printf("Reduce: ");
    int k = top;
    while (k >= 0 && stack[k] != '<') {
        k--;
    }
    
    for (int j = k + 1; j <= top; j++) {
        printf("%c", stack[j]);
    }
    printf(" -> E\n");
    
    top = k;
    push('E');
}

int main() {
    char input[MAX];
    int i;
    
    printf("Operator Precedence Parser - Experiment 5\n");
    printf("==========================================\n\n");
    printf("Grammar:\n");
    printf("E -> E+E | E*E | id\n\n");
    
    printf("Enter the input expression:\n");
    printf("Use 'i' for identifiers, example: i+i*i\n");
    printf("Input: ");
    scanf("%s", input);
    
    // Add $ at the end
    strcat(input, "$");
    
    // Initialize stack with $
    push('$');
    
    i = 0;
    printf("\n=== Parsing Steps ===\n\n");
    
    while (1) {
        char a = peek();
        char b = input[i];
        
        // For identifiers
        if (b == 'i' && isalpha(input[i+1])) {
            i++;
            continue;
        }
        
        int idx_a = getIndex(a == 'E' ? '+' : a);
        int idx_b = getIndex(b);
        
        if (idx_a == -1 || idx_b == -1) {
            printf("Invalid symbol\n");
            break;
        }
        
        char relation = precedence[idx_a][idx_b];
        
        printf("Stack: ");
        for (int j = 0; j <= top; j++) printf("%c", stack[j]);
        printf("\tInput: %s\t", &input[i]);
        
        if (relation == '<' || relation == '=') {
            printf("Shift %c\n", b);
            push(relation);
            push(b);
            i++;
        } else if (relation == '>') {
            reduce();
        } else {
            printf("Error\n");
            break;
        }
        
        // Check for acceptance
        if (peek() == 'E' && b == '$') {
            pop(); // E
            if (peek() == '$') {
                printf("\n=== SUCCESS: String is accepted ===\n");
                break;
            }
        }
        
        if (b == '$' && peek() == '$') {
            break;
        }
    }
    
    return 0;
}
