int reverseBits(int n) {
    unsigned int num = (unsigned int)n;
    num = ((num >> 1) & 0x55555555) | ((num & 0x55555555) << 1);
    num = ((num >> 2) & 0x33333333) | ((num & 0x33333333) << 2);
    num = ((num >> 4) & 0x0F0F0F0F) | ((num & 0x0F0F0F0F) << 4);
    num = ((num >> 8) & 0x00FF00FF) | ((num & 0x00FF00FF) << 8);
    num = (num >> 16) | (num << 16);
    return (int)num;
}
