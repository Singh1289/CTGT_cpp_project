/*
    - taking Dob from user in 3 diff variables day, month , year.
    - using time library calulate today date
    - take difference of date. 
*/


#include <stdio.h>
#include <time.h>


int main() {
    //declaring varibles for date, month, and year
    int date, month, year;

    // taking input in all 3 variables
    printf("Enter the dob in \"dd mm yyyy\" format:\n");
    scanf("%d %d %d", &date, &month, &year);
   
    // capturing current time and date form system
    time_t now;
    time(&now);

    // creating struct of time 
    struct tm *local = localtime(&now);

    // creating current date from struct
    int presentYear = local->tm_year + 1900;
    int presentMonth = local->tm_mon + 1;
    int presentDay = local->tm_mday;
   
    // calculating age by takin diffrence
    int ageYears = presentYear - year;
    int ageMonths = presentMonth - month;
    int ageDays = presentDay - date;

    /* 
        rectify the diffrences. handle some cases have diffrent value 
        eg. date can have -ve value 
            leap year 
            month -ve value
    */
    if (ageDays < 0) {
       
        ageMonths--;
       
        int daysInPrevMonth;
        // handle day according to leap year and month
        if (presentMonth % 2 != 0) {
            daysInPrevMonth = 31;
        } else if (presentMonth == 2) {
            if ((presentYear % 4 == 0 && presentYear % 100 != 0) || presentYear % 400 == 0) {
                daysInPrevMonth = 29;
            } else {
                daysInPrevMonth = 28;
            }
        } else {
            daysInPrevMonth = 30;
        }

        ageDays += daysInPrevMonth;
    }
    // handle month
    if (ageMonths < 0) {
        ageYears--;
        ageMonths += 12;
    }

    // printing DOB and age 
    printf("\nDay: %d, Month: %d, Year: %d", date, month, year);
    printf("\nYou are %d years, %d months, and %d days old.", ageYears, ageMonths, ageDays);

    return 0;
}