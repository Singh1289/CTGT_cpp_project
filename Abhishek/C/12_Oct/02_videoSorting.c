/*
    Program to improve the functionality of a media library where you need to sort video files. 
    Each video file has a resolution (e.g., 1080p, 720p) and time duration. The goal is to sort 
    the videos first by resolution (highest first) and then by duration (shortest first). 
*/

#include<stdio.h>
#include<string.h>

// static variable to count 1080 songs
int count = 0;

// struct of song have some properties
typedef struct video
{
    char title[50];
    int resolution;
    int duration;
}video;

// define types
enum base {DURATION,RESOLUTION};

// taking input from user in array
void populataPlaylist(video *list, int size) {
    int temp;
    for (int i = 0; i < size; i++) {
        printf("\nTitle of video (max 50 chars) %d: ",i+1);
        scanf(" %49[^\n]", list[i].title);
        while (1) {
            printf("\nResolution (1080 or 720)%d: ",i+1);
            scanf("%d", &temp);
            if (temp == 1080 || temp == 720) {
                list[i].resolution = temp;
                break;
            }
            printf("\nInvalid input. Please enter 1080 or 720.");
        }
        while (1) {
            printf("\nDuration (in sec)%d: ",i+1);
            if (scanf("%d", &temp) == 1 && temp > 0) {
                list[i].duration = temp;
                break; 
            }
            // Clear invalid input
            while (getchar() != '\n');
            printf("\nInvalid input. Please enter a positive integer.");
        }
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
}

// swap both structures
void swap(video *a, video *b)
{
    video temp = *a;
    *a= *b;
    *b= temp;
}

// sort algo according to based on resolution and duration
void sortPlaylist(video* list, int start, int end, enum base type)
{
    int i, j, first, second;
    
    for(int i=start; i<end; i++)
    {
        if(type)
        {
            for(j=i+1; j<end; j++)
            {
                if(list[i].resolution < list[j].resolution)
                {
                    swap(&list[i],&list[j]);
                }
            }
        }
        else
        {
            for(j=i+1; j<end; j++)
            {
                if(list[i].resolution == list[j].resolution && list[i].duration > list[j].duration)
                {
                    swap(&list[i],&list[j]);
                }
                
            }
        }
    }
}


// to diaplay playlist
void displayPlaylist(video* list, int size)
{
    for(int i = 0;i< size;i++)
    {
        printf("\n%-5d %-25s %7d %7d",i+1,list[i].title,list[i].resolution,list[i].duration);
    }
}

// initializing playlist with some data
void intializePlaylist(video *list)
{
    strcpy(list[0].title, "aa");
    list[0].resolution = 1080;
    list[0].duration = 120;

    strcpy(list[1].title, "bb");
    list[1].resolution = 720;
    list[1].duration = 60;

    strcpy(list[2].title, "cc");
    list[2].resolution = 1080;
    list[2].duration = 75;

    strcpy(list[3].title, "ee");
    list[3].resolution = 720;
    list[3].duration = 360;

    strcpy(list[4].title, "ff");
    list[4].resolution = 1080;
    list[4].duration = 50;

    strcpy(list[5].title, "gg");
    list[5].resolution = 720;
    list[5].duration = 400;

    strcpy(list[6].title, "hh");
    list[6].resolution = 720;
    list[6].duration = 250;
}

void main()
{
    int size;
    printf("\nEnter size of array: ");
    scanf("%d",&size);
    video playlist[size];

    populataPlaylist(playlist,size);
    //intializePlaylist(playlist);

    // sort according to resolution
    sortPlaylist(playlist,0,size,RESOLUTION);

    printf("\n ~~~~~ Playlist ~~~~~");
    printf("\nS.no. %-25s %-7s %-7s","Title","Resolution","Duration");
    displayPlaylist(playlist,size);

    // 2nd sort according to duration
    sortPlaylist(playlist,0,size,DURATION);

    printf("\n ~~~~~ Playlist ~~~~~");
    printf("\nS.no. %-25s %-7s %-7s","Title","Resolution","Duration");
    displayPlaylist(playlist,size);
}
