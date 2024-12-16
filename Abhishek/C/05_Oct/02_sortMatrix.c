/*
    Given an N x N matrix, write a program to sort the matrix in alternating ascending
    and descending order rowwise (i.e. first row is sorted in ascending order, second 
    row sorted in descending order, third row sorted in ascending order and so on.
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

// creating check flag to maintain ascending and decending order
int check = 1;

// populating the matrix with random numbers
void feedMatrix(int s,int mat[][s])
{
    printf("\nFeed matrix\n");
    srand(time(NULL));
    for(int i = 0;i<s; i++)
    {
        for(int j=0;j<s; j++)
        {
            mat[i][j]= rand() % 100;
        }
    }
}

// to diaplay matrix on console
void displayMatrix(int s,int mat[][s])
{
    
    for(int i = 0;i<s; i++)
    {
        for(int j=0;j<s; j++)
        {
            printf("%6d",mat[i][j]);
        }
        printf("\n");
    }
}

// sorting each row according to check flag 
void sortMatrix(int n, int mat[])
{
    int i, j;
    for(int i = 0;i<n-1; i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            
            if((check && mat[j] > mat[j+1]) || (!check && mat[j] < mat[j+1]))
            {
                int temp = mat[j];
                mat[j]= mat[j+1];
                mat[j+1]= temp;
              
            }
            
        }
    }
    check = (check == 1)? 0 : 1;
}


void main()
{
    // taiking the size of matrix
    int size;
    printf("\nEnter the size of the matrix : ");
    scanf("%d",&size);
    int matrix[size][size];

    // populating the matrix with random numbers
    feedMatrix(size,matrix);
    printf("\nDisplay matrix\n");
    // showing matrix with numbers
    displayMatrix(size,matrix);
    
    // sorting matrix alternate rows
    for(int i=0;i<size;i++)
    {
        sortMatrix(size,matrix[i]);
        
    }

    // displaying matrix after sorting
    printf("\nDisplay matrix after sort\n");
    displayMatrix(size,matrix);
    printf("\n End");
}