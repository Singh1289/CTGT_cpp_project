#include "MyStack.h"
//#include"LinkedList.h"

int isEmpty(MyStack *stack)
{
    return (stack->top == NULL) ? 1 : 0;
}

void push(MyStack *stack,int data)
{
    insertFirst(&stack->top,data);
}

int peek(MyStack *stack)
{
   // printf("check for data: %d : %d", stack->top->data, isEmpty(stack));
    return (isEmpty(stack)) ? -1 : stack->top->data;
}

int pop(MyStack *stack)
{
    int res;
    if(isEmpty(stack))
        return -1; 
    else
    {
        res = peek(stack);
        deleteFirst(&stack->top);
        return res;
    }
}
