//hammingDistance
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STR 1000
int arr[3];
int idx = 0;

void trim(char* str) {
    int start = 0, end = strlen(str) - 1, idx = 0;

    while (str[start] == ' ') {
        start++;
    }

    while (end >= start && str[end] == ' ') {
        str[end] = '\0';
        end--;
    }

    while (str[start] != '\0') {
        str[idx++] = str[start++];
    }
    str[idx] = '\0';
}

int convertToInteger(const char* str) {
    if (isalpha(str[0]) && str[1] == '\0') {
        return str[0];
    }

    int decimal = 0;
    if (strncmp(str, "0x", 2) == 0 || strncmp(str, "0X", 2) == 0) {
        decimal = (int)strtoul(str, NULL, 16);
    } else if (str[0] == '0' && str[1] != 'x' && str[1] != 'X') {
        decimal = (int)strtol(str, NULL, 8);
    } else {
        decimal = (int)strtol(str, NULL, 10);
    }

    return decimal;
}

void extractValue(char* str) {
    int i = 0;
    char temp[20];

    if (str[0] == '{')
        str++;

    while (str[i] != '\0' && str[i] != '}') {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '{' || str[i] == '\'') {
            i++;
            continue;
        }

        int j = 0;
        while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}' && str[i] != '\'') {
            temp[j++] = str[i++];
        }
        temp[j] = '\0';

        if (j > 0) {
            arr[idx] = convertToInteger(temp);
            idx++;
        }
    }
}

void printDistance(int n) {
    int count = 0;
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
       // printf("%d", bit);
        if(bit == 1) count++;

        if (i % 4 == 0) {
           // printf(" ");
        }
    }
    printf("\nOutput: %d",count);
}

int main() {
    char in[MAX_STR];
    printf("Enter values: ");
    fgets(in, MAX_STR, stdin);
    in[strcspn(in, "\n")] = '\0';

    trim(in);

    if (strlen(in) < 1) {
        printf("Invalid Input..!");
        exit(-1);
    }

    extractValue(in);

    arr[2] = arr[0] ^ arr[1];
   
    

    printf("\nOutput:\n");
    for (int i = 0; i <3; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printDistance(arr[2]);
    return 0;
}
