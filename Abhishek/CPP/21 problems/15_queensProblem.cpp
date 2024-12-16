/*
The N-Queens Problem is the problem of placing N queens on an N x N chessboard such that no two queens threaten each other. Implement an algorithm that returns all solutions to the N-Queens puzzle.
For example:
Input: n = 4
Output:
[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Input:
An integer n representing the size of the chessboard.
Output:
A list of valid solutions where each solution is represented as a list of strings.
Constraints:
n can be up to 10 (for N-Queens Problem).
in cpp
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// modifying the 2D matrix accoding to the Queens possion by placing '-'
void modify(vector<vector<string>> &sol, int i, int j)
{
    int rows = sol.size();
    // Horizontal
    for (int col = 0; col < rows; col++)
    {
        if (col != j)
            sol[i][col] = "-";
    }

    // Vertical
    for (int row = 0; row < rows; row++)
    {
        if (row != i)
            sol[row][j] = "-";
    }

    // Bottom-left diagonal
    int x = i + 1, y = j - 1;
    while (x < rows && y >= 0)
    {
        sol[x][y] = "-";
        x++;
        y--;
    }

    // Bottom-right diagonal
    x = i + 1;
    y = j + 1;
    while (x < rows && y < rows)
    {
        sol[x][y] = "-";
        x++;
        y++;
    }

    // return true;
}

// printing the solution if found (if Q reaches to 0 means all queens are placed)
void printSolution(vector<vector<string>> &sol, int rows)
{
    int Q = rows-1;

    //cout<<endl;
    for (int i = 1; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (sol[i][j] == ".") 
            {
                sol[i][j] = "Q";
                Q--;
                modify(sol, i, j);
                break;
            }
        }
      // cout << i << " :" << sol[i][0] << " " << sol[i][1] << " " << sol[i][2] << " " << sol[i][3] << endl;
    }
   // cout<<"Q: "<<Q<< endl;

    if (Q == 0) 
    {
        cout << "Solution: " << endl;
        for (int i = 0; i < rows; i++)
        {
            cout << "[ ";
            for (int j = 0; j < rows; j++)
            {
                cout << sol[i][j] << " ";
            }
            cout << "]" << endl;
        }
        cout << endl;
    }
    return;
}

// function to find the all possible solutionby recursion
void findSolution(int rows)
{
    for (int i = 0; i < rows; i++)
    {
        vector<vector<string>> solution(rows, vector<string>(rows, "."));
        // placing Queen 
        solution[0][i] = "Q";
        // modify the matrix 
        modify(solution, 0, i);
        //recursive call
        printSolution(solution, rows);
    }
}

int main()
{
    // taking input for rows 
    int rows;
    cout << "Enter the number of rows : ";
    cin >> rows;

    // find and print all possible solution
    findSolution(rows);

    return 0;
}

