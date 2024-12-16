#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to display 
void displayCombo(int *arr, int len)
{
    printf("{ ");
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("}\n");
}

// Recursive function to find all possible combinations
void findCombos(int inputNum, int currentSum, int startNum, int *comboArr, int pos)
{
    if (currentSum == inputNum)
    {
        displayCombo(comboArr, pos); 
        return;
    }

    for (int i = startNum; i <= inputNum; i++)
    {
        if (currentSum + i > inputNum) 
            break;

        comboArr[pos] = i;   
        findCombos(inputNum, currentSum + i, i, comboArr, pos + 1);
    }
}

// function tto genrate combination or start point of recursion 
void generateCombos(int num)
{
    int combinationArr[num]; 
    findCombos(num, 0, 1, combinationArr, 0); 
}

int main()
{
    char inputStr[8];
    printf("Enter a Number: ");
    fgets(inputStr, sizeof(inputStr), stdin);

    int num;
    if (strncmp(inputStr, "0x", 2) == 0 || strncmp(inputStr, "0X", 2) == 0)
        num = strtol(inputStr, NULL, 16); 
    else
        num = strtol(inputStr, NULL, 10);

    printf("Combinations: \n");
    generateCombos(num); 

    return 0;
}
