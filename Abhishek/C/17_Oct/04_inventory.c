/*
Write a program for managing the inventory of a store. Each time an item is added to the inventory, it may or may not exist in the inventory. Your goal is to maintain a list of unique items that are currently in stock. When the inventory is updated, you need to return the current unique items in the order they were first added. Each item may have attributes like item name, type, price, quantity, etc. The inventory can contain up to 10,000 items. Consider efficiency in both time and space, as the inventory can grow large with repeated updates. Your solution should ensure that the unique items are accurately represented after each update.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 10000
#define HASH_SIZE 13009

typedef struct item
{
    char forHASH[46];
    char brand[10];
    char type[10];
    char product[25];
    int price;
    int quantity;
    struct item *next;
} item;

item *hashTable[HASH_SIZE];
int inventoryArr[MAX_ITEMS];
int inventoryIdx = 0;

// Hash function
int hashFunction(const char *forHASH)
{
    int sum = 0;
    int prime = 31;
    for (int i = 0; i < strlen(forHASH); i++)
    {
        sum = sum * prime + forHASH[i];
    }
    return sum % HASH_SIZE;
}

// Function to create a new item
item *createItem(const char *brand, const char *type, const char *product, int price, int quantity)
{
    item *newItem = (item *)malloc(sizeof(item));
    strcpy(newItem->forHASH, brand);
    strcpy(newItem->forHASH, type);
    strcpy(newItem->forHASH, product);
    strcpy(newItem->brand, brand);
    strcpy(newItem->type, type);
    strcpy(newItem->product, product);
    newItem->price = price;
    newItem->quantity = quantity;
    newItem->next = NULL;
    return newItem;
}

// Function to add/update
void addItem(const char *brand, const char *type, const char *product, int price, int quantity)
{
    item *newItem = createItem(brand, type, product, price, quantity);
    int index = hashFunction(newItem->forHASH);
    item *current = hashTable[index];

    // Search for item
    while (current != NULL)
    {
        // if found then update it
        if (strcmp(current->forHASH, newItem->forHASH) == 0)
        {
            current->quantity += quantity;
            current->price = price;
            return;
        }
        current = current->next;
    }

    // Item not found; create and insert it at the beginning of the list
    newItem->next = hashTable[index];
    hashTable[index] = newItem;

    // Check if index is already in insertion order array
    int isIndexAdded = 0;
    for (int i = 0; i < inventoryIdx; i++)
    {
        if (inventoryArr[i] == index)
        {
            isIndexAdded = 1;
            break;
        }
    }
    // If it's a new index, add it to inventoryArr array
    if (!isIndexAdded)
    {
        inventoryArr[inventoryIdx++] = index;
    }
}


void displayInventoryInOrder() {
    printf("Inventory:\n");
    printf("%-4s %-15s %-10s %-20s %-10s %-10s\n", "No.", "Brand", "Type", "Product", "Price", "Quantity");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < inventoryIdx; i++) {
        int index = inventoryArr[i];
        item* current = hashTable[index];

        while (current != NULL) {
            printf("%-4d %-15s %-10s %-20s %-10d %-10d\n", 
                   i + 1, current->brand, current->type, current->product, current->price, current->quantity);
            current = current->next;
        }
    }
    printf("------------------------------------------------------------------------\n\n");

}


// Function to free memory for all items in the hash table
void freeInventory()
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        item *current = hashTable[i];
        while (current != NULL)
        {
            item *temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

// Function to take input for adding/updating an item
void takeInput(char *brand, char *type, char *product, int *price, int *quantity)
{
     printf("Enter brand: ");
    fgets(brand, 10, stdin);
    brand[strcspn(brand, "\n")] = '\0';

    printf("Enter type: ");
    fgets(type, 10, stdin);
    type[strcspn(type, "\n")] = '\0';

    printf("Enter product: ");
    fgets(product, 25, stdin);
    product[strcspn(product, "\n")] = '\0';

    printf("Enter price: ");
    scanf("%d", price);

    printf("Enter quantity: ");
    scanf("%d", quantity);

    getchar();
}

int main()
{
    int choice;
    char brand[10], type[10], product[25];
    int price, quantity;

    while (1)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n|  ~ Inventory Management ~   |");
        printf("\n|1: Add / update Item         |");
        printf("\n|2: Display Inventory         |");
        printf("\n|7: Exit                      |");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nChoose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            takeInput(brand, type, product, &price, &quantity);
            addItem(brand, type, product, price, quantity);
            printf("Item added/updated successfully.\n\n");
            break;

        case 2:

            displayInventoryInOrder();
            break;

        case 3:
            printf("~~~ See You Soon ~~~\n");
            freeInventory();
            return 0;

        default:
            printf("Invalid choice. Please try again.\n\n");
        }
    }
    return 0;
}
