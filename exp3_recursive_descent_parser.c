/*
 * Experiment 3: Recursive Descent Parser
 * Purpose: Implement a recursive descent parser for a simple grammar
 * Grammar: E -> TE'
 *          E' -> +TE' | ε
 *          T -> FT'
 *          T' -> *FT' | ε
 *          F -> (E) | id
 * KTU S7 BTech CSE - Compiler Lab
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int i = 0;
int error = 0;

// Function prototypes
void E();
void E_prime();
void T();
void T_prime();
void F();

// Function to match terminal
void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        error = 1;
        printf("\nError: Expected '%c' but found '%c' at position %d\n", expected, input[i], i);
    }
}

// E -> TE'
void E() {
    printf("E -> TE'\n");
    T();
    E_prime();
}

// E' -> +TE' | ε
void E_prime() {
    if (input[i] == '+') {
        printf("E' -> +TE'\n");
        match('+');
        T();
        E_prime();
    } else {
        printf("E' -> ε\n");
        // Epsilon production, do nothing
    }
}

// T -> FT'
void T() {
    printf("T -> FT'\n");
    F();
    T_prime();
}

// T' -> *FT' | ε
void T_prime() {
    if (input[i] == '*') {
        printf("T' -> *FT'\n");
        match('*');
        F();
        T_prime();
    } else {
        printf("T' -> ε\n");
        // Epsilon production, do nothing
    }
}

// F -> (E) | id
void F() {
    if (input[i] == '(') {
        printf("F -> (E)\n");
        match('(');
        E();
        match(')');
    } else if (isalnum(input[i])) {
        printf("F -> id\n");
        match(input[i]);
    } else {
        error = 1;
        printf("\nError: Invalid symbol '%c' at position %d\n", input[i], i);
    }
}

int main() {
    printf("Recursive Descent Parser - Experiment 3\n");
    printf("========================================\n\n");
    printf("Grammar:\n");
    printf("E  -> TE'\n");
    printf("E' -> +TE' | ε\n");
    printf("T  -> FT'\n");
    printf("T' -> *FT' | ε\n");
    printf("F  -> (E) | id\n\n");
    
    printf("Enter an expression (use single characters for identifiers):\n");
    printf("Example: a+b*c or (a+b)*c\n");
    printf("Input: ");
    scanf("%s", input);
    
    printf("\n=== Parsing Steps ===\n\n");
    
    E();
    
    if (input[i] == '\0' && error == 0) {
        printf("\n=== SUCCESS: String is accepted ===\n");
    } else if (error == 0) {
        printf("\n=== ERROR: Extra symbols after valid expression ===\n");
    } else {
        printf("\n=== ERROR: String is not accepted ===\n");
    }
    
    return 0;
}
