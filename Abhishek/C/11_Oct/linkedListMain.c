#include "LinkedList.h"
#include "LinkedList.c"

void main()
{
   
    LinkedList LL;
    LL.head = NULL;
    int n;
    do{
        printf("\n~~~~~~~~~~~~~~~~~~~");
        printf("\n 1. Add last");
        printf("\n 2. Add first");
        printf("\n 3. Display");
        printf("\n 4. Delete Last");
        printf("\n 5. Delete First");
       // printf("\n 6. Length of list");
        printf("\n 6. Exit");
        printf("\n~~~~~~~~~~~~~~~~~~~");

        while(TRUE)
        {
            printf("\nEnter choice : ");
            if (scanf("%d", &n) == 1) break;
                
            printf("\nTry again..! ");
        }
        switch (n)
        {
        case 1: insertLast(&LL.head,takeInput());
                break;
        
        case 2: insertFirst(&LL.head,takeInput());
                break;
        
        case 3: display(LL.head);
                break;
        
        case 4: deleteLast(&LL.head);
                break;

        case 5: deleteFirst(&LL.head);
                break;

        // case 6: printf("\nLength of Linked List : %d",length);
        //         break;
        
        default:printf("\nEnter from the list.");
                break;
        }
 
    }while(n!=6);
    freeList(&LL.head);
    printf("\n~~~ See you next time ~~~~");
}