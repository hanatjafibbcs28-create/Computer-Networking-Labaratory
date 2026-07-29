#include <stdlib.h>
#include <string.h>
#define HASH_SIZE 1000003
typedef struct {
    int* table;
    int size;
} HashSet;
HashSet* createHashSet() {
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    set->table = (int*)malloc(HASH_SIZE * sizeof(int));
    memset(set->table, -1, HASH_SIZE * sizeof(int));
    set->size = 0;
    return set;}
int insert(HashSet* set, int val) {
    unsigned int hash = (unsigned int)val % HASH_SIZE;
    while (set->table[hash] != -1) {
        if (set->table[hash] == val) {
            return 0;}
        hash = (hash + 1) % HASH_SIZE;}
    set->table[hash] = val;
    set->size++;
    return 1;}
void freeHashSet(HashSet* set) {
    free(set->table);
    free(set);}
int subarrayBitwiseORs(int* arr, int arrSize) {
    if (arrSize <= 0) return 0;
    HashSet* global_set = createHashSet();
    int current_window[32];
    int current_size = 0;
    for (int i = 0; i < arrSize; i++) {
        int current_val = arr[i];
        int next_window[32];
        int next_size = 0;
        next_window[next_size++] = current_val;
        insert(global_set, current_val);
        for (int j = 0; j < current_size; j++) {
            int combined_or = current_window[j] | current_val;
            if (combined_or != next_window[next_size - 1]) {
                next_window[next_size++] = combined_or;
                insert(global_set, combined_or); } }
        current_size = next_size;
        memcpy(current_window, next_window, next_size * sizeof(int));}
    int total_distinct = global_set->size;
    freeHashSet(global_set);
    return total_distinct;}
