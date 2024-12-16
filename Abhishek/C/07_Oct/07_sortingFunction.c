/*
    Program to use an array of function pointers to sort an array of integers. 
    Implement different sorting algorithms (e.g., bubble sort, insertion sort) 
    and use the function pointer array to select the sorting algorithm at runtime. 
    Store pointers to these sorting functions in the array of function pointers 
    and allow the user to choose which sorting algorithm to use.
*/


#include<stdio.h>
#include<stdlib.h>

// function declaration
void insertionSort(int *arr,int n);
void bubbleSort(int *arr,int n);
void selectionSort(int *arr,int n);
void showMenu();

// taking input from user 
void feedArray(int *arr,int n)
{
    for(int i =0;i<n;i++)
    {
        printf("\n %d : ",i+1);
        scanf("%d",&arr[i]);
    }
}

// defining the function pointer
typedef void (*sortingPtr) (int * , int);


void main()
{
    // creating the function pointer array
    sortingPtr functionPtrList[3] = {insertionSort,bubbleSort,selectionSort}; 
    int choice;
    // taking the size of array
    int size;
    printf("\nEnter the size of array: ");
    scanf("%d",&size);
    int inputArr[size];

    // taking input in array
    feedArray(inputArr,size);

    do
    {
        // showing menu 
        showMenu();
        while (1)
        {   // taking valid choice from the menu
            printf("\nChoose one : ");
            scanf("%d",&choice);
            if(choice>0 && choice<5) break;

            printf("\nInvalid response.");
        }
        
        // call function 
        if(choice != 4)
        {
            functionPtrList[choice-1](inputArr,size);
            for(int i=0; i<size ;i++)
                printf("%d ",inputArr[i]);

            printf("\n");
        }

    }while(choice != 4);
    printf("\n~~~~ See you next time.~~~~");
}


// showing menu
void showMenu() {
    printf("\n~~~ Sorting Algo ~~~");
    printf("\n1. Insetion");
    printf("\n2. Bubble");
    printf("\n3. Selection");
    printf("\n4. Exit");
}

//for swaping 
void swap(int *a, int *b)
{
    int temp = *a;
    *a= *b;
    *b= temp;
}

// diffrent sorting algo
void insertionSort(int *arr,int n)
{
    int temp,i,j;
    for( i =1 ; i<n;i++)
    {
        temp= arr[i];
        for(j= i-1 ; j>=0 && temp<arr[j];j--)
            arr[j+1]=arr[j];

        arr[j+1]= temp;
    }
}

void bubbleSort(int *arr,int n)
{   // pick maxminum take it to back
    int flag;
   for(int i=1; i<n;i++)
    {
        flag=0;
        for(int j=0;j<n-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(&arr[j],&arr[j+1]);
                flag=1;
            }
        }
        if(flag==0) break;
    }
}


void selectionSort(int *arr,int n)
{   // pick minimum and bring to first
    int min;
    for(int i=0; i<n-1;i++)
    {
        min = i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[min]>arr[j]) min=j;
        }
        if(min != i)
        {
            swap(&arr[min],&arr[i]);
        }
    }

}