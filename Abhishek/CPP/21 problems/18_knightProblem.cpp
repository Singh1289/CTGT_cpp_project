/*
Given an n x n chessboard and a starting position, write a program to find a solution to the Knight’s Tour problem. The knight must visit every square of the board exactly once, moving in an "L" shape. The solution should be represented as a sequence of board positions.
For example:
Input: n = 5, start at (0,0)
Output: A possible sequence of moves where every square is visited once.
Input:
An integer n representing the size of the chessboard.
The starting position of the knight as a tuple (x, y).
Output:
A sequence of positions the knight must move to, visiting every square exactly once, or "no solution" if no such sequence exists.
Constraints:
1 <= n <= 10.

*/

#include <iostream>
#include <vector>
#include <iomanip> 
using namespace std;

// Define 'chess' as a 2D vector 
#define chess vector<vector<bool>> 

// Define 'moves' as a 2D vector of integers 
#define moves vector<vector<int>> 

// Global variables to track the total number of cells and whether a solution is found
int cell_count = 0;
bool solution_found = false;

// Function to check if a cell (x, y) is safe to visit
// A cell is safe if it is within bounds and not already visited
bool isSafe(chess& board, int x, int y) {
    // Get the size of the chessboard (n x n)
    int n = board.size();  
    // Return true if within bounds and not visited
    return (x >= 0 && x < n && y >= 0 && y < n && !board[x][y]); 
}

// Recursive function to perform the knight's tour
void move_rec(chess& board, moves& sol, int count, int x, int y) {
    // Base case: if the knight has visited all the cells
    if (count == cell_count) {
        solution_found = true;  // Mark solution as found
        cout << "Solution Exists:" << endl;

        // Output the solution (the tour path)
        for (auto row : sol) {
            cout << "[ ";
            for (auto c : row) {
                cout << setw(3) << ((c == -1) ? 25 : c) << " ";  
            }
            cout << "]" << endl;
        }

        // Exit the program once a solution is found
        exit(0);
    }

    // Mark the current cell (x, y) as visited
    board[x][y] = true;

    // Mark the current cell in the solution path with the current count
    sol[x][y] = ++count;

    // Try all possible knight moves 

    // Move down-right 
    if (isSafe(board, x + 2, y + 1)) 
        move_rec(board, sol, count, x + 2, y + 1);

    // Move right-down 
    if (isSafe(board, x + 1, y + 2))
        move_rec(board, sol, count, x + 1, y + 2);

    // Move up-right 
    if (isSafe(board, x - 1, y + 2))
        move_rec(board, sol, count, x - 1, y + 2);

    // Move up-right 
    if (isSafe(board, x - 2, y + 1))
        move_rec(board, sol, count, x - 2, y + 1);

    // Move up-left 
    if (isSafe(board, x - 2, y - 1))
        move_rec(board, sol, count, x - 2, y - 1);

    // Move left-up 
    if (isSafe(board, x - 1, y - 2))
        move_rec(board, sol, count, x - 1, y - 2);

    // Move left-down
    if (isSafe(board, x + 1, y - 2))
        move_rec(board, sol, count, x + 1, y - 2);

    // Move down-left 
    if (isSafe(board, x + 2, y - 1))
        move_rec(board, sol, count, x + 2, y - 1);

    // Backtrack: unmark the current cell (x, y) and reset the solution path
    board[x][y] = false;
    sol[x][y] = -1;
}

// Function to start the knight's tour from the given (x, y) position
void knightTour(chess& board, moves& sol, int count, int x, int y) {
    // Start the recursive knight's tour
    move_rec(board, sol, count, x, y);

    // Check if no solution is found after trying all possibilities
    int n = board.size();
    if (!solution_found)
        cout << "Solution does not exist for (" << x << ", " << y << ") position in " << n << "*" << n << " chessboard." << endl;

    return; // End the function
}

int main() {
    int row, x, y;

    // Prompt the user to input the size of the chessboard (number of rows)
    cout << "Enter number of rows: ";
    cin >> row;

    // Prompt the user to input the starting position of the knight (x, y)
    cout << "Enter the starting position (x, y): ";
    cin >> x >> y;

    // Initialize the chessboard and the solution path matrix
    moves solution(row, vector<int>(row, -1));   
    chess board(row, vector<bool>(row, false)); 

    // Set the total number of cells to be visited (cell_count = n^2 - 1)
    cell_count = (row * row) - 1;

    // Start the knight's tour from the given starting position (x, y)
    knightTour(board, solution, 0, x, y);

    return 0; 
}
