#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000

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

    while (str[i] != '\0' && str[i] != '}' ) 
    {
        if (str[i] == ' ' || str[i] == ',')  
        {
            i++;
            continue;
        }

        int j = 0;

        //printf("\n i: %d", i);
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
        else if ((str[i]== '-' &&  (str[i+1] >= '0' && str[i+1] <= '9'))|| (str[i] >= '0' && str[i] <= '9'))
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


// Merge Sort: Merge two subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(int arr[], int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);         
        mergeSort(arr, mid + 1, right); 

        merge(arr, left, mid, right);      
    }
}

void removeDublicates(int arr[], int *idx){
    
    int j = 0;
    for (int i = 0; i < (*idx) - 1; i++) {
        if (arr[i]!= arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[*idx - 1];
    *idx = j;
}


int main()
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
//_________________________________________________________________
//_________________________________________________________________

    mergeSort(inputArr, 0, idx - 1);

    printf("After Sort: ");
    for (int i = 0; i < idx; i++)
    {
        printf("%d ", inputArr[i]);
    }
    printf("\n");
    
//_________________________________________________________________
//_________________________________________________________________

    removeDublicates(inputArr, &idx);

    printf("After remove : ");
    for (int i = 0; i < idx; i++)
    {
        printf("%d ", inputArr[i]);
    }
    printf("\n");

    return 0;
}
