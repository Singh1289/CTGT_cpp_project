#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100
int SIZE = 0;
int called = 1;

void convertToIntegerArray(int *array, char *input, int len)
{
    char *token = strtok(input, ",");
    while (token != NULL && SIZE < MAX_SIZE)
    {
        // Check for hexadecimal format
        if (strncmp(token, " 0x", 3) == 0 || strncmp(token, " 0X", 3) == 0)
        {
            //Convert hex to integer
            array[SIZE++] = (int)strtol(token, NULL, 16);
        }
        else if (strncmp(token, " No", 3) == 0)
        {
            //printf("called :%d\n",called++);
            array[SIZE++] = INT_MIN;
        }
        else
        {
            // Convert regular decimal numbers
            array[SIZE++] = atoi(token);
        }
        token = strtok(NULL, ",");
    }
}

// function to create a array of nodes levelwise
void printingReverseLevel(int *array, int *output, int *len)
{
    if (array[0] == INT_MIN)
    {
        printf("\nRoot node is empty\n");
        return;
    }

    output[0] = array[0];
    output[1] = -999;
    *len = 2;
    int push = 2, arrIdx = 1;
    int pop = 0;

    while (arrIdx < SIZE)
    {
        if (output[pop] != -999)
        {
            if (output[pop] != INT_MIN)
            {
                pop++;
                if (arrIdx < SIZE)
                {
                    output[push++] = array[arrIdx++];
                    (*len)++;
                }

                if (arrIdx < SIZE)
                {
                    output[push++] = array[arrIdx++];
                    (*len)++;
                }
            }
            else
            {
                pop++;
            }
        }
        else
        {
            output[push++] = -999;
            pop++;
            (*len)++;
        }
    }
}

void main()
{
    char string[1024];
    printf("Enter a string: ");
    fgets(string, sizeof(string), stdin);

    int len = strlen(string);

    int inputArray[MAX_SIZE] = {INT_MIN};

    convertToIntegerArray(inputArray, string, len);

    // for testing  purposes
    for (int i = 0; i < SIZE; i++)
        printf("%d ", inputArray[i]);

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // array to save nodes according to the level
    int output[110];
    int outLength = 0;
 
    printingReverseLevel(inputArray, output, &outLength);

   
    // printing nodes in reverse order
    for (int i = outLength - 1; i >= 0; i--)
    {
        //printf("%d ", output[i]);
        if (output[i] != -999)
        {
            if(output[i] != INT_MIN)
                printf("%d ", output[i]);
        }
        else
        {
            printf("\n");
        }
    }
}