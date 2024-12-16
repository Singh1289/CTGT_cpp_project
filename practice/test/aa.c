#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
 
#define BITS 32
#define MAX_STR 1000

 
void intToBinary(int num, char *binary)
{
    unsigned int mask = 1 << (BITS - 1);
    for (int i = 0; i < BITS; i++)
    {
        binary[i] = (num & mask) ? '1' : '0';
        mask >>= 1;
    }
    binary[BITS] = '\0';
}
 
int hammingDistance(int x, int y)
{
    char binX[BITS + 1], binY[BITS + 1];
    intToBinary(x, binX);
    intToBinary(y, binY);
 
    int distance = 0;
    for (int i = 0; i < BITS; i++)
    {
        if (binX[i] != binY[i])
        {
            distance++;
        }
    }
 
    return distance;
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
 
int convertToInteger(const char *str)
{
    if (isalpha(str[0]) && str[1] == '\0')
    {
        return str[0];
    }
 
    int decimal = 0;
    if (strncmp(str, "0x", 2) == 0 || strncmp(str, "0X", 2) == 0)
    {
        decimal = (int)strtoul(str, NULL, 16);
    }
    else if (str[0] == '0' && str[1] != 'x' && str[1] != 'X')
    {
        decimal = (int)strtol(str, NULL, 8);
    }
    else
    {
        decimal = (int)strtol(str, NULL, 10);
    }
 
    return decimal;
}
 
void extractValue(char *str,int* arr, int* idx)
{
    int i = 0;
    char temp[20];
 
    if (str[0] == '{')
        str++;
 
    while (str[i] != '\0' && str[i] != '}')
    {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '{' || str[i] == '\'')
        {
            i++;
            continue;
        }
 
        if ((strncmp(str, "null", 4) == 0) || (strncmp(str, "NULL", 4) == 0))
        {
            i++;
            i++;
            i++;
            i++;
            continue;
        }
 
        int j = 0;
        while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}' && str[i] != '\'')
        {
            temp[j++] = str[i++];
        }
        temp[j] = '\0';
 
        if (j > 0)
        {
            arr[*idx] = convertToInteger(temp);
            (*idx)++;
        }
    }
}
 
int main()
{
    char in[MAX_STR];
    printf("Enter values: ");
    fgets(in, MAX_STR, stdin);
    in[strcspn(in, "\n")] = '\0';
 
    trim(in);
 
    if (strlen(in) < 1)
    {
        printf("Invalid Input..!");
        exit(-1);
    }
    int arr[3];
int idx = 0;
 
    extractValue(in,arr,&idx);

    if(idx<2){
        printf("Invalid Input..!");
        exit(-1);
    }
    // int x, y;
    // printf("Enter two integers x and y: ");
    // scanf("%d %d", &x, &y);
 
    int result = hammingDistance(arr[0], arr[1]);
    printf("The Hamming distance between %d and %d is: %d\n", arr[0], arr[1], result);
 
    return 0;
}