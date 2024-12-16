#include "MyStack.h"
#include "MyStack.c"

void main()
{
    MyStack stack;
    stack.top = NULL;

    int n,t;
    do{
        printf("\n~~~~~~~~~~~~~~~~~~~");
        printf("\n 1. Push");
        printf("\n 2. Pop");
        printf("\n 3. Peek");
        printf("\n 4. display");
        printf("\n 5. Exit");
        printf("\n~~~~~~~~~~~~~~~~~~~");

        while(TRUE)
        {
            printf("\nEnter choice : ");
            if (scanf("%d", &n) == 1) break;
                
            printf("\nTry again..! ");
        }
        switch (n)
        {

        case 1: push(&stack,takeInput());
                break;
        
        case 2: if((t = pop(&stack)) == -1)
                    printf("\nStack is Empty");
                else
                    printf("\nPoped: %d",t);
                break;
        
        case 3: if((t = peek(&stack)) == -1)
                    printf("\nStack is Empty");
                else
                    printf("\nTop: %d",t);
                break;
        
        case 4: display(stack.top);
                break;
        
        default:printf("\nEnter from the list.");
                break;
        }
 
    }while(n!=6);
    freeList(stack.top);
    printf("\n~~~ See you next time ~~~~");
}