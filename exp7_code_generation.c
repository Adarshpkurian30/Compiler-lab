/*
 * Experiment 7: Intermediate Code Generation (Three Address Code)
 * Purpose: Generate three-address code from arithmetic expressions
 * KTU S7 BTech CSE - Compiler Lab
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char expr[MAX];
int temp_count = 1;
int i = 0;

// Function to generate new temporary variable
char* newTemp() {
    static char temp[10];
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

// Function prototypes
char* E();
char* T();
char* F();

// E -> T + E | T
char* E() {
    char *t1 = T();
    
    while (expr[i] == '+' || expr[i] == '-') {
        char op = expr[i];
        i++;
        char *t2 = T();
        char *temp = newTemp();
        printf("%s = %s %c %s\n", temp, t1, op, t2);
        t1 = temp;
    }
    
    return t1;
}

// T -> F * T | F
char* T() {
    char *t1 = F();
    
    while (expr[i] == '*' || expr[i] == '/') {
        char op = expr[i];
        i++;
        char *t2 = F();
        char *temp = newTemp();
        printf("%s = %s %c %s\n", temp, t1, op, t2);
        t1 = temp;
    }
    
    return t1;
}

// F -> (E) | id
char* F() {
    static char buffer[10];
    
    if (expr[i] == '(') {
        i++; // skip (
        char *t = E();
        i++; // skip )
        return t;
    } else if (isalnum(expr[i])) {
        int j = 0;
        while (isalnum(expr[i])) {
            buffer[j++] = expr[i++];
        }
        buffer[j] = '\0';
        return buffer;
    }
    
    return "";
}

// Function to remove spaces from expression
void removeSpaces(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ' && str[i] != '\t') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char result[10];
    
    printf("Three Address Code Generator - Experiment 7\n");
    printf("============================================\n\n");
    
    printf("Grammar:\n");
    printf("E -> E+T | E-T | T\n");
    printf("T -> T*F | T/F | F\n");
    printf("F -> (E) | id\n\n");
    
    printf("Enter an arithmetic expression:\n");
    printf("Example: a+b*c or (a+b)*(c-d)\n");
    printf("Input: ");
    fgets(expr, sizeof(expr), stdin);
    
    // Remove newline and spaces
    expr[strcspn(expr, "\n")] = 0;
    removeSpaces(expr);
    
    printf("\n=== Three Address Code ===\n\n");
    
    char *final = E();
    
    // Generate final assignment
    printf("%s = %s\n", "result", final);
    
    printf("\n=== Code Generation Complete ===\n");
    
    return 0;
}
