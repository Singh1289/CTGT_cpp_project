/*
    write a program to take a input and create a single linked list then remove dublicates from the list while traversing only once.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


int idx = 0;

int table_size = 10007;

int hashFunction(int key)
{
    return key % table_size;
}

void createArray(int *array, char *input)
{
    int temp ;
    char *token = strtok(input, " ");
    while (token != NULL)
    {
       
        if (strncmp(token, "0x", 2) == 0 || strncmp(token, "0X", 2) == 0)
        {          
            array[idx++] = (int)strtol(token, NULL, 16);
        }
        else if (strncmp(token, "null", 4) == 0 || strncmp(token, "->", 2) == 0 || strncmp(token, "NULL", 4) == 0)
        {
        }
        else 
        {
            array[idx++] = atoi(token);
        }
        token = strtok(NULL, " ");
    }
}

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int temp)
{
    // allocating memory new node
    Node *newNode = (Node *)malloc(1 * sizeof(Node));
    if (newNode == NULL)
    {
        printf("\nFailed to allocate memory to new node.");
        return 0;
    }

    newNode->data = temp;
    newNode->next = NULL;
    return newNode;
}

// add a node to the last in linked list
void insertLast(Node **head, int data)
{
    Node *newNode = createNode(data);

    if (*head == NULL)
    {
        *head = newNode;
        // printf("\nData added successfully.");
        return;
    }

    Node *iter = *head;
    while (iter != NULL)
    {
        if (iter->next == NULL)
        {
            iter->next = newNode;
            iter = NULL;
            return;
        }
        iter = iter->next;
    }
}

void display(Node *head)
{
    if (head == NULL)
    {
        printf("null");
        return;
    }

    Node *iter = head;
    while (iter != NULL)
    {
        printf("%d -> ", iter->data);
        iter = iter->next;
    }
    printf("null\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void removeDuplicates(Node **head)
{
    int mapCount[5000] = {0};

    Node *iter = *head;
    Node *prev = NULL;
    while (iter != NULL)
    {

        int num = hashFunction(iter->data);
        if (num < 0 && mapCount[num] == 1)
        {
            num *= -1;
            mapCount[num] = 0;
        }
        if (mapCount[num] == 1)
        {
            Node *temp = iter->next;
            prev->next = temp;
            free(iter);
            iter = prev;
        }
        else{
            mapCount[num] = 1;
            prev = iter;
        }

        prev = iter;
        iter = iter->next;
    }
}
// 5 -> 4 -> 3 -> 2 -> 1 -> 5 -> 4 -> 6 -> 7 -> 3 -> 2 -> 8 -> 9 -> 10 -> null

void main()
{
    Node *head = NULL;
    char inputString[1024];
    printf("Enter the input number string : ");
    fgets(inputString, sizeof(inputString), stdin);

    int arr[100];

    createArray(arr, inputString);

    for (int i = 0; i < idx; i++)
    {
         //printf("%d ", arr[i]);
        insertLast(&head, arr[i]);
    }

    printf("Original Linked List: ");
    display(head);

    removeDuplicates(&head);

    printf("Filtered Linked List: ");
    display(head);

    freeList(head);
}
