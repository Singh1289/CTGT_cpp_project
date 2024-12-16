#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAX_SIZE 100000
int IDX = 0;

int isBinary(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '0' && str[i] != '1')
            return 0;
    }
    return 1;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int validateInput(char *input)
{
    if (strlen(input) == 0 || strspn(input, " ") == strlen(input))
    {
        return 0;
    }
    return 1;
}

void convertArray(char *str, int arr[], int *idx)
{
    char *token = strtok(str, "{, }");
    while (token != NULL)
    {
        if (strncmp(token, " 0x", 3) == 0 || strncmp(token, " 0X", 3) == 0)
        {
            arr[(*idx)++] = (int)strtoul(token, NULL, 16);
        }
        else if (isBinary(token))
        {
            arr[(*idx)++] = (int)strtol(token, NULL, 2);
        }
        else if (strlen(token) == 1 && isalpha(token[0]))
        {
            arr[(*idx)++] = (int)token[0];
        }
        else
        {
            arr[(*idx)++] = atoi(token);
        }
        token = strtok(NULL, "{, }");
    }
}

int compareArray(const void *a, const void *b)
{
    int int_a = *(int *)a;
    int int_b = *(int *)b;

    if (int_a < int_b)
    {
        return -1;
    }
    else if (int_a > int_b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void removeDuplicates(int arr[], int *n)
{
    if (*n == 0 || *n == 1)
        return;

    qsort(arr, *n, sizeof(int), compareArray);

    int j = 0;
    for (int i = 0; i < *n - 1; i++)
    {
        if (arr[i] != arr[i + 1])
        {
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[*n - 1];
    *n = j;
}

void rearrange_array(int *arr, int idx)
{
    for (int i = 1; i < idx ; i+=2)
    {
       swap(&arr[i], &arr[i - 1]);
    }
}

int checkModified(int *arr, int *old, int idx)
{
    int mod = 0;
    for (int i = 0; i < idx; i++)
    {
        if (arr[i] != old[i])
            mod++;
    }

    return mod;
}

void printArray(int arr[], int idx)
{
    printf("Output: {");
    for (int i = 0; i < idx; i++)
    {
        printf("%d", arr[i]);
        if (i < idx - 1)
            printf(", ");
    }
    printf("}\n");
}

int main()
{
    char str[10000];

    printf("Input: ");
    fgets(str, 10000, stdin);
    str[strcspn(str, "\n")] = '\0';

    int arr[MAX_SIZE];
    int idx = 0;

    if (!validateInput(str))
    {
        printf("Invalid input\n");
        return -1;
    }

    convertArray(str, arr, &idx);

    int oldArr[idx];
    for (int i = 0; i < idx; i++)
    {
        oldArr[i] = arr[i];
    }

    removeDuplicates(arr, &idx);

    if (idx >= 2)
    {
        rearrange_array(arr, idx);
    }
    else
    {
        printf("Error: no second element can be greater than both its left and right neighbors\n");
        return -1;
    }

    int check = checkModified(arr, oldArr, idx);
    if (check == 0)
    {
        printf("Error: no need to rearrange the array\n");
    }
    else
    {
        printArray(arr, idx);
    }

    return 0;
}
