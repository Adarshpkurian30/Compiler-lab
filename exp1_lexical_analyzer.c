/*
 * Experiment 1: Lexical Analyzer
 * Purpose: Tokenize source code and identify keywords, identifiers, operators, and constants
 * KTU S7 BTech CSE - Compiler Lab
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Keywords in C
char *keywords[] = {"int", "float", "char", "double", "if", "else", "for", "while", 
                    "return", "void", "main", "printf", "scanf"};
int num_keywords = 13;

// Function to check if a string is a keyword
int isKeyword(char *str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || 
            ch == '=' || ch == '<' || ch == '>' || ch == '!');
}

// Function to check if a character is a delimiter
int isDelimiter(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n' || ch == ';' || 
            ch == ',' || ch == '(' || ch == ')' || ch == '{' || 
            ch == '}' || ch == '[' || ch == ']');
}

// Main lexical analyzer function
void lexicalAnalyzer(char *input) {
    int i = 0, j;
    int len = strlen(input);
    char token[100];
    
    printf("\n=== LEXICAL ANALYSIS ===\n\n");
    
    while (i < len) {
        // Skip whitespace
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') {
            i++;
            continue;
        }
        
        // Check for operators
        if (isOperator(input[i])) {
            printf("OPERATOR: %c\n", input[i]);
            i++;
            continue;
        }
        
        // Check for delimiters (special symbols)
        if (isDelimiter(input[i])) {
            if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
                printf("DELIMITER: %c\n", input[i]);
            i++;
            continue;
        }
        
        // Check for numbers
        if (isdigit(input[i])) {
            j = 0;
            while (i < len && (isdigit(input[i]) || input[i] == '.')) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("NUMBER: %s\n", token);
            continue;
        }
        
        // Check for identifiers and keywords
        if (isalpha(input[i]) || input[i] == '_') {
            j = 0;
            while (i < len && (isalnum(input[i]) || input[i] == '_')) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            
            if (isKeyword(token))
                printf("KEYWORD: %s\n", token);
            else
                printf("IDENTIFIER: %s\n", token);
            continue;
        }
        
        // Check for string literals
        if (input[i] == '"') {
            j = 0;
            token[j++] = input[i++];
            while (i < len && input[i] != '"') {
                token[j++] = input[i++];
            }
            if (i < len) token[j++] = input[i++]; // closing quote
            token[j] = '\0';
            printf("STRING: %s\n", token);
            continue;
        }
        
        i++;
    }
}

int main() {
    char input[500];
    
    printf("Lexical Analyzer - Experiment 1\n");
    printf("================================\n\n");
    printf("Enter the source code (single line):\n");
    fgets(input, sizeof(input), stdin);
    
    lexicalAnalyzer(input);
    
    printf("\n=== Analysis Complete ===\n");
    
    return 0;
}
