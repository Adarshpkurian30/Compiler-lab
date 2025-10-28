/*
 * Experiment 8: Symbol Table Management
 * Purpose: Implement a symbol table with insert, search, display, and delete operations
 * KTU S7 BTech CSE - Compiler Lab
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 100

typedef struct Symbol {
    char name[50];
    char type[20];
    int scope;
    int address;
    struct Symbol *next;
} Symbol;

Symbol *hashTable[TABLE_SIZE];

// Hash function
int hash(char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    return sum % TABLE_SIZE;
}

// Function to insert symbol
void insert() {
    char name[50], type[20];
    int scope, address;
    
    printf("\nEnter symbol name: ");
    scanf("%s", name);
    printf("Enter type (int/float/char/etc): ");
    scanf("%s", type);
    printf("Enter scope: ");
    scanf("%d", &scope);
    printf("Enter address: ");
    scanf("%d", &address);
    
    int index = hash(name);
    
    // Check if symbol already exists
    Symbol *temp = hashTable[index];
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0 && temp->scope == scope) {
            printf("Symbol already exists in this scope!\n");
            return;
        }
        temp = temp->next;
    }
    
    // Create new symbol
    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    strcpy(newSymbol->type, type);
    newSymbol->scope = scope;
    newSymbol->address = address;
    newSymbol->next = hashTable[index];
    hashTable[index] = newSymbol;
    
    printf("Symbol inserted successfully!\n");
}

// Function to search symbol
void search() {
    char name[50];
    int scope;
    
    printf("\nEnter symbol name to search: ");
    scanf("%s", name);
    printf("Enter scope: ");
    scanf("%d", &scope);
    
    int index = hash(name);
    Symbol *temp = hashTable[index];
    
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0 && temp->scope == scope) {
            printf("\n=== Symbol Found ===\n");
            printf("Name: %s\n", temp->name);
            printf("Type: %s\n", temp->type);
            printf("Scope: %d\n", temp->scope);
            printf("Address: %d\n", temp->address);
            return;
        }
        temp = temp->next;
    }
    
    printf("Symbol not found!\n");
}

// Function to display all symbols
void display() {
    printf("\n=== Symbol Table ===\n");
    printf("%-15s %-15s %-10s %-10s\n", "Name", "Type", "Scope", "Address");
    printf("------------------------------------------------------\n");
    
    int empty = 1;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *temp = hashTable[i];
        while (temp != NULL) {
            printf("%-15s %-15s %-10d %-10d\n", 
                   temp->name, temp->type, temp->scope, temp->address);
            temp = temp->next;
            empty = 0;
        }
    }
    
    if (empty) {
        printf("Symbol table is empty!\n");
    }
}

// Function to delete symbol
void deleteSymbol() {
    char name[50];
    int scope;
    
    printf("\nEnter symbol name to delete: ");
    scanf("%s", name);
    printf("Enter scope: ");
    scanf("%d", &scope);
    
    int index = hash(name);
    Symbol *temp = hashTable[index];
    Symbol *prev = NULL;
    
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0 && temp->scope == scope) {
            if (prev == NULL) {
                hashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Symbol deleted successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    
    printf("Symbol not found!\n");
}

// Function to modify symbol
void modify() {
    char name[50];
    int scope;
    
    printf("\nEnter symbol name to modify: ");
    scanf("%s", name);
    printf("Enter scope: ");
    scanf("%d", &scope);
    
    int index = hash(name);
    Symbol *temp = hashTable[index];
    
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0 && temp->scope == scope) {
            printf("Enter new type: ");
            scanf("%s", temp->type);
            printf("Enter new address: ");
            scanf("%d", &temp->address);
            printf("Symbol modified successfully!\n");
            return;
        }
        temp = temp->next;
    }
    
    printf("Symbol not found!\n");
}

int main() {
    int choice;
    
    // Initialize hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    
    printf("Symbol Table Management - Experiment 8\n");
    printf("=======================================\n");
    
    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. Insert symbol\n");
        printf("2. Search symbol\n");
        printf("3. Display symbol table\n");
        printf("4. Delete symbol\n");
        printf("5. Modify symbol\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                insert();
                break;
            case 2:
                search();
                break;
            case 3:
                display();
                break;
            case 4:
                deleteSymbol();
                break;
            case 5:
                modify();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
