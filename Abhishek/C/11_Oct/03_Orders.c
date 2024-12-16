/*
    Program to manage food orders/deliveries. Program should receive food orders from the customer and process
     them based on their delivery/processing times. Task is to manage these orders efficiently.
     Implement functionality to add new orders, retrieve the earliest order for delivery, and modify existing
      orders. Functions
      (a) Add Order: Add a new food order with a specific delivery time;
      (b) Retrieve Earliest Order: Retrieve and remove the order with the earliest delivery time;
      (c) Modify/Cancel Order: Update the details of an existing order;
      (d) List Orders: List pending/processed orders;
      (e) Average Order Processing Time: compute the average delivery/processing time of all pending orders.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ORDERID = 0;
int OERDER_COUNT= 0;

// Structure for food order
typedef struct foodOrder
{
    int orderId;
    char customerName[50];
    char foodItem[50];
    time_t deliveryTime;
    time_t processingTime;
    int status;
} FoodOrder;

// Function declarations
void addOrder(FoodOrder orders[], char *customerName, char *foodItem, time_t deliveryTime);
void retrieveEarliestOrder(FoodOrder orders[]);
void modifyOrder(FoodOrder orders[],int id, char *customerName, char *foodItem, time_t deliveryTime);
void cancelOrder(FoodOrder orders[], int orderId);
void listOrders(FoodOrder orders[]);
float calculateAverageProcessingTime(FoodOrder orders[]);

int main()
{
    FoodOrder orders[100];
    
    int choice;

    do
    {
        printf("\n1. Add Order\n2. Retrieve Earliest Order\n3. Modify/Cancel Order\n4. List Orders\n5. Average Order Processing Time\n6. Exit\n=> ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char customerName[50], foodItem[50];
            time_t deliveryTime;
            printf("Enter Customer Name: ");
            scanf("%s", customerName);
            printf("Enter Food Item: ");
            scanf("%s", foodItem);
            printf("Enter Delivery Time (seconds from now): ");
            int timeOffset;
            scanf("%d", &timeOffset);
            if(timeOffset < 180)
            {
                printf("Invalid time offset. Time offset should be more than at least 180 seconds.\n");
                break;
            }
            deliveryTime = time(NULL) + timeOffset;

            addOrder(orders, customerName, foodItem, deliveryTime);
            break;
        }
        case 2:
            if (OERDER_COUNT == 0)
            {
                printf("No pending orders.\n");
            }
            else
            {
                retrieveEarliestOrder(orders);
            }
            break;

        case 3:
        {
            int orderId, cancelOrModify;
            printf("Enter Order ID to modify/cancel: ");
            scanf("%d", &orderId);
            printf("Enter 1 to modify, 2 to cancel: ");
            scanf("%d", &cancelOrModify);

            if (cancelOrModify == 1)
            {
                char customerName[50], foodItem[50];
                time_t deliveryTime;
                printf("Enter New Customer Name: ");
                scanf("%s", customerName);
                printf("Enter New Food Item: ");
                scanf("%s", foodItem);
                printf("Enter New Delivery Time (seconds): ");
                scanf("%ld", &deliveryTime);

                modifyOrder(orders,orderId, customerName, foodItem, deliveryTime);
            }
            else if (cancelOrModify == 2)
            {
                cancelOrder(orders, orderId);
            }
            else
            {
                printf("Invalid choice.\n");
            }
            break;
        }

        case 4:
            listOrders(orders);
            break;

        case 5:
        {
            float avgProcessingTime = calculateAverageProcessingTime(orders);
            if (avgProcessingTime > 0)
            {
                printf("Average Order Processing Time: %.2f seconds\n", avgProcessingTime);
            }
            else
            {
                printf("No processed orders.\n");
            }
            break;
        }

        case 6:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 6);

    return 0;
}

void addOrder(FoodOrder orders[], char *customerName, char *foodItem, time_t deliveryTime)
{
    orders[ORDERID].orderId = ORDERID+1;
    strcpy(orders[ORDERID].customerName, customerName);
    strcpy(orders[ORDERID].foodItem, foodItem);
    orders[ORDERID].deliveryTime = deliveryTime+180;
    orders[ORDERID].processingTime = 180;
    orders[ORDERID].status = 0;
    ORDERID++;
    OERDER_COUNT++;
    printf("Order added successfully.\n");
}

void retrieveEarliestOrder(FoodOrder orders[])
{
    if (OERDER_COUNT == 0)
    {
        printf("No pending orders to retrieve.\n");
        return;
    }

    int earliestIndex = 0;
    for (int i = 1; i < OERDER_COUNT; i++)
    {
        if (orders[i].deliveryTime < orders[earliestIndex].deliveryTime && orders[i].status == 0)
        {
            earliestIndex = i;
        }
    }

    printf("Earliest order: \nOrder ID - %d, \nCustomer - %s, \nFood Item - %s, \nDelivery Time - %s\n", orders[earliestIndex].orderId, orders[earliestIndex].customerName, orders[earliestIndex].foodItem, ctime(&orders[earliestIndex].deliveryTime));
    
    orders[earliestIndex].status = 1;
    orders[earliestIndex].processingTime = time(NULL); 
    OERDER_COUNT--;

    printf("Order processed successfully.\n");
}

void modifyOrder(FoodOrder orders[], int id, char *name, char *foodName, time_t deliveryTime)
{
    for (int i = 0; i < OERDER_COUNT; i++)
    {
        if (orders[i].orderId == id && orders[i].status == 0)
        {
            strcpy(orders[i].customerName, name);
            strcpy(orders[i].foodItem, foodName);
            orders[i].deliveryTime += deliveryTime;
            printf("Order modified successfully.\n");
            return;
        }
    }
    printf("Order not found or already processed.\n");
}

void cancelOrder(FoodOrder orders[], int orderId)
{
    for (int i = 0; i <OERDER_COUNT; i++)
    {
        if (orders[i].orderId == orderId && orders[i].status == 0)
        {
            orders[i].status = 1;
            printf("Order canceled successfully.\n");
            return;
        }
    }
    printf("Order not found or already processed.\n");
}

void listOrders(FoodOrder orders[])
{
    printf("Pending Orders: %d\n", OERDER_COUNT);
    for (int i = 0; i < ORDERID; i++)
    {
        if (orders[i].status == 0)
        {
            printf("Order ID - %d, Customer - %s, Food Item - %s, Delivery Time - %s", orders[i].orderId, orders[i].customerName, orders[i].foodItem, ctime(&orders[i].deliveryTime));
        }
    }

    printf("\nProcessed Orders: %d\n",ORDERID - OERDER_COUNT);
    for (int i = 0; i < ORDERID; i++)
    {
        if (orders[i].status == 1)
        {
            printf("Order ID - %d, Customer - %s, Food Item - %s, Processed Time - %s", orders[i].orderId, orders[i].customerName, orders[i].foodItem, ctime(&orders[i].processingTime));
        }
    }
}

float calculateAverageProcessingTime(FoodOrder orders[])
{
    float totalProcessingTime = 0;
    int processedOrders = 0;

    for (int i = 0; i < ORDERID; i++)
    {
        if (orders[i].status == 1)
        {
            totalProcessingTime +=  difftime(time(NULL),orders[i].deliveryTime);
            processedOrders++;
        }
    }
    if(totalProcessingTime < 0) totalProcessingTime *= -1;
    if (processedOrders > 0)
    {
        return totalProcessingTime / processedOrders;
    }
    else
    {
        printf("There are no orders to process");
    }
}
