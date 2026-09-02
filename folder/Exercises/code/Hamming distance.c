#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main() {
    char input_str[100];
    int codeword[8];
    int received[8];
    int data[4];
    int p1, p2, p4, p8;
    int s1, s2, s4, syndrome;
    int global_check;
    int error_choice;
    int bit1, bit2;
    // Declare loop variables at the top to satisfy older C compilers
    int char_idx, i;
    int length;
    // Seed the randomizer for picking positions
    srand(time(NULL));
    // 1. Input: Read an alphanumeric string
    printf("Enter an alphanumeric string: ");
    if (fgets(input_str, sizeof(input_str), stdin) == NULL) {
        return 1;
    }
    // Remove newline character if present
    input_str[strcspn(input_str, "\n")] = '\0';
    length = strlen(input_str);
    if (length == 0) {
        printf("Empty input.\n");
        return 1;
    }
    // Ask how many bits to flip once for the whole transmission session
    printf("\n--- ERROR SIMULATION MENU ---\n");
    printf("How many bits do you want to flip in the message blocks? (0, 1, or 2): ");
    scanf("%d", &error_choice);
    // Process each character block in the string sequentially
    for (char_idx = 0; char_idx < length; char_idx++) {
        char current_char = input_str[char_idx];
        // Extract the lower 4 bits of the ASCII character
        data[0] = (current_char >> 3) & 1; // D3
        data[1] = (current_char >> 2) & 1; // D5
        data[2] = (current_char >> 1) & 1; // D6
        data[3] = (current_char >> 0) & 1; // D7
        printf("\n=========================================\n");
        printf("PROCESSING BLOCK %d: Character '%c'\n", char_idx + 1, current_char);
        printf("=========================================\n");
        printf("Extracted 4 bits: D3=%d, D5=%d, D6=%d, D7=%d\n", data[0], data[1], data[2], data[3]);
        // 2. Calculate Standard Hamming Parity Bits (Even Parity)
        p1 = data[0] ^ data[1] ^ data[3]; // Checks positions 1, 3, 5, 7
        p2 = data[0] ^ data[2] ^ data[3]; // Checks positions 2, 3, 6, 7
        p4 = data[1] ^ data[2] ^ data[3]; // Checks positions 4, 5, 6, 7
        // Build the first 7 bits of the codeword
        codeword[0] = p1;      // Pos 1
        codeword[1] = p2;      // Pos 2
        codeword[2] = data[0]; // Pos 3 (D3)
        codeword[3] = p4;      // Pos 4
        codeword[4] = data[1]; // Pos 5 (D5)
        codeword[5] = data[2]; // Pos 6 (D6)
        codeword[6] = data[3]; // Pos 7 (D7)
        // Calculate Global Parity Bit (Pos 8) across all 7 bits
        p8 = 0;
        for (i = 0; i < 7; i++) {
            p8 ^= codeword[i];
        }
        codeword[7] = p8; // Pos 8 (Global Guard)
        printf("Generated 8-bit Codeword: ");
        for (i = 0; i < 8; i++) printf("%d", codeword[i]);
        printf("\n");
        // Copy to receiver array before simulation
        for (i = 0; i < 8; i++) {
            received[i] = codeword[i];
        }
        // 3. Inject Errors based on your previous menu choice
        if (error_choice == 1) {
            bit1 = rand() % 8;
            received[bit1] ^= 1; // Flip exactly one random bit
            printf(">> Simulation: Flipped bit at position %d\n", bit1 + 1);
        }
        else if (error_choice == 2) {
            bit1 = rand() % 8;
            bit2 = rand() % 8;
            while (bit1 == bit2) {
                bit2 = rand() % 8; // Ensure two unique positions
            }
            received[bit1] ^= 1; // Flip first bit
            received[bit2] ^= 1; // Flip second bit
            printf(">> Simulation: Flipped bits at positions %d and %d\n", bit1 + 1, bit2 + 1);
        }
        else {
            printf(">> Simulation: Transmitting clean codeword data.\n");
        }
        printf("Received Codeword Data:   ");
        for (i = 0; i < 8; i++) printf("%d", received[i]);
        printf("\n");
        // 4. Receiver Side: Check Integrity
        // Calculate Syndrome bits using the first 7 positions
        s1 = received[0] ^ received[2] ^ received[4] ^ received[6]; // C1 ^ C3 ^ C5 ^ C7
        s2 = received[1] ^ received[2] ^ received[5] ^ received[6]; // C2 ^ C3 ^ C6 ^ C7
        s4 = received[3] ^ received[4] ^ received[5] ^ received[6]; // C4 ^ C5 ^ C6 ^ C7
        syndrome = (s4 << 2) | (s2 << 1) | s1; // Decimal position pointer
        // Calculate Global Parity Check across all 8 positions
        global_check = 0;
        for (i = 0; i < 8; i++) {
            global_check ^= received[i];
        }
        printf("Syndrome calculated:       %d\n", syndrome);
        printf("Global Parity Check bit:   %d\n", global_check);
        // 5. SECDED Decision Rules Matrix
        if (syndrome == 0 && global_check == 0) {
            printf("Result: SUCCESS! No errors detected for this block.\n");
        }
        else if (syndrome != 0 && global_check != 0) {
            printf("Result: 1-Bit Error Detected at position %d.\n", syndrome);
            received[syndrome - 1] ^= 1; // Auto-correct the bit
            printf("Fixed Codeword data:      ");
            for (i = 0; i < 8; i++) printf("%d", received[i]);
            printf("\n");
        }
        else if (syndrome != 0 && global_check == 0) {
            printf("Result: CRITICAL WARNING! A 2-Bit (Double) Error was detected!\n");
            printf("        Data uncorrectable. Re-transmission required.\n");
        }
        else {
            printf("Result: Only the Global Parity Bit (Pos 8) itself was flipped.\n");
        }
    }
    return 0;
}
