#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100003 // A prime number close to constraints for fewer collisions

// A lightweight hash table node structure
typedef struct HashNode {
    int key;
    struct HashNode* next;
} HashNode;

// Simple function to insert a prefix into the hash table
void insertHash(HashNode** hashTable, int prefix) {
    int index = abs(prefix) % HASH_SIZE;
    HashNode* curr = hashTable[index];
    
    // Check if the prefix is already in the hash table to avoid duplicates
    while (curr != NULL) {
        if (curr->key == prefix) return;
        curr = curr->next;
    }
    
    // Insert new node at the head of the bucket list
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = prefix;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Simple function to search for a prefix in the hash table
int searchHash(HashNode** hashTable, int prefix) {
    int index = abs(prefix) % HASH_SIZE;
    HashNode* curr = hashTable[index];
    while (curr != NULL) {
        if (curr->key == prefix) return 1;
        curr = curr->next;
    }
    return 0;
}

// Function to free the hash table memory efficiently
void freeHash(HashNode** hashTable) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* curr = hashTable[i];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
}

int findMaximumXOR(int* nums, int numsSize) {
    int maxXOR = 0;
    int mask = 0;
    
    // Allocate the bucket array on the heap once
    HashNode** hashTable = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));

    // Iterate from the most significant bit down to the least significant bit
    for (int i = 30; i >= 0; i--) {
        // The mask keeps prefixes from bit 30 down to bit i
        mask |= (1 << i);
        
        // We greedily guess if the i-th bit can be set to 1 in our final maximum XOR
        int greedyCandidate = maxXOR | (1 << i);
        
        // Clear out the previous iteration's hash table chains quickly
        for (int j = 0; j < HASH_SIZE; j++) {
            HashNode* curr = hashTable[j];
            while (curr != NULL) {
                HashNode* temp = curr;
                curr = curr->next;
                free(temp);
            }
            hashTable[j] = NULL;
        }
        
        // Step 1: Store the prefixes of all numbers up to the current bit position
        for (int j = 0; j < numsSize; j++) {
            insertHash(hashTable, nums[j] & mask);
        }
        
        // Step 2: Use the mathematical property of XOR: if A ^ B = C, then A ^ C = B
        for (int j = 0; j < numsSize; j++) {
            int prefix = nums[j] & mask;
            if (searchHash(hashTable, prefix ^ greedyCandidate)) {
                maxXOR = greedyCandidate;
                break; // Found a valid pair to support this bit, no need to look further
            }
        }
    }
    
    free(hashTable);
    return maxXOR;
}
