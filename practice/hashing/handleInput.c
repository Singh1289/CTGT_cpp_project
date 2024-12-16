#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COUNT 10000

int isBinary(char *str) {
    if (strlen(str) < 8) return 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '0' && str[i] != '1') {
            return 0;
        }
    }
    return 1;
}

int convertTokenToInt(char *token) {
    int value = 0;

    // for hexadecimal
    if (strncmp(token, "0x", 2) == 0 || strncmp(token, "0X", 2) == 0) {
        value = (int)strtoul(token, NULL, 16);
    }
    // for binary
    else if (isBinary(token)) {
        value = (int)strtol(token, NULL, 2);
    }
    // for character
    else if (token[0] == '\'' && token[strlen(token) - 1] == '\'') {
        if (strlen(token) == 3) {
            value = (int)token[1];
        } else if (strlen(token) == 4 && token[1] == '\\') {
            if (token[2] == 'n') value = '\n';
            else if (token[2] == 't') value = '\t';
            else if (token[2] == '0') value = '\0';
            
        }
    }
    else {
        value = atoi(token);
    }

    return value;
}

int* parseStringToIntArray(char *str, int *size) {
    int *arr = malloc(MAX_COUNT * sizeof(int));
    int idx = 0;

    char *token = strtok(str, "[, ]");
    while (token != NULL) {
        arr[idx++] = convertTokenToInt(token);
        token = strtok(NULL, "[, ]");
    }

    *size = idx;  
    return arr;
}


int compareArray(const void *a, const void *b)
{
     int int_a = *(int *)a;
    int int_b = *(int *)b;

    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int main() { 
    char str[10000];
    int size = 0;

    printf("Input Array: ");
    fgets(str, 10000, stdin);
    str[strcspn(str, "\n")] = '\0';  // Remove newline character

    int *arr = parseStringToIntArray(str, &size);

    printf("Converted Integer Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");   

    qsort(arr, size, sizeof(arr[0]),(int (*)(const void *, const void *))compareArray);

    printf("Sorted Integer Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");  

    free(arr);
    return 0;
}
