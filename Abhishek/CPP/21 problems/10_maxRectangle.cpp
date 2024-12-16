/*
Given a binary matrix, find the area of the largest rectangle that can be formed using only 1s. The rectangle must be formed from adjacent 1s.
For example:
Input:
1 0 1 0 0  
1 0 1 1 1  
1 1 1 1 1  
1 0 0 1 0
Output: 6
Input:
A binary matrix of n x m.
Output:
The area of the largest rectangle of 1s.
Constraints:
The matrix dimensions can be up to 10^5.
*/

/*
    * Change the input matrix to no. or histograms have sum of values of above columns
    * then find max height at each row
    * iterate over all rows and find the maximum height

*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Function to create histograms for each row
void makeHistograms(vector<vector<int>>& mat, vector<vector<int>>& histograms) {
    int n = mat.size();  
    int m = mat[0].size();  

    // Iterate through each row to build the histograms
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // For the first row, the histogram is equal to the matrix itself
            if (i == 0)
                histograms[i][j] = mat[i][j];
            else
                // If current element is 1, increase the histogram value from the previous row
                histograms[i][j] = (mat[i][j] == 0) ? 0 : histograms[i - 1][j] + mat[i][j];
        }
    }
}

// Function to display a 2D grid (matrix)
void display(vector<vector<int>>& grid, int rows, int cols) {
    cout << endl;
    // Loop through the rows and columns to print the grid
    for (int i = 0; i < rows; i++) {
        cout << "| ";
        for (int j = 0; j < cols; j++) {
            // Print the current element
            cout << grid[i][j];  
            if (j < cols - 1)    
                cout << ", ";
        }
        cout << " |" << endl;  // End of the row
    }
}

// Function to calculate the maximum rectangle area in a histogram (given heights)
int getMaxArea(vector<int>& heights) {
    // Stack to store indices of histogram bars
    stack<int> st;
    // Variable to store the maximum area found  
    int maxArea = 0; 
     // Number of bars in the histogram
    int n = heights.size(); 
    // Loop through each bar in the histogram
    for (int i = 0; i <= n; i++) {
        // While the current bar is smaller than the top of the stack, calculate area
        while (!st.empty() && (i == n || heights[st.top()] >= heights[i])) {
            int height = heights[st.top()];  
            st.pop();  

            // Calculate the width of the rectangle
            int width;
            if (st.empty()) {
                // If stack is empty, width is the full length
                width = i;  
            } else {
                // Width is the difference between current index and top of stack
                width = i - st.top() - 1;  
            }

            // Calculate the area and update the maximum area if needed
            int area = width * height;
            // Update maxArea if a larger area is found
            maxArea = max(maxArea, area);  
        }

        // Push the current index to the stack
        st.push(i);
    }
    return maxArea; 
}

// Function to find the maximum rectangle of 1s in the binary matrix
int findMaxArea(vector<vector<int>>& mat) {
    int n = mat.size();  
    int m = mat[0].size();  
    int maxArea = 0;  

    // Create a histogram matrix to store the heights of bars for each row
    vector<vector<int>> histograms(n, vector<int>(m, 0));
    // Generate the histogram matrix
    makeHistograms(mat, histograms);  

    // Display histograms for debugging purposes
    cout << "Histograms:";
    display(histograms, n, m);

    // Loop through each row of the histogram to calculate the maximum area
    for (int i = 0; i < n; i++) {
        // Calculate max area for the current row's histogram
        int area = getMaxArea(histograms[i]);  
        // Update maxArea if a larger area is found
        maxArea = max(maxArea, area);  
        // cout << "Row " << i << ": Max Area = " << area << endl; 
    }
    // Return the largest rectangle area
    return maxArea;  
}

int main() {
    int row , col ;  // row and column count
    cout << "Number of matrix size (row*col): ";
    cin >> row >> col;  

    // Create a matrix of 0s with user-defined size (row x col)
    vector<vector<int>> matrix(col, vector<int>(row, 0));

    // Prompt the user to enter the matrix elements
    cout << "Enter the elements of matrix: ";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << i << " " << j << " : ";
            cin >> matrix[i][j];  // Take matrix element input from the user
        }
    }

    // Display the input matrix
    display(matrix, row, col);
    cout << endl;

    // Call findMaxArea to calculate the largest rectangle area of 1s in the matrix
    int max_area = findMaxArea(matrix);
    cout << "\nThe area of largest rectangle of 1s is: " << max_area << endl;

    return 0;
}
