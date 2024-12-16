
//  Program to schedule interviews for candidates after processing job applications efficiently. Sort the applications based on multiple criteria: the application date, the applicant's experience, and the application score. The goal is to prioritize candidates who applied earlier, have more experience, and scored higher. Ensure that the sorting is stable, preserving the order of applications with equal criteria. Each job application is stored in a file containing details about the criteria in a specific format (e.g., Alice, 2024-09-01, 5 years, 90 or Charlie, 2024-09-01, 5 years, 95). Output the interview schedule.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char name[100];
    char date[11];
    float experience;
    float score;
} Application;


void swap(Application *a, Application *b)
{
    Application temp = *a;
    *a = *b;
    *b = temp;
}

void sortApplication(Application *arr, int count,int type)
{
      
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (type == 0) {
            
                if (strcmp(arr[j].date, arr[i].date) < 0) {
                    swap(&arr[j], &arr[i]);
                }
            } 
            else if (type == 1) {

                if (strcmp(arr[j].date, arr[i].date) == 0 && arr[j].experience > arr[i].experience) {
                    swap(&arr[j], &arr[i]);
                }
            } 
            else {
            
                if (strcmp(arr[j].date, arr[i].date) == 0 && arr[j].experience == arr[i].experience && arr[j].score > arr[i].score) {
                    swap(&arr[j], &arr[i]);
                }
            }
        }
    }
}

int main()
{
    FILE *file = fopen("aplication.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    int count = 0;
    Application appAarry[100];
    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        char name[100];
        char date[11];
        float exp;
        float scores;

        int result = sscanf(line, "%[^,],%[^,],%f,%f", name, date, &exp, &scores);

        if (result != 4)
        {
            printf("Error: Line is not in the expected format. line : %d\n", count);
        }
        else
        {
            strcpy(appAarry[count].name, name);
            strcpy(appAarry[count].date, date);
            appAarry[count].experience = exp;
            appAarry[count].score = scores;
        }
        count++;
    }
    fclose(file);

    sortApplication(appAarry, count , 0);
    sortApplication(appAarry, count , 1);
    sortApplication(appAarry, count , 2);
    printf("Interview Schedule:\n");
        printf("Name       Date          Experience   Scores\n");
    for (int i = 0; i < count; i++)
    {   
        printf("%-10s %-12s  %-5.2f years  %-5.2f\n", appAarry[i].name, appAarry[i].date, appAarry[i].experience, appAarry[i].score);
    }
    return 0;
}