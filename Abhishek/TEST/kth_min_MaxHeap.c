/*
Problem: Given an array of n integers, find the kth smallest element
in the array using a heap data structure
Example: Input:
Array: {1, 3, 4, 5, 6, 7, 9}
k = 2
Output: kth smallest element = 3
Input:
Array: {10, 4, 5, 8, 20, 3, 1}
k = 1
Output: kth smallest element = 1
Input:
1. An array of integers (0 ≤ len(array) ≤ 10^6)
2. A positive integer 'k' where k is the index of
the smallest element you need to find
Output: kth smallest element in the array as per the format specified
in the examples
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000

int convertIntoDecimal(char *str)
{
    int decimal = 0;
    if (strncmp(str, "0x", 2) == 0 || strncmp(str, "0X", 2) == 0)
    {
        decimal = (int)strtoul(str, NULL, 16);
    }
    else if (str[0] == '0' && str[1] != 'x')
    {
        decimal = (int)strtol(str, NULL, 8);
    }
    else
    {
        decimal = (int)strtol(str, NULL, 10);
    }
    return decimal;
}

void convert(char *str, int *arr, int *idx)
{
    int i = 0;
    char temp[20];

    if (str[0] == '{')
        str++;

    while (str[i] != '\0' && str[i] != '}')
    {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '{')
        {
            i++;
            continue;
        }

        int j = 0;

        if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
        {
            while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}')
                temp[j++] = str[i++];
        }
        else if (str[i] == '0' && str[i + 1] != 'x')
        {
            while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}')
                temp[j++] = str[i++];
        }
        else if ((str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9')) || (str[i] >= '0' && str[i] <= '9'))
        {
            while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}')
                temp[j++] = str[i++];
        }
        temp[j] = '\0';

        if (j > 0)
        {
            arr[*idx] = convertIntoDecimal(temp);
            (*idx)++;
        }
    }
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

int kthSmallest(int arr[], int n, int k)
{
    
    for (int i = k / 2 - 1; i >= 0; i--)
        heapify(arr, k, i);

    
    for (int i = k - 1; i < n; i++)
    {
        if (arr[0] > arr[i])
        {
            swap(&arr[0], &arr[i]);
            heapify(arr, k, 0);
        }
    }

    return arr[0];
}

int main()
{
    char buf[MAX_SIZE];
    printf("Input: ");
    fgets(buf, MAX_SIZE, stdin);
    buf[strcspn(buf, "\n")] = '\0';

    int inputArr[MAX_SIZE];
    int idx = 0;

    convert(buf, inputArr, &idx);

    if (idx == 0)
    {
        printf("Invalid input\n");
        return -1;
    }

    int k;
    printf("Enter the value of k: ");
    scanf("%d", &k);

    if (k == 0 || k > idx - 1)
    {
        printf("Invalid value of k\n");
        return -1;
    }

    int res = kthSmallest(inputArr, idx, k);

    printf("The kth smallest element is: %d\n", res);
}
