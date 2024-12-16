/*
    Program to Find 
    (a) size of each primitive data type 
    (b) range of each primitive type   
*/

#include <stdio.h>

int main() {
    // For int
    signed int sIMin = -(1 << (sizeof(int) * 8 - 1));
    signed int sIMax = (1 << (sizeof(int) * 8 - 1)) - 1;
    unsigned int UIMax = (1 << (sizeof(int) * 8)) - 1;

    // For char
    char cMin = -(1 << (sizeof(char) * 8 - 1));
    char cMax = (1 << (sizeof(char) * 8 - 1)) - 1;
    unsigned char UCMax = (1 << (sizeof(char) * 8)) - 1;

    // For short
    signed short sSMin = -(1 << (sizeof(short) * 8 - 1));
    signed short sSMax = (1 << (sizeof(short) * 8 - 1)) - 1;
    unsigned short USMax = (1 << (sizeof(short) * 8)) - 1;

    // For long
    signed long sLMin = -(1L << (sizeof(long) * 8 - 1));
    signed long sLMax = (1L << (sizeof(long) * 8 - 1)) - 1;
    unsigned long ULMax = (1L << (sizeof(long) * 8)) - 1;

    // // For float
    // float fMin = -1.7014117E+38; 
    // float fMax = 1.7014117E+38;  

    // Print results
    printf("Signed int  %d to %d = 0x%X to 0x%X \n", sIMin, sIMax, sIMin, sIMax);
    printf("Unsigned int 0 to %d = 0 to 0x%X \n", UIMax, UIMax);

    printf("Signed char  %d to %d = 0x%X to 0x%X \n", cMin, cMax, cMin, cMax);
    printf("Unsigned char 0 to %d = 0 to 0x%X \n", UCMax, UCMax);

    printf("Signed short  %d to %d = 0x%X to 0x%X \n", sSMin, sSMax, sSMin, sSMax);
    printf("Unsigned short 0 to %d = 0 to 0x%X \n", USMax, USMax);

    printf("Signed long  %ld to %ld = 0x%lX to 0x%lX \n", sLMin, sLMax, sLMin, sLMax);
    printf("Unsigned long 0 to %ld = 0 to 0x%lX \n", ULMax, ULMax);

   // printf("Float min: %.7f, Float max: %.7f\n", fMin, fMax);

    return 0;
}
