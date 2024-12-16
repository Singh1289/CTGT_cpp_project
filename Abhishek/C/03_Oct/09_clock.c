/*
    Program to Print a Digital Clock showing time (both in 24-hour format and 12-hour format)
     in IST, UTC and GMT
*/


#include <stdio.h>
#include <time.h>


// print time on console in diffrent time zone
void printTime(struct tm *local_time, const char *zone) {
   
//     printf("%s (24-hour format): %02d:%02d:%02d\n", zone, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    
//     int hour = local_time->tm_hour % 12;
//     hour = (hour == 0) ? 12 : hour; 
//     printf("%s (12-hour format): %02d:%02d:%02d %s\n", zone, hour, local_time->tm_min, local_time->tm_sec, (local_time->tm_hour < 12) ? "AM" : "PM");

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_time);
    printf("%s: %s\n", zone, buffer);
}


// stop or pause the execution for 1 sec
void delay(int sec)
{  
    sleep(sec);   
}


int main() {

    // declaration of time variable
    time_t current_time;
    struct tm *local_time;
    struct tm *utc_time;
    
    // loop to diaplay the whole clock and refresh it in every 1 sec
    for(int i=0 ;i<500;i++)
    {
        system("cls");
        time(&current_time);

        // taking local time from time string
        local_time = localtime(&current_time);

        // talking UTC and GMT from time string
        utc_time = gmtime(&current_time);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("i: %d\n",i);
        printf("Current Time in IST:\n");
        printTime(local_time, "IST");
    
        printf("\nCurrent Time in UTC:\n");
        printTime(utc_time, "UTC");

        printf("\nCurrent Time in GMT:\n");
        printTime(utc_time, "GMT");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        
        delay(1);
    }

   

    return 0;
}
