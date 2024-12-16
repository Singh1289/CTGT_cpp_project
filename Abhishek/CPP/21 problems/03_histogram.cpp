/*
Given an array of heights representing the heights of bars in a histogram, find the area of the largest rectangle that can be formed within the histogram.
Input:
An array of integers where each element represents the height of a bar in the histogram.
Output:
The area of the largest rectangle.
Constraints:
The number of bars can be up to 10^5.
Implement the solution with a time complexity of O(n).
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// Function to find the index of the previous smaller element for each element in the histogram
vector<int> prevSmaller(vector<int> &nums) {
    int n = nums.size();
    vector<int> result;
    stack<int> st;

    for (int i = 0; i < n; i++) {
        // Pop elements from stack while the current element is smaller than or equal to the top element
        while (!st.empty() && nums[st.top()] >= nums[i])
            st.pop();

        // If the stack is empty, it means no smaller element, so push -1
        int ele = (st.empty()) ? -1 : (st.top());
        result.push_back(ele);
        st.push(i);
    }

    return result;
}

// Function to find the index of the next smaller element for each element in the histogram
vector<int> nextSmaller(vector<int> &nums) {
    int n = nums.size();
    vector<int> result;

    stack<int> st;

    // Traverse the array from right to left
    for (int i = n - 1; i >= 0; i--) {
        // Pop elements from stack while the current element is smaller than or equal to the top element
        while (!st.empty() && nums[st.top()] >= nums[i])
            st.pop();

        // If the stack is empty, it means no smaller element, so push n (length of the array)
        int ele = (st.empty()) ? n : (st.top());
        result.push_back(ele);

        st.push(i);
    }

    // Reverse the result array to maintain correct order
    reverse(result.begin(), result.end());

    return result;
}

// Optimized approach to calculate the largest rectangle area using the previous and next smaller elements
int largestRectangleArea(vector<int> &heights) {
    int maxArea = 0;
    int area = 0;
    int n = heights.size();

    // Get the previous smaller and next smaller element indices for each height
    vector<int> ps = prevSmaller(heights);
    vector<int> ns = nextSmaller(heights);

    // Calculate area using the formula: height * (next smaller index - previous smaller index - 1)
    for (int i = 0; i < n; i++) {
        area = heights[i] * (ns[i] - ps[i] - 1);
        maxArea = max(maxArea, area);
    }

    return maxArea;
}

// Brute-force approach to calculate the largest rectangle area using a stack
int largestRectangleArea1(vector<int> &heights) {
    stack<int> st;
    int maxArea = 0;
    int n = heights.size();

    // Traverse through each bar in the histogram
    for (int i = 0; i <= n; i++) {
        // While the current bar is shorter than the bar at the top of the stack, calculate area
        while (!st.empty() && (i == n || heights[st.top()] >= heights[i])) {
            int height = heights[st.top()];
            st.pop();

            int width;
            if (st.empty()) {
              // If stack is empty, it means the current bar extends to the beginning
                width = i; 
            } else {
               // Width between the current bar and the last smaller bar
                width = i - st.top() - 1;
            }

            int area = width * height;
            maxArea = max(maxArea, area);
        }

        st.push(i);
    }

    return maxArea;
}

int main() {
    vector<int> heights = {6, 1, 7, 0, 3, 6, 4};

    
    int area = largestRectangleArea(heights);  
    // int area = largestRectangleArea1(heights); 
    
    cout << "The area of the largest rectangle is: " << area << endl;
    return 0;
}
