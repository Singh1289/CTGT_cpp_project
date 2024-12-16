#ifndef MY_STACK_H
#define MY_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "LinkedList.c"

typedef struct MyStack 
{
    struct Node *top;
}MyStack;

int isEmpty(MyStack *stack);
void push(MyStack *stack,int data);
int pop(MyStack *stack);
int peek(MyStack *stack);


#endif