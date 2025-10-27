#include<stdio.h>      // Standard input-output functions (printf, scanf, fopen, etc.)
#include<string.h>     // String handling functions (strcpy, strcmp, etc.)

// Global declarations
char result[20][20];   // Stores epsilon closure result states
char copy[3];          // Stores the copy of the current state (base state)
char states[20][20];   // Stores all states entered by the user

// Function to add a state into result array at position i
void add_state(char a[3], int i)
{
    strcpy(result[i], a);   // Copies string 'a' into result[i]
}

// Function to display epsilon closure
void display(int n)
{
    int k = 0;   // Counter variable
    printf("\n Epsilon closure of %s = {", copy);  // Displaying which state’s closure is printed
    while(k < n)   // Loop through result array and print all states
    {
        printf(" %s", result[k]);  // Print each state in closure
        k++;
    }
    printf(" }\n");  // Close the curly bracket of closure set
}

// Main function
int main()
{
    FILE *INPUT;   // File pointer for reading transitions
    INPUT = fopen("inputec.txt", "r");   // Open transition file in read mode
    if(INPUT == NULL)   // Check if file exists
    {
        printf("Error opening file!\n");
        return 1;
    }

    char state[3];       // Current state being processed
    int end;             // Variable to check for EOF (end of file)
    int n;               // Total number of states
    int k = 0;           // Loop counter
    int i = 0;           // Index for result array

    char state1[3], input[3], state2[3];  // Variables to read transition lines (from file)

    // Step 1: Read number of states
    printf("\n Enter the no of states: ");
    scanf("%d", &n);

    // Step 2: Read all states
    printf("\n Enter the states: ");
    for(k = 0; k < n; k++)   // Loop through each state
    {
        scanf("%s", states[k]);   // Read and store each state
    }

    // Step 3: For each state entered, find its epsilon closure
    for(k = 0; k < n; k++)
    {
        i = 0;                         // Reset index for result array
        strcpy(state, states[k]);       // Copy one state from list into variable 'state'
        strcpy(copy, state);            // Copy same state into 'copy' for displaying purpose
        add_state(state, i++);          // Add current state to result (first element of closure)

        // Step 4: Read transition lines from file until EOF
        while(1)
        {
            end = fscanf(INPUT, "%s %s %s", state1, input, state2);  // Read one line (state1, input, state2)
            if(end == EOF)   // If end of file, break the loop
            {
                break;
            }

            // If the current line's starting state equals our current state
            if(strcmp(state, state1) == 0)
            {
                // Check if input symbol is epsilon (represented as 'e')
                if(strcmp(input, "e") == 0)
                {
                    add_state(state2, i++);   // Add the epsilon reachable state to result array
                    strcpy(state, state2);    // Update current state to newly reached state
                }
            }
        }

        // Step 5: Display the epsilon closure for this state
        display(i);

        // Step 6: Reset file pointer back to start for next state
        rewind(INPUT);
    }

    fclose(INPUT);   // Close file after use
    return 0;        // End of program
}
