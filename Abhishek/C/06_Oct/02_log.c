/*
    Program to filter a set of log entries entered by the user. Each log entry is a timestamped entry 
    in a format that includes date, time, and message. The program should filter log entries based on 
    a date range and display the filtered entries
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for log entry
typedef struct LogEntry {
    char date[11];   
    char time[9];     
    char message[100]; 
} LogEntry;

// Function to convert date and time to a single timestamp
time_t convertDateAndTime(char date[], char time[]) {
    struct tm tm = {0};
    sscanf(date, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    sscanf(time, "%d:%d:%d", &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
    
    tm.tm_year -= 1900; 
    tm.tm_mon -= 1;    
    return mktime(&tm);
}

// Function to filter log entries based on date range
void filterLogEntries(LogEntry log[], int logEntryCount, char startDate[], char endDate[]) {
    // converting string to date formated string
    time_t start = convertDateAndTime(startDate, "00:00:00"); 
    time_t end = convertDateAndTime(endDate, "23:59:59");    
    int foundCount = 0;

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for (int i = 0; i < logEntryCount; i++) {
        time_t currentDate = convertDateAndTime(log[i].date, log[i].time);

        if (currentDate >= start && currentDate <= end) {
            printf("%s %s %s\n", log[i].date, log[i].time, log[i].message);
            foundCount++;
        }
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nFiltered log entries: %d\n", foundCount);
}

int main() {
    // Array of log entries
    LogEntry logs[] = {
        {"2024-06-01", "18:00:00", "Server started"},
        {"2024-07-11", "11:30:00", "Error: failed to intialize server"},
        {"2024-07-15", "10:30:00", "Error: Out of memory"},
        {"2024-08-05", "09:30:00", "Database connection established"},
        {"2024-08-12", "14:45:00", "File upload successful"},
        {"2024-09-23", "10:15:00", "Authentication failed"},
        {"2024-09-31", "12:30:00", "Error: Index file not found"},
        {"2024-10-02", "08:30:00", "Error: Connection closed"},
        {"2024-10-16", "16:30:00", "Error: failed to connect"},
    };
    int logCount = sizeof(logs) / sizeof(logs[0]);
    
    char startDate[11], endDate[11];

    printf("Enter start date (YYYY-MM-DD): ");
    scanf("%10s", startDate);
    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%10s", endDate);
    
    filterLogEntries(logs, logCount, startDate, endDate);
    
    return 0;
}
