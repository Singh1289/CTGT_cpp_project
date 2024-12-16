/*
    Program to implement a matrix calculator capable of performing various operations on matrices 
    of dynamic size. Handle dynamic memory allocation to manage matrices of varying sizes. The 
    operations include matrix addition, subtraction, multiplication, and transposition. Users should 
    be able to interactively input matrices and perform these operations. Use a 2D dynamic array to 
    represent matrices. Allow the user to define matrix dimensions and input values dynamically.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAT(matrix, i, j, cols) matrix[i * cols + j]

// Allocate memory for the matrix
void initializeMatrix(int rows, int cols, int **matrix) {
    *matrix = (int *)malloc(rows * cols * sizeof(int));
    if (*matrix == NULL) {
        printf("\nMemory allocation failed.");
        exit(0);
    }
}

// Taking input in matrix
void populateMatrix(int rows, int cols, int *matrix) {
    printf("\nEnter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter value at [%d][%d]: ", i, j);
            scanf("%d", &MAT(matrix, i, j, cols));
        }
    }
}

// Displaying the matrix
void displayMatrix(int rows, int cols, int *matrix) {
    printf("\nMatrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", MAT(matrix, i, j, cols));
        }
        printf("\n");
    }
}

// Function for matrix addition
void addMatrices(int rows, int cols, int *matrixA, int *matrixB, int *result) {
    //initializeMatrix(rows, cols, result); // Allocate memory for result
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            MAT(result, i, j, cols) = MAT(matrixA, i, j, cols) + MAT(matrixB, i, j, cols);
        }
    }
}

// Function for matrix subtraction
void subtractMatrices(int rows, int cols, int *matrixA, int *matrixB, int *result) {
   // initializeMatrix(rows, cols, result);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            MAT(result, i, j, cols) = MAT(matrixA, i, j, cols) - MAT(matrixB, i, j, cols);
        }
    }
}

// Function for matrix multiplication
void multiplyMatrices(int rowsA, int colsA, int colsB, int *matrixA, int *matrixB, int *result) {
    //initializeMatrix(rowsA, colsB, result);
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            MAT(result, i, j, colsB) = 0;
            for (int k = 0; k < colsA; k++) {
                MAT(result, i, j, colsB) += MAT(matrixA, i, k, colsA) * MAT(matrixB, k, j, colsB);
            }
        }
    }
}

// Function for matrix transposition
void transposeMatrix(int rows, int cols, int *matrix, int *result) {
   // initializeMatrix(cols, rows, result); // Note: Transpose changes dimensions
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            MAT(result, j, i, rows) = MAT(matrix, i, j, cols);
        }
    }
}

void takeRowCols(int *rows, int *cols) {
    printf("Enter the number of ROWS: ");
    scanf("%d", rows);
    printf("Enter the number of COLUMNS: ");
    scanf("%d", cols);
}

int main() {
    int rows, cols;
    takeRowCols(&rows, &cols);

    int *matrix = NULL;
    initializeMatrix(rows, cols, &matrix);
    populateMatrix(rows, cols, matrix);
    displayMatrix(rows, cols, matrix);

    int rowsB, colsB;
    takeRowCols(&rowsB, &colsB);

    int *matrix2 = NULL;
    initializeMatrix(rowsB, colsB, &matrix2);
    printf("\nEnter the elements of the second matrix: ");
    populateMatrix(rowsB, colsB, matrix2);
    displayMatrix(rowsB, colsB, matrix2);

    int *resultAdd = NULL;
    int *resultSub = NULL;

    if (rows == rowsB && cols == colsB) {
        initializeMatrix(rows, cols, &resultAdd);
        initializeMatrix(rowsB, colsB, &resultSub);

        printf("\nMatrix addition:\n");
        addMatrices(rows, cols, matrix, matrix2, resultAdd);
        displayMatrix(rows, cols, resultAdd);

        printf("\nMatrix subtraction:\n");
        subtractMatrices(rows, cols, matrix, matrix2, resultSub);
        displayMatrix(rows, cols, resultSub);
    } else {
        printf("\nMatrices cannot be added or subtracted because dimensions are different.");
    }

    // Matrix multiplication
    int *resultMul = NULL;
    if (cols == rowsB) {
        initializeMatrix(rows, colsB, &resultMul);


        printf("\nMatrix multiplication:");
        multiplyMatrices(rows, cols, colsB, matrix, matrix2, resultMul);
        displayMatrix(rows, colsB, resultMul);
    } else {
        printf("\nMatrices cannot be multiplied because the number of columns in 1st matrix and the number of rows in 2nd matrix are different.");
    }

    // Transposing the result matrix
    printf("\nTransposing the result matrix...");
    int *resultTranspose = NULL;
    initializeMatrix(rows, colsB, &resultTranspose);
    transposeMatrix(rowsB, cols, resultMul, resultTranspose);
    displayMatrix(colsB, rows, resultTranspose);

    // Free the memory
    free(matrix);
    free(matrix2);
    free(resultAdd);
    free(resultSub);
    free(resultMul);
    free(resultTranspose);
    matrix = matrix2 = resultAdd = resultSub = resultMul = resultTranspose = NULL;

    return 0;
}

