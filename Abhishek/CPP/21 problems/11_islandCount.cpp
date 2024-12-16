#include <iostream>
#include <vector>

using namespace std;
#define MAX_SIZE 100

//function to check if a cell is valid in the grid
bool isValid(int i, int j, int n, int m, vector<vector<int>> &grid)
{
    return (i >= 0 && i < n && j >= 0 && j < m && grid[i][j] == 1) ? true : false;
}

//function to perform DFS on a cell and mark all adjacent cells as visited
void dfs_Rec(int i, int j, int n, int m, vector<vector<int>> &grid)
{
    grid[i][j] = -1;

    if (isValid(i - 1, j, n, m, grid))
        dfs_Rec(i - 1, j, n, m, grid);

    if (isValid(i, j + 1, n, m, grid))
        dfs_Rec(i, j + 1, n, m, grid);

    if (isValid(i + 1, j, n, m, grid))
        dfs_Rec(i + 1, j, n, m, grid);

    if (isValid(i, j - 1, n, m, grid))
        dfs_Rec(i, j - 1, n, m, grid);
}

//function to count the number of islands using DFS algorithm
//Time complexity  O(n^2)
int numIslands(vector<vector<int>> &grid, int rr, int cc)
{
    int count = 0;
    for (int i = 0; i < rr; i++)
    {
        for (int j = 0; j < cc; j++)
        {
            if (grid[i][j] == 1)
            {
                count++;
                dfs_Rec(i, j, rr, cc, grid);
            }
        }
    }
    return count;
}

//Time complexity  O(n^2)
void takingInput(vector<vector<int>> &grid, int rr, int cc)
{
    for (int i = 0; i < rr; i++)
    {
        for (int j = 0; j < cc; j++)
        {
            cout << i << " " << j << " : ";
            cin >> grid[i][j];
        }
    }
}
// funtion to print grid matrix
//Time complexity  O(n^2)
void display(vector<vector<int>> &grid, int rr, int cc)
{
    cout<<endl;
    for (int i = 0; i < rr; i++)
    {
        cout << "| ";
        for (int j = 0; j < cc; j++)
        {
            cout << grid[i][j];
            if (j < cc - 1)
                cout << ", ";
        }
        cout << " |" << endl;
    }
}

int main()
{   
    // declaring the row and col vaeriables
    int row, col;
    while (true)
    {   
        // taking input from user 
        cout << "Enter no. of rows and column: ";
        cin >> row >> col;
        if (row > MAX_SIZE || col > MAX_SIZE)
            cout << "Both value must be under 100." << endl;
        else
            break;
    }

    // vector of vector is to store the grid 
    vector<vector<int>> grid(row, vector<int>(col));
    // functionall to fill the grid
    takingInput(grid, row, col);
    // display the grid on console
    display(grid, row, col);

    // print number of islands in the grid
    cout << "\nNumber of islands : " << numIslands(grid, row, col);

    return 0;
}