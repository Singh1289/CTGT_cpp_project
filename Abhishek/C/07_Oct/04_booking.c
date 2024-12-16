#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 3

int TABLE_ID = 1100;

typedef struct
{
    int id;
    char name[20];
    unsigned int mobile;
} Table;

void initializeTable(int mapTable[][MAX_COLS])
{
    int count = 1;
    for (int i = 0; i < MAX_ROWS; i++)
    {
        mapTable[i][0] = count++;       
        mapTable[i][1] = 0;              // Availability (0: Available, 1: Reserved)
        mapTable[i][2] = rand() % 4 + 3; // Seating capacity (3-6)
    }
}

void tableStatus(Table tables[], int mapTable[][MAX_COLS])
{
    int temp;
    printf("\nEnter table number to see details: ");
    while (scanf("%d", &temp))
    {
        if (temp > 0 && temp <= MAX_ROWS)
            break;
        printf("\nInvalid input. Please enter a valid table number (1 - %d): ", MAX_ROWS);
    }
    getchar();

    int index = temp - 1; // Adjust for 0-based indexing
    if (mapTable[index][1] == 1)
    {
        printf("\nTable %d is reserved by %s with mobile number %u.\n",
               temp, tables[index].name, tables[index].mobile);
    }
    else
    {
        printf("\nTable %d is available.\n", temp);
    }
}

void printTable(Table tables[], int mapTable[][MAX_COLS])
{
    printf("T.No.\tStatus\t   Seating\n");
    for (int i = 0; i < MAX_ROWS; i++)
    {
        printf("%d\t%-8s\t%d\n",
               mapTable[i][0],
               mapTable[i][1] == 0 ? "Available" : "Reserved",
               mapTable[i][2]);
    }
    while(1){
        char i;
        tableStatus(tables,mapTable);
        printf("\nWant to go Back Y/N: ");
        scanf("%c",&i);
        if(i == 'Y'||i == 'y')break;
    }
}

void reserveTable(Table tables[], int mapTable[][MAX_COLS])
{
    int temp;
    printf("\nEnter table number to reserve: ");
    while (scanf("%d", &temp))
    {
        if (temp > 0 && temp <= MAX_ROWS)
            break;
        printf("\nInvalid input. Please enter a valid table number (1 - %d): ", MAX_ROWS);
    }
    getchar();

    int index = temp - 1;
    if (mapTable[index][1] == 1)
    {
        printf("\nTable %d is already reserved.\n", temp);
        return;
    }

    tables[index].id = TABLE_ID++;
    printf("Enter customer name: ");
    fgets(tables[index].name, 20, stdin);
    tables[index].name[strcspn(tables[index].name, "\n")] = '\0'; // Remove newline
    printf("Enter customer mobile number: ");
    scanf("%u", &tables[index].mobile);

    mapTable[index][1] = 1; // Mark as reserved
    printf("\nTable %d has been reserved.\n", temp);
}

void cancelReservation(Table tables[], int mapTable[][MAX_COLS])
{
    int temp;
    printf("\nEnter table number to cancel reservation: ");
    while (scanf("%d", &temp))
    {
        if (temp > 0 && temp <= MAX_ROWS)
            break;
        printf("\nInvalid input. Please enter a valid table number (1 - %d): ", MAX_ROWS);
    }
    getchar();

    int index = temp - 1;
    if (mapTable[index][1] == 0)
    {
        printf("\nTable %d is not currently reserved.\n", temp);
        return;
    }

    mapTable[index][1] = 0; // Mark as available
    tables[index].id = 0;
    strcpy(tables[index].name, "");
    tables[index].mobile = 0;

    printf("\nReservation for table %d has been canceled.\n", temp);
}

int main()
{
    Table tables[MAX_ROWS] = {0};
    int mapTable[MAX_ROWS][MAX_COLS] = {0};

    initializeTable(mapTable);
    int choice;

    do
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n|         ~ W E L C O M E ~         |");
        printf("\n|1 : Table Availability             |");
        printf("\n|2 : Reserve a Table                |");
        printf("\n|3 : Cancel a Reservation           |");
        printf("\n|4 : Exit                           |");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\nWhat would you like to do: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printTable(tables, mapTable);
            break;
        case 2:
            reserveTable(tables, mapTable);
            break;
        case 3:
            cancelReservation(tables, mapTable);
            break;
        case 4:
            printf("\n~~~~ T H A N K  Y O U ~~~~~\n");
            break;
        default:
            printf("\n~~~~ Please choose a valid option ~~~~\n");
            break;
        }
    } while (choice != 4);

    return 0;
}
