#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100
void bitStuff(const char* input, char* output) {
    int count = 0; // Tracks consecutive 1s
    int j = 0,i;     // Index for output string
    for (i = 0; input[i] != '\0'; i++) {
        output[j++] = input[i];

        if (input[i] == '1') {
            count++;
            // If five consecutive 1s are found, stuff a 0
            if (count == 5) {
                output[j++] = '0';
                count = 0; // Reset counter after stuffing
            }
        } else {
            count = 0; // Reset counter if a 0 is encountered
        }
    }
    output[j] = '\0'; // Null-terminate the string
}

int main() {
    char input[MAX_SIZE];
    // Stuffed array size is larger to accommodate added '0' bits safely
    char stuffedOutput[MAX_SIZE * 2];

    // Prompt user for input
    printf("Enter the binary data (0s and 1s): ");

    // Reads up to 99 characters, stopping at white space or newlines
    if (scanf("%99s", input) != 1) {
        printf("Error reading input.\n");
        return 1;
    }

    // Process the input
    bitStuff(input, stuffedOutput);

    // Display results
    printf("\n--- Bit Stuffing Results ---\n");
    printf("Original Data: %s\n", input);
    printf("Stuffed Data:  %s\n", stuffedOutput);

    return 0;
}
