/*
Given a string s, partition the string such that every substring is a palindrome. Return all possible palindrome partitioning of the string.
For example:
"aab" → [["a", "a", "b"], ["aa", "b"]]
Input:
A string s.
Output:
All possible palindrome partitioning of the string.
Constraints:
The length of the string can be up to 10^5.
in cpp
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        
        // DP table to store whether a substring s[i..j] is a palindrome
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        
        // Every single character is a palindrome
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }
        
        // Fill the DP table for substrings of length >= 2
        for (int length = 2; length <= n; length++) {
            for (int i = 0; i <= n - length; i++) {
                int j = i + length - 1;
                if (s[i] == s[j]) {
                    // Check for palindromes
                    dp[i][j] = (length == 2) || dp[i + 1][j - 1]; 
                }
            }
        }

        // Vector to store all possible palindrome partitions
        vector<vector<string>> result;
        
        // Temporary vector to store the current partition
        vector<string> current;
        
        // Start the depth-first search to find all palindromic partitions
        dfs(0, s, dp, current, result);
        return result;
    }

private:
    // Helper function to perform DFS and find all palindromic partitions
    void dfs(int start, const string& s, const vector<vector<bool>>& dp, 
             vector<string>& current, vector<vector<string>>& result) {
        
        // If we have processed the whole string, add the current partition to result
        if (start == s.size()) {
            result.push_back(current);
            return;
        }
        
        // Try all possible end positions for the substring
        for (int end = start; end < s.size(); end++) {
            // If the substring s[start..end] is a palindrome
            if (dp[start][end]) { 
                // Add it to current partition
                current.push_back(s.substr(start, end - start + 1));
                // Recurse with the remaining string 
                dfs(end + 1, s, dp, current, result); 
                
                // Backtrack: remove the last added string from current partition
                current.pop_back(); 
            }
        }
    }
};

int main() {
    string s = "abcd"; // Input string
    Solution solution;
    
    // Get all palindromic partitions of the string
    vector<vector<string>> result = solution.partition(s);

    // Print all the palindromic partitions
    for (const auto& partition : result) {
        cout << "[ ";
        for (const auto& str : partition) {
            cout << "\"" << str << "\" ";
        }
        cout << "]" << endl;
    }
    return 0;
}

// string s = "aabbccddd";

