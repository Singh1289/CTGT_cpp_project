#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 200

typedef union vehicle_d
{
    char fuel_type[20];
    int cargo_capacity;
} vehicle_d;

typedef struct vehicle
{
    char vehicle_type[20];
    char vehicle_ID[20];
    char maintenance_info[50];
    int kms;  
    int kms1; 
    time_t current_time;
    vehicle_d v1; 
    int is_cargo;
} vehicle;

vehicle vehice_details[MAX_SIZE];
int count = 0;

void accept_details()
{
    if (count >= MAX_SIZE)
    {
        printf("Maximum number of vehicles reached.\n");
        return;
    }

    printf("Enter the vehicle type: ");
    fgets(vehice_details[count].vehicle_type, sizeof(vehice_details[count].vehicle_type), stdin);
    vehice_details[count].vehicle_type[strcspn(vehice_details[count].vehicle_type, "\n")] = 0;

    printf("Enter the vehicle number: ");
    fgets(vehice_details[count].vehicle_ID, sizeof(vehice_details[count].vehicle_ID), stdin);
    vehice_details[count].vehicle_ID[strcspn(vehice_details[count].vehicle_ID, "\n")] = 0;

    printf("Enter the vehicle maintenance information: ");
    fgets(vehice_details[count].maintenance_info, sizeof(vehice_details[count].maintenance_info), stdin);
    vehice_details[count].maintenance_info[strcspn(vehice_details[count].maintenance_info, "\n")] = 0;

    printf("Enter the daily vehicle use in kms: ");
    scanf("%d", &vehice_details[count].kms);
    printf("Enter the kms after the oil change: ");
    scanf("%d", &vehice_details[count].kms1);
    vehice_details[count].current_time = time(NULL);

    getchar(); 
    printf("Enter the vehicle fuel type (or type 'none' if it's a cargo vehicle): ");
    fgets(vehice_details[count].v1.fuel_type, sizeof(vehice_details[count].v1.fuel_type), stdin);
    vehice_details[count].v1.fuel_type[strcspn(vehice_details[count].v1.fuel_type, "\n")] = 0;

    // Set the is_cargo flag based on fuel type
    if (strcmp(vehice_details[count].v1.fuel_type, "none") == 0)
    {
        vehice_details[count].is_cargo = 1; // Mark as cargo vehicle
        printf("Enter the vehicle cargo capacity: ");
        scanf("%d", &vehice_details[count].v1.cargo_capacity);
    }
    else
    {
        vehice_details[count].is_cargo = 0; // Mark as non-cargo vehicle
    }

    count++;
}

void display()
{
    printf("Here's the information of all vehicles:\n");

    for (int i = 0; i < count; i++)
    {
        printf("Vehicle Type: %s\n", vehice_details[i].vehicle_type);
        printf("Vehicle ID: %s\n", vehice_details[i].vehicle_ID);
        printf("Maintenance Info: %s\n", vehice_details[i].maintenance_info);

        // Print based on whether it's a cargo vehicle
        if (vehice_details[i].is_cargo)
        {
            printf("Cargo Capacity: %d\n", vehice_details[i].v1.cargo_capacity);
        }
        else
        {
            printf("Fuel Type: %s\n", vehice_details[i].v1.fuel_type);
        }

        printf("\n"); 
    }
}

void update()
{
    char vehicle_number[20];
    printf("Enter the vehicle number: ");
    fgets(vehicle_number, sizeof(vehicle_number), stdin);
    vehicle_number[strcspn(vehicle_number, "\n")] = 0; 

    int found = 0; 

    for (int i = 0; i < count; i++)
    {
        if (strcmp(vehice_details[i].vehicle_ID, vehicle_number) == 0)
        {
            found = 1; 
            printf("Enter the vehicle maintenance information: ");

            fgets(vehice_details[count].maintenance_info, sizeof(vehice_details[count].maintenance_info), stdin);
            vehice_details[count].maintenance_info[strcspn(vehice_details[count].maintenance_info, "\n")] = 0;

           
        }
    }
}
void maintenance_schedule()
{
    char vehicle_number[20];
    printf("Enter the vehicle number: ");
    fgets(vehicle_number, sizeof(vehicle_number), stdin);
    vehicle_number[strcspn(vehicle_number, "\n")] = 0; 

    int found = 0; 

    for (int i = 0; i < count; i++)
    {
        if (strcmp(vehice_details[i].vehicle_ID, vehicle_number) == 0)
        {
            found = 1; 
            printf("Vehicle Type: %s\n", vehice_details[i].vehicle_type);
            printf("Vehicle ID: %s\n", vehice_details[i].vehicle_ID);
            printf("Maintenance Info: %s\n", vehice_details[i].maintenance_info);

            int days_until_maintenance = vehice_details[i].kms1 / vehice_details[i].kms;
            struct tm *tm_info = localtime(&vehice_details[i].current_time);
            tm_info->tm_mday += days_until_maintenance;
            time_t next_maintenance_time = mktime(tm_info);
            printf("Next maintenance date: %s", ctime(&next_maintenance_time));

            if (vehice_details[i].is_cargo)
            {
                printf("Cargo Capacity: %d\n", vehice_details[i].v1.cargo_capacity);
            }
            else
            {
                printf("Fuel Type: %s\n", vehice_details[i].v1.fuel_type);
            }
            break;
        }
    }

    if (!found)
    { 
        printf("Vehicle not found.\n");
    }
}

int menu()
{
    int choice;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n|          ~ W E L C O M E ~          |");
    printf("\n|1 : Add vehicle details              |");
    printf("\n|2 : Update vehicle details           |");
    printf("\n|3 : Schedule maintenance date        |");
    printf("\n|4 : Display all maintenance details  |");
    printf("\n|0 : Exit                             |");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\nWhat would you like to do: ");
    scanf("%d", &choice);
    getchar(); 
    return choice;
}

int main()
{
    int choice;

    while ((choice = menu()) != 0)
    {
        switch (choice)
        {
        case 1:
            accept_details();
            break;
        case 2:
            update();
            break;
        case 3:
            maintenance_schedule();
            break;
        case 4:
            display();
            break;
        default:
            printf("Wrong choice entered.\n");
            break;
        }
    }

    return 0;
}
