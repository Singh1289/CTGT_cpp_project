#include <stdio.h>


int hammingDistance(int x, int y) {
    int xor = x ^ y;  
    int distance = 0;
    
   
    while (xor > 0) {
        distance += xor & 1;  
        xor >>= 1;            
    }
    return distance;
}
int calculateHammingDistance(int a, int b) {
    // XOR the two integers
    int xorResult = a ^ b;
    int hammingDistance = 0;

    // Count number of 1's in the XOR result
    while (xorResult != 0) {
        hammingDistance += xorResult & 1;  // If last bit is 1, increment counter
        xorResult >>= 1;  // Right shift by 1 to check next bit
    }

    return hammingDistance;
}

int main() {
    int x= -1, y= 4;
    
    int distance = hammingDistance(x, y);
    printf("Hamming distance: %d\n", distance);

    return 0;
}
