
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNT 1003
#define INT_HASH 1003

typedef struct
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
        return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertFirst(Node **head, int data)
{
    Node *newNode = createNode(data);
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

void printList(Node **head)
{
    if (*head == NULL)
    {
        printf("NULL\n");
        return;
    }
    Node *iter = *head;
    while (iter != NULL)
    {
        printf("%d -> ", iter->data);
        iter = iter->next;
    }
    printf("\n");
}

Node* HashTable[MAX_COUNT] = {NULL};

int hashFunctionInteger(int key)
{
    int a = key % 1003;
    return (a*a) % 1003;
}

int isAvilableInHashTable(int key)
{
    int index = hashFunctionInteger(key);
    if (HashTable[index] == NULL)
        return 1;
    Node *iter = HashTable[index];
    while (iter != NULL)
    {
        if (iter->data == key)
            return 0;
        iter = iter->next;
    }
    return 1;
}

void insertIntoHashTable(int key)
{
    int index = hashFunctionInteger(key);
    insertFirst(&HashTable[index], key);
}

void main()
{
    int array[] = {1003, 1000,1002, 1001, 100};
    int size = sizeof(array) / sizeof(array[0]);

    
    for (int i = 0; i < size; i++)
    {
        if (isAvilableInHashTable(array[i]))
            insertIntoHashTable(array[i]);
        else
            insertIntoHashTable(array[i]);
    }

    //printing hash table
    for(int i = 0; i < MAX_COUNT; i++)
    {
        printf("%d -> ", i);
        printList(&HashTable[i]);
    }
}