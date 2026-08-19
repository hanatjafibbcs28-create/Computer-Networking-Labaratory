int totalHammingDistance(int* nums, int numsSize) {
    int total = 0;
    for (int i = 0; i < 32; i++) { // Changed 31 to 32 to cover all bits
        int count = 0;
        for(int j = 0; j < numsSize; j++) {
            count += ((nums[j] >> i) & 1);
        }
        total += count * (numsSize - count);
    }
    return total;
}
