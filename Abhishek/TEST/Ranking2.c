/*
Problem: Given an array of n integers, replace each element in the array with its corresponding rank. (The rank of an element is determined by its position. For example, the minimum element in the array will have a rank of 1, the second minimum element will have a rank of 2, and so on.)
Example: Input: {10, 8, 15, 12, 6, 20, 1}
Output:           {4, 3, 6, 5, 2, 7, 1}
Input: {100, 200, 300, 400}
Output: {1, 2, 3, 4}
Input: An array of integers (0 ≤ len(array) ≤ 10^7) as given in examples
Output: An array of ranks corresponding to each element in the original array as given in examples

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAX_SIZE 10000
int minNum = INT_MAX;

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
        if(L[i]< minNum) minNum = L[i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
        if(R[j]< minNum) minNum = R[j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{

    if (left < right)
    {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void printRank(int array[], int idx)
{
    printf("\nOutput: {");
    for (int i = 0; i < idx; i++)
    {
        // code
        if (i != idx - 1)
            printf(", ");
    }
    printf("}\n");
}

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
        if (str[i] == ' ' || str[i] == ',')
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

        else if ((str[i] == '-' && isdigit(str[i + 1])) || isdigit(str[i]))
        {
            while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}')
                temp[j++] = str[i++];
        }
        else if (str[i] == '\'' && isalpha(str[i + 1]) && str[i + 2] == '\'')
        {
            arr[*idx] = str[i + 1];
            (*idx)++;
            i += 3;
            continue;
        }
        temp[j] = '\0';

        if (j > 0)
        {
            arr[*idx] = convertIntoDecimal(temp);
            (*idx)++;
        }
    }
}

int checkDublicates(int arr[],int idx, int mid, int key){
    int i = mid-1;
    while(1){
        if(arr[i] != key){
            arr[i+1] = minNum;
            return i+1;
        }
        i--;
    }
}

int binarySearch(int arr[], int idx, int key)
{
    int left = 0;
    int right = idx - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
        {       
            mid = checkDublicates(arr, idx, mid, key);
            return mid + 1;
        }
        else if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

void computeRank(int sorted[], int arr[], int idx)
{
    printf("Output : {");
    for (int i = 0; i < idx; i++)
    {
        printf("%d", binarySearch(sorted, idx, arr[i]));
        if (i != idx - 1)
            printf(", ");
    }
    printf("}");
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
        printf("\nInvalid Input.\n");
        return -1;
    }

    int oldArr[idx];

    memcpy(oldArr, inputArr, idx * sizeof(int));

    mergeSort(inputArr, 0, idx - 1);

    // printf("sorted: ");
    // for (int i = 0; i < idx; i++)
    // {
    //     printf("%d ", inputArr[i]);
    // }
    // printf("\n");
    minNum--;
    computeRank(inputArr, oldArr, idx);

    // printRank(oldArr, idx);

    // {'a', 'b', 'c'}

    return 0;
}
