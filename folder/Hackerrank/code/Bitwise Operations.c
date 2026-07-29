#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void calculate_the_maximum(int n, int k) {
    int max_and = 0;
    int max_or = 0;
    int max_xor = 0;
    
    // Outer loop picks the first number 'a'
    for (int a = 1; a < n; a++) {
        // Inner loop picks the second number 'b' ensuring a < b
        for (int b = a + 1; b <= n; b++) {
            
            // Calculate bitwise operations
            int current_and = a & b;
            int current_or  = a | b;
            int current_xor = a ^ b;
            
            // Update AND maximum if it's less than the threshold k
            if (current_and < k && current_and > max_and) {
                max_and = current_and;
            }
            
            // Update OR maximum if it's less than the threshold k
            if (current_or < k && current_or > max_or) {
                max_or = current_or;
            }
            
            // Update XOR maximum if it's less than the threshold k
            if (current_xor < k && current_xor > max_xor) {
                max_xor = current_xor;
            }
        }
    }
    
    // Print the final maximum values each on a new line
    printf("%d\n", max_and);
    printf("%d\n", max_or);
    printf("%d\n", max_xor);
}

int main() {
    int n, k;
  
    if (scanf("%d %d", &n, &k) == 2) {
        calculate_the_maximum(n, k);
    }
    
    return 0;
}
