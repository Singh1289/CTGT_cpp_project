/*
Given a partially filled 9x9 Sudoku board, solve the puzzle by filling the empty cells with digits from 1 to 9. The solution must satisfy the following rules:
Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each 3x3 subgrid must contain the digits 1-9 without repetition.
Input:
A partially filled 9x9 Sudoku board (2D array).
Output:
The solved Sudoku board.
Constraints:
The board will have exactly one solution.

*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// check it cell is valid or not with num
bool isValid(vector<vector<int>>& board, int row, int col, int num)
{
    // Check row
    for (int i = 0; i < 9; i++)
        if (board[row][i] == num)
            return false;
            
    // Check column
    for (int i = 0; i < 9; i++)
        if (board[i][col] == num)
            return false;
            
    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++)
        for (int j = startCol; j < startCol + 3; j++)
            if (board[i][j] == num)
                return false;
                
    return true;

}

// solve the sudoku by recursion 
// if solution found the return true otherwies false 
// change the sudoku grid while solving
bool solveSudoku(vector<vector<int>>& board)
{
    int row, col;
    bool isEmpty = true;
    
    // Find an empty cell
    for (row = 0; row < 9; row++){
        for (col = 0; col < 9; col++)
            if (board[row][col] == 0)
            {
                isEmpty = false;
                break;
            }
        if(!isEmpty) break;
    }
            
    if (isEmpty)
        return true;
    
    // Fill the empty cell with digits from 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (isValid(board, row, col, num))
        {
            board[row][col] = num;
            
            if (solveSudoku(board))
                return true;
                
            // Backtrack
            board[row][col] = 0;
        }
    }   
    return false;
}

// Function to print the Sudoku
void printSudoku(vector<vector<int>>& board)
{
    cout<<"---------------------------------"<< endl;
    for (int i = 0; i < 9; i++)
    {   cout<<"[";
        for (int j = 0; j < 9; j++)
        {   if(j == 3 || j == 6) cout<<"| ";
             cout <<setw(2)<< board[i][j] << " ";}
        cout <<"]"<< endl;
        if(i == 2 || i == 5)cout<<"---------------------------------"<< endl;
    }
    
    cout<<"---------------------------------"<< endl;
}

int main()
{   
    // defining the sudoku and intailize with some values
    vector<vector<int>> board = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                                 {5, 2, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 8, 7, 0, 0, 0, 0, 3, 1},
                                 {0, 0, 3, 0, 1, 0, 0, 8, 0},
                                 {9, 0, 0, 8, 6, 3, 0, 0, 5},
                                 {0, 5, 0, 0, 9, 0, 6, 0, 0},
                                 {1, 3, 0, 0, 0, 0, 2, 5, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 7, 4},
                                 {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    
    // print sudoku
    printSudoku(board);

    cout<<"\n\nSolution: "<<endl;
    // if solution found then print the solution or other msg
    if(solveSudoku(board))
        printSudoku(board);
    else
        cout<<"No solution can be made."<<endl;



    return 0;
}