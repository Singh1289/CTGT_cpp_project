
#include"LinkedList.h"

int takeInput()
{
    int temp;
    while(TRUE){
        printf("\nEnter integer data: ");
        if (scanf("%d", &temp) == 1) break;
    
        printf("\nPlease enter an integer.");    
    }
    return temp;
}

Node* createNode(int temp)
{
        // allocating memory new node
    Node *newNode= (Node *)malloc(1*sizeof(Node));
    if(newNode==NULL)
    {
        printf("\nFailed to allocate memory to new node.");
        return 0;
    }

    newNode->data= temp;
    newNode->next= NULL;
    return newNode;
}

void insertLast(Node **head,int data)
{
    Node *newNode = createNode(data);
    
    if(*head == NULL) 
    {
        *head = newNode; 
        printf("\nData added successfully.");
        return;
    }

    Node *iter = *head;
    while(iter != NULL)
    {
        if(iter->next == NULL)
        {
            iter->next = newNode;
            printf("\nData added successfully.");
            iter=NULL;
            return;
        }
        iter = iter->next;
    }
    
}

void insertFirst(Node **head,int data)
{
    Node *newNode = createNode(data);
    
    if(*head== NULL)
        *head = newNode;
    else
    {
        newNode->next = *head;
        *head = newNode; 
    }    
    //printf("\nNew Node added successfully. %d : %d : %d: head: %d",newNode,newNode->data,newNode->next,head);  
}

void display(Node *head)
{
    if(head == NULL)
    {
        printf("\nlinkedList is empty.");
        return;
    }

    Node *iter = head;
    printf("\n~~~~ Printing Nodes ~~~~\n");
    while(iter != NULL)
    {
        printf("-> %d ",iter->data);
        iter = iter->next;
    }
    
} 

void deleteLast(Node **head)
{
    if(*head == NULL)
    {
        printf("\nlinkedList is empty.");
        return;
    }
    
    if((*head)->next == NULL)
    {
        free(*head);
        *head= NULL;
         
        printf("\nlinkedList is empty.");
        return;
    }

    Node *iter = *head;
    while(iter->next != NULL)
    {
        if(iter->next->next == NULL)
        {
            free(iter->next);
            iter->next= NULL;
            printf("\nNode deleted Successfully.");
            iter = NULL;
            return;
        }
        iter = iter->next;
    }   
}

void deleteFirst(Node **head)
{
    if(*head == NULL)
    {
        printf("\nlinkedList is empty.");
        return;
    }

    Node *iter = *head;
    *head = iter->next;
    free(iter);
    printf("\nNode deleted Successfully.");
    
    iter=NULL;
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

