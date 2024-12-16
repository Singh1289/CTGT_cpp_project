/*
Problem: Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well. Do not use any built-in exponent function or operator. For example, do not use pow(x, 0.5).
Example: Input: 2
Output: 2
Input: 8
Output: 2
Input: A non-negative integer x such that 0 <= x <= 2^31 - 1
Output: Square root of x rounded down to the nearest integer as shown in example.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int mySqrt1(int x) {
   for( int i = 0; i < x/2 ; i++ ) {
     if(i*i == x) return i;
     else if(i*i > x) return i-1;
   }
}

int mySqrt(int x)
{
    if (x == 0 || x == 1)
    {
        return x;
    }
 
    int left = 1, right = x, result = 0;
 
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (mid <= x / mid)
        {
            result = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return result;
}

int isValidInput(const char *in) {
    if (strcmp(in, "NULL") == 0 || strcmp(in, "Null") == 0 || in[0] == '\0') {
        return 0;
    }

    int i = 0;
    if (in[0] == '-') {
        return 0;
    }
    
    if((in[0]>= 'A' && in[0]<='Z') ||( in[0]>='a' && in[0]<='z'))
    return 0;

    return 1;
}

int convertIntoDecimal(char *str)
{
    int decimal = 0;
    if (strncmp(str, "0x", 2) == 0 || strncmp(str, "0X", 2) == 0)
    {
        decimal = (int)strtoul(str, NULL, 16);
    }
    else if (str[0] == '0' && str[1] != 'x')
    {
        decimal = (int)strtol(str, NULL, 8);
    }
    else
    {
        decimal = (int)strtol(str, NULL, 10);
    }
    return decimal;
}

void convert(char *str, int *arr, int *idx)
{
    int i = 0;
    char temp[20];


    if (str[0] == '{')
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

        else if ((str[i] == '-' && isdigit(str[i + 1])) || isdigit(str[i]))
        {
            while (str[i] != ' ' && str[i] != ',' && str[i] != '\0' && str[i] != '}')
                temp[j++] = str[i++];
        }
        else if (str[i] == '\'' && isalpha(str[i + 1]) && str[i + 2] == '\'')
        {
            arr[*idx] = str[i + 1]; 
            (*idx)++;
            i += 3; 
            continue;
        }
        temp[j] = '\0';

        if (j > 0)
        {
            arr[*idx] = convertIntoDecimal(temp);
            (*idx)++;
        }
    }
}

int main() {
    char inputBuffer[100];
    printf("Input: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

  
    if (!isValidInput(inputBuffer)) {
        printf("Invalid input!\n");
        exit(1);
    }
   
    int inputArr[1];
    int idx = 0;

    convert(inputBuffer, inputArr, &idx);
    if(idx == 0 || inputArr[0]<0) { printf("Invalid input.!"); exit(1); }

    int sqrtResult = mySqrt1(inputArr[0]);
    printf("Output: %d\n", sqrtResult);
    return 0;
}