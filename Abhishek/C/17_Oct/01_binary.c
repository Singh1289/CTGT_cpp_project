/*
    Program to read a binary file that store multi-byte integers in a specific format. 
    Task is to implement a function that reads these integers from the file, correctly 
    handling the endianness of the system on which the program is running and convert 
    the contents of the file so that it can be used on an incompatible platform. The 
    program should implement a function to read a 4-byte integer from a binary file and 
    correctly interpret it based on the system's endianness. Ensure that the program 
    correctly handles both little-endian and big-endian formats.
*/

#include <stdio.h>

int checkSystemEndianness() {
    unsigned int i = 1;
    char* ch = (char*)&i;
    return (*ch) ? 1 : 0;  
}

void printBinary(unsigned int num) {
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}

unsigned int convertToLittleEndian(unsigned int num) {
    return ((num & 0x000000FF) << 24) | ((num & 0x0000FF00) << 8) |
           ((num & 0x00FF0000) >> 8) | ((num & 0xFF000000) >> 24);
}

unsigned int convertToBigEndian(unsigned int num) {
    return convertToLittleEndian(num); 
}

int main() {
    FILE* inputFile;
    unsigned int num, convertedNum;
    int n;

    
    inputFile = fopen("binaryFile.bin", "wb");
    if (!inputFile) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    printf("Enter number of integers to write to file: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        fwrite(&num, sizeof(unsigned int), 1, inputFile);
    }
    fclose(inputFile);

    // Reading and converting each integer from binary file
    inputFile = fopen("binaryFile.bin", "rb");
    if (!inputFile) {
        printf("Error opening file for reading.\n");
        return 1;
    }

    printf("\nReading and converting integers from file:\n");
    int isLittleEndian = checkSystemEndianness();
    for (int i = 0; i < n; i++) {
        fread(&num, sizeof(unsigned int), 1, inputFile);

        if (isLittleEndian) {
            convertedNum = convertToLittleEndian(num); 
            printf("Original (little-endian): %d\nIn binary: ", num);
            printBinary(num);
            printf("Converted to big-endian: %d\nIn binary: ", convertedNum);
            printBinary(convertedNum);
        } else {
            convertedNum = convertToBigEndian(num);  
            printf("Original (big-endian): %d\nIn binary: ", num);
            printBinary(num);
            printf("Converted to little-endian: %d\nIn binary: ", convertedNum);
            printBinary(convertedNum);
        }
        printf("\n");
    }

    fclose(inputFile);
    return 0;
}
