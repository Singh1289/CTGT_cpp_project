/*
    Program to calculate the total customer bill based on the user's menu choices in a restaurant. 
    The program should allow the user to view a menu, select items (which are used to add to their bill), 
    and display the final total considering tax (e.g., 5% GST and 10% service tax) on the ordered items.

*/

#include<stdio.h>
#include <string.h>

#define GST 5
#define SERVICE_TAX 10
#define ITEM_COUNT 5

// defined structure for menu and order
struct Menu{
   char item[ITEM_COUNT][15];
   int price[ITEM_COUNT];
}Menu;

struct Order{
    int itemIndex[50];
    int itenQuatity[50];
    float total;
}Order;

// function declaration
void initializeMenu(struct Menu*);
void makeOrder();
void displayMenu(struct Menu*);
void placeOrder(struct Order*, struct Menu*, int*,int*);
void getBill(struct Order*, struct Menu*, int*);


int main()
{
    makeOrder();
    return 0;
}

// providing menu 
void initializeMenu(struct Menu *m)
{
    strcpy(m->item[0], "Tea");
    strcpy(m->item[1], "Coffee");
    strcpy(m->item[2], "Pav Bhaji");
    strcpy(m->item[3], "Pizza");
    strcpy(m->item[4], "Burger");

    m->price[0] = 15;
    m->price[1] = 25;
    m->price[2] = 60;
    m->price[3] = 90;
    m->price[4] = 50;
}

// to show menu in formated manner
void displayMenu(struct Menu *m)
{
    printf("\n%-2s %-15s %-10s", "No", "Item",  "Price");
    printf("\n---------------------------------");
    for(int i=0; i<ITEM_COUNT;i++)
        printf("\n%-2d %-15s %-10d",i+1,m->item[i],m->price[i]);
};

// to take order from user
void placeOrder(struct Order *ord, struct Menu *mm, int *choice, int* orderNum)
{
    int quantity;
    printf("Quantity: ");
    scanf("%d", &quantity);
    if (quantity > 0) { 
        ord->itemIndex[*orderNum] = *choice - 1;  
        ord->itenQuatity[*orderNum] = quantity;
        ord->total += mm->price[*choice - 1] * quantity;  
        (*orderNum)++;
    } else {
        printf("Invalid quantity. Please enter a positive number.\n");
    }
}

// genrate bill and calculate the GST
void getBill(struct Order *ord, struct Menu *mm ,int* orderNum )
{
    int ind,quan;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n      ~ B I L L ~            ");
    printf("\n%-2s %-15s %-10s %-10s", "No", "Item", "Quantity", "Price");
    printf("\n-----------------------------------");
    for(int i=0 ; i< *orderNum; i++)
    {
        ind = ord->itemIndex[i];
        quan = ord->itenQuatity[i];
    printf("\n%-2d %-15s %-10d %-10d",i+1, mm->item[ind],mm->price[ind],quan,(mm->price[ind] * quan));
    }
    printf("\n-----------------------------------");
    printf("\n   Total           : %.2f  ",ord->total);
    printf("\n   GST 5%%          : %.2f  ", (ord->total * GST)/100);
    printf("\n   Service Tax 10%% : %.2f  ",(ord->total * SERVICE_TAX)/100);
    printf("\n   Final bill      : %.2f  ", (ord->total + ((ord->total * GST)/100) + ((ord->total * SERVICE_TAX)/100)));
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n~~~~ T H A N K  Y O U  ~~~~~\n");
}

// code for make order
void makeOrder()
{
    struct Menu m;
    initializeMenu(&m);
    struct Order order = { .total = 0 };
   
    int orderNum=0;
    int choice;
    do {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n      ~ W E L C O M E ~        ");
        displayMenu(&m);
        printf("\n6 Generate Bill");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\n What would you like to have: ");
        scanf("%d", &choice);
        // to avoid infinite loop by clearing buffer for next line charactor
        getchar(); 
        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                placeOrder(&order,&m,&choice,&orderNum);
                break;
            case 6:
                getBill(&order,&m, &orderNum);
                break;
            default:
                printf("\n~~~~  Please choose another option  ~~~~\n");
                break;
        }
    } while (choice != 6);
}
