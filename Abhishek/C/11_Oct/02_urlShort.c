/*
    Program to implement a URL shortener that maps long URLs to shorter, unique strings.
    The program should support generating short URLs and retrieving the original URL from
    a short URL. Implement a method to generate a unique short URL for a given long URL.
    Use a simple encoding scheme to create short URLs, e.g., Base62 encoding. Also, Implement
    a method to retrieve the original long URL given a short URL.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_MAX 100
#define BASE62 "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

// Assuming url_map and url_index are defined globally
typedef struct
{
    char long_url[URL_MAX];
    char short_url[URL_MAX];
} URLMap;

URLMap url_map[1001];
int url_index = 0;
char long_url[URL_MAX];
char short_url[URL_MAX];

long long int generateNumber(const char *string)
{
    if (string == NULL)
        return 0; // Handle NULL case

    int len = strlen(string);
    if (len > 25)
        len = 25;

    long long int num = 0;
    for (int i = 0; i < len; i++)
    {
        num = num * 2 + string[i];
    }
    return num;
}

void reverseString(char *str, int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void generateShortURL(const char *long_url, char *short_url)
{
    // Check if the short URL map is full
    if (url_index > 1000)
    {
        printf("URL map is full.\n");
        return;
    }

    // Copy the long URL to the map
    strcpy(url_map[url_index].long_url, long_url);

    // Find the first '.' in the long URL for encoding purposes
    char *link = strrchr(long_url, '.');

    // generate unique number
    long long int number = generateNumber(link);
    // printf("Decimal: %lld\n", number);

    // Generate the short URL using Base62 encoding
    char newShortURL[URL_MAX];
    int baseIndex = 0;

    // Convert the number to Base62
    while (number > 0)
    {
        int digit = number % 62;
        newShortURL[baseIndex++] = BASE62[digit];
        number /= 62;
    }
    newShortURL[baseIndex] = '\0';

    // Reverse the encoded string since it's built backward
    reverseString(newShortURL, baseIndex);

    // Concatenate "Shrt_/" with the encoded string
    strcpy(short_url, "Shrt_/");
    strcat(short_url, newShortURL);

    // Store the short URL in the map
    strcpy(url_map[url_index].short_url, short_url);

    // printf("Generated Short URL: %s\n", .short_url);
    url_index++;
}

// Function to retrieve the original long URL given a short URL
int getLongURL(const char *short_url)
{
    for (int i = 0; i < url_index; i++)
    {
        if (strcmp(url_map[i].short_url, short_url) == 0)
        {
            return i;
        }
    }
    return -1;  // Return -1 if the short URL is not found
}

// function to genrate short url
void shorternURL()
{
    //printf(" lengths: %d\n", strlen(long_url));
    printf("Enter a long URL: ");
    fgets(long_url, sizeof(long_url), stdin);
    long_url[strcspn(long_url, "\n")] = '\0';

    generateShortURL(long_url, short_url);
    if (short_url[0])
    {
        printf("\nShortened URL: %s", short_url);
    }
    else
    {
        printf("\nFailed to generate short URL.");
    }
}

// function to get original URL
void getOriginalURL()
{
    printf("\nEnter the short URL to retrieve the long URL: ");
    fgets(short_url, sizeof(short_url), stdin);
    short_url[strcspn(short_url, "\n")] = '\0';

    int mapIndex = getLongURL(short_url);
    if (mapIndex == -1)
        printf("\nNo URL found.");
    else
        printf("\nURL: %s", url_map[mapIndex].long_url);
}

int main()
{

    int choice;

    do
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n|         ~ W E L C O M E ~         |");
        printf("\n|1 : Shorten URL                    |");
        printf("\n|2 : Get original URL               |");
        printf("\n|3 : Exit                           |");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\n What would you like to do: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            shorternURL();
            break;
        case 2:
            getOriginalURL();
            break;

        case 3:
            printf("\n~~~~ T H A N K  Y O U  ~~~~~\n");
            break;
        default:
            printf("\n~~~~  Please choose another option  ~~~~\n");
            break;
        }
    } while (choice != 3);

    return 0;
}