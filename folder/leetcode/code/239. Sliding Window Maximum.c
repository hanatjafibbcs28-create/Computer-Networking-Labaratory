#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    // The number of sliding windows is numsSize - k + 1
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    
    // Array to simulate the deque storing indices
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int head = 0; // Front of the deque
    int tail = 0; // Back of the deque
    
    for (int i = 0; i < numsSize; i++) {
        // 1. Remove indices that are out of the current window boundary
        if (head < tail && deque[head] <= i - k) {
            head++;
        }
        
        // 2. Remove elements smaller than the current element from the back
        while (head < tail && nums[deque[tail - 1]] <= nums[i]) {
            tail--;
        }
        
        // 3. Add the current element's index to the back
        deque[tail++] = i;
        
        // 4. The window is fully formed when index i reaches at least k - 1
        if (i >= k - 1) {
            result[i - k + 1] = nums[deque[head]];
        }
    }
    
    // Free the temporary deque memory
    free(deque);
    
    return result;
}
