/*
Problem: Given a list of numbers, which represents a set of numbers ranging from m to n (inclusive), where |n - m| is the length of the list. Due to an error, at least one number from the set is duplicated, and at least one other number is missing. Find the duplicated number(s) and the missing number(s).
Input: A list of numbers ranging from m to n such that m <= n and m <= 10^19 and n <= 10^19. Please follow the same input format as depicted in the examples.
Output: Print a list of pair(s) of duplicate number(s) and the missing number(s) such that each pair is represented as (duplicate number, missing number). Follow the same output format as depicted in the examples.
Instructions: Solve for one duplicate only for the purpose of this assessment. However, consider the problem for multiple duplicates as an assignment and include it in the list of assignments.
Examples:
Input: [1,2,2,4]
Output: [(2, 3)]
Input: [3, 1, 2, 5, 3]
Output: [(3, 4)]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pair
{
    unsigned long long duplicate;
    unsigned long long missing;
} Pair;

void findDuplicateAndMissing(unsigned long long *nums, int n)
{
    Pair result;
   
    //unsigned long long sum = 0;
    unsigned long long expected = nums[0];
    int dub, miss;
    unsigned long long duplicate,missing;
    duplicate =missing= -9999;
    dub = missing = 1;
    for (int i = 1; i < n; i++)
    {
        expected++;
        if (dub && nums[i - 1] == nums[i])
        {
            duplicate = nums[i];
            dub = 0;
        }
        if (missing && nums[i] != expected)
        {   //printf("Duplicate\n");
            missing = expected;
            miss = 0;
        }
        if (!miss && !dub)
        {
            //printf("i: %d",i);
            break;
        }
    }
    printf("\n([ %llu, %llu ])", duplicate, missing);
    
}

int convertIntoDecimal(char *str)
{
    unsigned long long decimal = 0;
    if (strncmp(str, "0x", 2) == 0 || strncmp(str, "0X", 2) == 0)
    {
        decimal = (unsigned long long)strtoul(str, NULL, 16);
    }
    else if (str[0] == '0' && str[1] != 'x')
    {
        decimal = (unsigned long long)strtol(str, NULL, 8);
    }
    else
    {
        decimal = (unsigned long long)strtol(str, NULL, 10);
    }
    return decimal;
}

void convert(char *str, unsigned long long *arr, int *idx)
{
    int i = 0;
    char temp[20];
    char *end = strchr(str, ']');
    char *start = strchr(str, '[');
    if (start == NULL || end == NULL)
    {
        printf("invalid input.");
        exit(-1);
    }

    if (str[0] == '[')
        str++;

    while (str[i] != '\0' && str[i] != '}')
    {
        if (str[i] == ' ' || str[i] == ',')
        {
            i++;
            continue;
        }

        int j = 0;

        if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
        {
            while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}')
                temp[j++] = str[i++];
        }
        else if (str[i] == '0' && str[i + 1] != 'x')
        {
            while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}')
                temp[j++] = str[i++];
        }
        else if ((str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9')) || (str[i] >= '0' && str[i] <= '9'))
        {
            while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}')
                temp[j++] = str[i++];
        }
        temp[j] = '\0';

        if (j > 0)
        {
            arr[*idx] = convertIntoDecimal(temp);
            (*idx)++;
        }
    }
}
void trim(char *str)
{
    int start = 0, end = strlen(str) - 1, idx = 0;

    while (str[start] == ' ')
    {
        start++;
    }

    while (end >= start && str[end] == ' ')
    {
        str[end] = '\0';
        end--;
    }

    while (str[start] != '\0')
    {
        str[idx++] = str[start++];
    }
    str[idx] = '\0';
}

void sort(unsigned long long arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                unsigned long long temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void main()
{
    char buffer[1000];
    printf("input: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    trim(buffer);

    if (strlen(buffer) < 1)
    {
        printf("invalid input.");
        exit(-1);
    }
    unsigned long long arr[10000];
    int idx = 0;
    convert(buffer, arr, &idx);

    for (int i = 0; i < idx; i++)
    {
        printf("%llu", arr[i]);
    }

    if (idx == 0)
    {
        printf("invalid input.");
        exit(-1);
    }

    sort(arr, idx);

   findDuplicateAndMissing(arr, idx);
}
