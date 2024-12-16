#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>


typedef enum {FALSE,TRUE} boolean;

typedef struct Node
{
    int data;
    struct Node *next; 
}Node;

typedef struct LinkedList
{
    struct Node *head;
}LinkedList;

int takeInput();
Node* createNode();
void insertLast(Node **head, int data);
void insertFirst(Node **head, int data);
void display(Node *head);
void deleteLast(Node **head);
void deleteFirst(Node **head);
void freeList(Node* head);

#endif