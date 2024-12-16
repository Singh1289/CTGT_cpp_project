// integer convert each byte into a number and then add

#include <stdio.h>
#include <stdint.h>
//Folding Method of hashing
// in this we divide the number -> add -> modulo
int sumOfBytes(int num) {
    // Extract each byte by shifting and masking
    int byte1 = (num & 0xFF);        
    int byte2 = (num >> 8) & 0xFF;   
    int byte3 = (num >> 16) & 0xFF; 
    int byte4 = (num >> 24) & 0xFF; 
    return byte1 + byte2 + byte3 + byte4;
}

void printBinary(int num)
{
    int mask = 1 << 7;
    for (int j = 0; j < 8; j++) {
        printf("%d", (num & mask) >> (7 - j));
        mask >>= 1;
    }
    printf("\n");
}

void main()
{
    int i = -2147483647;
    printf("Sum of bytes in 0xff: %d\n", sumOfBytes(i));
    printBinary(i);

}