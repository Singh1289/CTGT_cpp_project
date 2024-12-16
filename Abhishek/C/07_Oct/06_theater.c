/*
    Program to manage seating arrangements in a 3D theater layout where each row, column, and section represents a seating area. The program should support following functionality - Book Seat: Mark a seat as booked at a specific location; Cancel Booking: Cancel a booking for a seat at a specified location; View Seating: Display the seating arrangement with booked and available seats.
*/


#include <stdio.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLUMNS 10
#define MAX_SECTIONS 10

// Function to display the seating arrangement
void displaySeating(int arrangement[MAX_SECTIONS][MAX_ROWS][MAX_COLUMNS], int rows, int columns, int sections) {

    printf("Current Seating Arrangement:\n");
    // Iterate through each section
    for (int i = 0; i < sections; i++) {
        printf("Section %d:\n", i + 1);
        // printf column index
        for (int m = 0; m < columns; m++)
            printf("\t%d   ",m+1);

        printf("\n");
        // Iterate through each row
        for (int j = 0; j < rows; j++) {
            printf("%d ", j+1); // Print row number
            // Iterate through each column
            for (int k = 0; k < columns; k++) {
                printf("     [%c]", arrangement[i][j][k]? '*':'_'); // Print seat status (*- booked or _ vacant)
            }
            printf("\n"); 
        }
        printf("\n"); 
    }
}

// Function to book a seat
void bookSeat(int arrangement[MAX_SECTIONS][MAX_ROWS][MAX_COLUMNS], int rows, int columns, int sections) {
    int r, c, s;
    printf("Enter section, row, and column to book (1-indexed): ");
    scanf("%d %d %d", &s, &r, &c);
    r--; c--; s--; // Convert to 0-indexed

    // Validate input and book seat if available
    if (s >= 0 && s < sections && r >= 0 && r < rows && c >= 0 && c < columns) {
        if (arrangement[s][r][c] == 0) {
            arrangement[s][r][c] = 1; // Mark seat as booked
            printf("Seat booked successfully.\n");
        } else {
            printf("This seat is already booked.\n");
        }
    } else {
        printf("Invalid seat location.\n");
    }
}

// Function to cancel a booking
void cancelBooking(int arrangement[MAX_SECTIONS][MAX_ROWS][MAX_COLUMNS], int rows, int columns, int sections) {
    int r, c, s;
    printf("Enter section, row, and column to cancel booking: ");
    scanf("%d %d %d", &s, &r, &c);
    r--; c--; s--;

    // Validate input and cancel booking if it exists
    if (s >= 0 && s < sections && r >= 0 && r < rows && c >= 0 && c < columns) {
        if (arrangement[s][r][c] == 1) {
            arrangement[s][r][c] = 0; 
            printf("Booking cancelled successfully.\n");
        } else {
            printf("No booking found at this seat.\n");
        }
    } else {
        printf("Invalid seat location.\n");
    }
}


int main() {
    int rows, columns, sections;
    printf("Enter the number of sections, rows, and columns (max %d each): ", MAX_ROWS);
    scanf("%d %d %d", &sections, &rows, &columns);

    // Limit input to maximum values defined
    if (sections > MAX_SECTIONS) sections = MAX_SECTIONS;
    if (rows > MAX_ROWS) rows = MAX_ROWS;
    if (columns > MAX_COLUMNS) columns = MAX_COLUMNS;

    int arrangement[MAX_SECTIONS][MAX_ROWS][MAX_COLUMNS];

    // Initialize seating arrangement to 0 (available)
    memset(arrangement, 0, sizeof(arrangement)); 

    int choice;
    do {
        // Menu for user interaction
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n|   ~ W E L C O M E ~         |");
        printf("\n|1 : Seat Availability        |");
        printf("\n|2 : Book a Seat              |");
        printf("\n|3 : Cancel a seat            |");
        printf("\n|4 : Exit                     |");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\nWhat would you like to do: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                displaySeating(arrangement, rows, columns, sections); 
                break;
            case 2:
                bookSeat(arrangement, rows, columns, sections); 
                break;
            case 3:
                cancelBooking(arrangement, rows, columns, sections); 
                break;
            printf("\n~~~~ T H A N K  Y O U ~~~~~\n");
            break;
        default:
            printf("\n~~~~ Please choose a valid option ~~~~\n");
            break;
        }
    } while (choice != 4); 

    return 0; 
}
