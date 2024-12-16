/* 
 Program to allow the user to enter details of an upcoming event (e.g., title, description, start time, and end time) and print the details in a format (including key-value pairs such as VERSION:2.0, CALSCALE:GREGORIAN, BEGIN:VEVENT, etc.) that can be imported into calendar applications (iCalendar/ics format). The code should include basic error handling for date formatting and should prompt the user to enter the correct format if invalid data is provided.
*/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_INPUT 100

typedef struct {
    char title[MAX_INPUT];
    char description[MAX_INPUT];
    char start_time[16];
    char end_time[16];
} Event;

int validateDate(const char *date) {
    if (strlen(date) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && date[i] != '-') return 0;
        if (i != 4 && i != 7 && !isdigit(date[i])) return 0;
    }
    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);
    return (year >= 1900 && month >= 1 && month <= 12 && day >= 1 && day <= 31);
}

int validateTime(const char *time) {
    if (strlen(time) != 8) return 0;
    for (int i = 0; i < 8; i++) {
        if ((i == 2 || i == 5) && time[i] != ':') return 0;
        if (i != 2 && i != 5 && !isdigit(time[i])) return 0;
    }
    int hour = atoi(time);
    int minute = atoi(time + 3);
    int second = atoi(time + 6);
    return (hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60);
}

void getValidDateTime(char *prompt, char *datetime) {
    char date[11], time[9];
    while (1) {
        printf("%s date (YYYY-MM-DD): ", prompt);
        scanf("%s", date);
        if (validateDate(date)) break;
        printf("Invalid date format. Please enter in YYYY-MM-DD.\n");
    }
    while (1) {
        printf("%s time (HH:MM:SS): ", prompt);
        scanf("%s", time);
        if (validateTime(time)) break;
        printf("Invalid time format. Please enter in HH:MM:SS.\n");
    }
    sprintf(datetime, "%.4s%.2s%.2sT%.2s%.2s%.2s", date, date + 5, date + 8, time, time + 3, time + 6);
}

void getEventDetails(Event *event) {
    printf("Enter event title: ");
    fgets(event->title, sizeof(event->title), stdin);
    event->title[strcspn(event->title, "\n")] = '\0';

    printf("Enter event description: ");
    fgets(event->description, sizeof(event->description), stdin);
    event->description[strcspn(event->description, "\n")] = '\0';

    getValidDateTime("Enter event start", event->start_time);
    getValidDateTime("Enter event end", event->end_time);
}

void parseDatetime(const char *datetime_str, struct tm *tm) {
    memset(tm, 0, sizeof(struct tm));
    sscanf(datetime_str, "%4d%2d%2dT%2d%2d%2d",
           &tm->tm_year, &tm->tm_mon, &tm->tm_mday,
           &tm->tm_hour, &tm->tm_min, &tm->tm_sec);

    tm->tm_year -= 1900; 
    tm->tm_mon -= 1;    
}

void printEvent(const Event *event) {
    struct tm tm;
    char formatted_start_date[11], formatted_start_time[9];
    char formatted_end_date[11], formatted_end_time[9];
    char *date_format = "%Y-%m-%d", *time_format = "%H:%M:%S"; 

    parseDatetime(event->start_time, &tm);
    strftime(formatted_start_date, sizeof(formatted_start_date), date_format, &tm);
    strftime(formatted_start_time, sizeof(formatted_start_time), time_format, &tm);

    parseDatetime(event->end_time, &tm);
    strftime(formatted_end_date, sizeof(formatted_end_date), date_format, &tm);
    strftime(formatted_end_time, sizeof(formatted_end_time), time_format, &tm);

    printf("\nBEGIN:VCALENDAR\n");
    printf("VERSION:2.0\n");
    printf("CALSCALE:GREGORIAN\n");
    printf("BEGIN:VEVENT\n");
    printf("SUMMARY: %s\n", event->title);
    printf("DESCRIPTION: %s\n", event->description);
    printf("DTSTART:%s Time: %s\n", formatted_start_date, formatted_start_time);
    printf("DTEND:%s Time: %s\n", formatted_end_date, formatted_end_time);
    printf("END:VEVENT\n");
    printf("END:VCALENDAR\n");
}

int main() {
    Event event;
    printf("Welcome to the Event Creator!\n");
    getEventDetails(&event);
    printEvent(&event);
    return 0;
}
