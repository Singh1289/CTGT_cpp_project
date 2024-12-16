

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000

int convertIntoDecimal(char *str)
{
    int decimal = 0;
    int len = strlen(str);

    if(strncmp(str,"0x",2)==0 || strncmp(str,"0X",2)==0)
        decimal = (int)strtol(str, NULL,16);
    
    else if(str[0] == '0')
        decimal = (int)strtol(str, NULL, 8);

    else
        decimal = (int)strtol(str, NULL,10);
    

    return decimal;
}

void convert(char *str, int *arr, int *idx)
{
    int i = 0;
    char temp[10];
    if (str[0] == '{')
        str++;
    while (str[i] != '}' || str[i] != '\0')
    {
        int j = 0;
        if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
        {
            while (str[i] != ' ' || str[i] != ',')
                temp[j++] = str[i++];
        }
        else if (str[i] == '0')
        {
            while (str[i] != ' ' || str[i] != ',')
                temp[j++] = str[i++];
        }
        else if (str[i] > 0 && str[i] < 9)
        {
            while (str[i] != ' ' || str[i] != ',')
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

void main()
{
    char buf[MAX_SIZE];
    printf("Input: ");
    fgets(buf, MAX_SIZE, stdin);
    buf[strcspn(buf, "\n")] = '\0';

    int inputArr[MAX_SIZE];
    int idx = 0;
    convert(buf, inputArr, &idx);

    printf("Output: ");
    for (int i = 0; i < idx; i++)
    {
        printf("%d ", inputArr[i]);
    }
    printf("\n");
}