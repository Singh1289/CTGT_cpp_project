/*
Problem: Given an array of n integers, replace each element in the array with its corresponding rank. (The rank of an element is determined by its position. For example, the minimum element in the array will have a rank of 1, the second minimum element will have a rank of 2, and so on.)
Example: Input: {10, 8, 15, 12, 6, 20, 1}
Output:           {4, 3, 6, 5, 2, 7, 1}
Input: {100, 200, 300, 400}
Output: {1, 2, 3, 4}
Input: An array of integers (0 ≤ len(array) ≤ 10^7) as given in examples
Output: An array of ranks corresponding to each element in the original array as given in examples
use hashing to compute and store rank in a table
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100000
#define MAX_COUNT 1003

int rank = 1;

typedef struct Node
{
    int data;
    int count;
    int rank;
    struct Node *next;
} Node;

Node *HashTable[MAX_COUNT] = {NULL};

Node *createNode(int data, int rank)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
        return NULL;
    newNode->data = data;
    newNode->rank = rank;
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

void insert(Node **head, int data, int rank)
{
    Node *newNode = createNode(data, rank);
    if (!newNode)
    {
        printf("createNode failed\n");
        return;
    }

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    Node *iter = *head;
    while (iter->next != NULL)
        iter = iter->next;
    iter->next = newNode;
}

void update(Node **head, int data)
{
    Node *iter = *head;
    while (iter != NULL)
    {
        if (iter->data == data)
        {
            iter->count++;
            iter->rank = rank++;
            return;
        }
        iter = iter->next;
    }
}

int hashFunctionInteger(int key)
{
    int a = key % 1003;
    return (a * a) % 1003;
}

int isAvailableInHashTable(int key)
{
    int index = hashFunctionInteger(key);
    if (HashTable[index] == NULL)
        return 0;

    Node *iter = HashTable[index];
    while (iter != NULL)
    {
        if (iter->data == key)
            return 1;
        iter = iter->next;
    }
    return 0;
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);         
        mergeSort(arr, mid + 1, right); 

        merge(arr, left, mid, right);      
    }
}

void computeRank(int *array, int idx)
{
    for (int i = 0; i < idx; i++)
    {
        int index = hashFunctionInteger(array[i]);
        if (isAvailableInHashTable(array[i]))
            update(&HashTable[index], array[i]);
        else
            insert(&HashTable[index], array[i], rank++);
    }
}

void printRank(int array[], int idx)
{
    printf("\nOutput: {");
    for (int i = 0; i < idx; i++)
    {
        Node *iter = HashTable[hashFunctionInteger(array[i])];
        while (iter != NULL)
        {
            if (iter->data == array[i])
            {
                if(iter->count > 1){
                    printf("%d", iter->rank - iter->count +1);
                    iter->count--;
                }else
                    printf("%d", iter->rank);
                break;
            }
            iter = iter->next;
        }
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

int main()
{
    char buf[MAX_SIZE];
    printf("Input: ");
    fgets(buf, MAX_SIZE, stdin);
    buf[strcspn(buf, "\n")] = '\0';

    int inputArr[MAX_SIZE];
    int idx = 0;

    convert(buf, inputArr, &idx);

    if(idx == 0){
        printf("\nInvalid Input.\n");
        return -1;
    }

    int outputArr[idx];

    memcpy(outputArr, inputArr, idx * sizeof(int));

    mergeSort(inputArr, 0, idx - 1);

    // printf("sorted: ");
    // for (int i = 0; i < idx; i++)
    // {
    //     printf("%d ", inputArr[i]);
    // }
    // printf("\n");

    computeRank(inputArr, idx);

    printRank(outputArr, idx);

// {'a', 'b', 'c'}

    return 0;
}
