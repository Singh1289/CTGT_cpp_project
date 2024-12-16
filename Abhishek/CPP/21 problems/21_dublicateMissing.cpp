/*
Problem: Given a list of numbers, which represents a set of numbers ranging
from m to n (inclusive), where in ml is the length of the list. Due to an error, at least one number from the set is duplicated, and at least one other number is missing. Find the duplicated number(s) and the missing number(s).
Input:
A list of numbers ranging from m ton such that m <= n and m <= 10^19 and n <= 10^19. Please follow the same input format as depicted in the examples.
Output:
Print a list of pair(s) of duplicate number(s) and the missing number(s) such that each pair is represented as (duplicate number, missing number). Follow the same output format as depicted in the examples.

Examples:
Input: [1,2,2,4]
Output: [(2, 3)]
Input: [3, 1, 2, 5, 3]
Output: [(3, 4)]
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <set>
#include <climits>
using namespace std;


// Function to find duplicate and missing numbers in the sorted array
void findDuplicateAndMissing(vector<unsigned long long> nums) {
     // Set to store pairs of duplicate and missing numbers
    set<pair<size_t, size_t>> res; 
    size_t duplicate, missing;
    // Initialize to an invalid value
    duplicate = missing = -999;  

    // Iterate through the array to find duplicates and missing numbers
    for (size_t i = 1; i < nums.size(); ++i) {
        // Check for duplicate
        if (nums[i] == nums[i - 1]) {  
            duplicate = nums[i];
        }
        // Check for missing number
        if (nums[i] != nums[i - 1] + 1) {  
            missing = nums[i - 1] + 1;
        }

        // If both duplicate and missing numbers are found, insert them as a pair into the set
        if (duplicate != -999 && missing != -999)
            res.insert({duplicate, missing});
    }

    // If duplicate and missing numbers are found, print them
    if (res.size() > 0) {
        int k = 1;
        cout << "[";
        for (auto &p : res) {
            cout << "(" << p.first << "," << p.second << ")";
            if (k < res.size()) cout << ", ";
            k++;
        }
        cout << "]" << endl;
    } else {
        // If no duplicates or missing numbers found, print a message
        cout << "No duplicates or missing numbers found." << endl;
    }
}

// Function to convert a string into a decimal value based on its format (hexadecimal, octal, or decimal)
unsigned long long toDecimal(const string& str) {
    unsigned long long decimal = 0;
    if (str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X") {
        decimal = stoull(str, nullptr, 16);  // Convert hexadecimal to decimal
    } else if (str[0] == '0' && str[1] != 'x') {
        decimal = stoull(str, nullptr, 8);  // Convert octal to decimal
    } else {
        decimal = stoull(str);  // Convert decimal string to decimal value
    }
    return decimal;
}

// Function to trim whitespace from the start and end of a string
string trimString(const string& str) {
    size_t start = str.find_first_not_of(' ');  
    size_t end = str.find_last_not_of(' ');  
    // Return the trimmed string
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);  
}

// Function to convert the input string into an array of unsigned long long integers
void convertIntoArray(vector<unsigned long long> &array, const string &str, int &idx)
{
    long temp = 0;
    size_t start = str.find('[');  // Find start of the array
    size_t end = str.find(']');    // Find end of the array
    if (start == string::npos || end == string::npos || start >= end) {
        cout << "Invalid input2: " << endl;
        exit(-1);  // Exit if the array format is incorrect
    }

    // Extract the content inside the square brackets
    string content = str.substr(start + 1, end - start - 1);
    trimString(content);  // Trim the content

    size_t pos = 0;
    // Split the content by commas and convert each element to decimal
    while ((pos = content.find(',')) != string::npos) {
         // Get the token between commas
        string token = content.substr(0, pos); 
        trimString(token);  
        // Ensure it's not "NULL"
        if (token != "NULL" && token != "null" && token != "Null") {  
            if (token == "-0") {  // Handle invalid input
                cout << "Invalid input ";
                exit(-1);
            }
            temp = toDecimal(token);  // Convert the token to decimal
            array.push_back(temp);  // Add the converted value to the array
            idx++;  // Increment the index
        } else {
            cout << "Invalid input ";
            exit(-1);  
        }
        // Remove the processed token
        content.erase(0, pos + 1);  
    }

    trimString(content);  // Trim the remaining content
    // Ensure it's not "NULL"
    if (content != "NULL" && content != "null" && content != "Null") {  
        temp = toDecimal(content);  // Convert the final element
        array.push_back(temp);  // Add it to the array
        idx++;  // Increment the index
    } else {
        cout << "Invalid input ";
        exit(-1);  
    }
}

int main() {
    string buffer;
    cout << "Input: ";
    getline(cin, buffer);  

     // Trim leading and trailing spaces
    buffer = trimString(buffer); 
    if (buffer.empty()) {
        cerr << "Invalid input." << endl;
        // Exit if input is empty
        return -1;  
    }

    vector<unsigned long long> arr;
    int idx = 0;
    // Convert the input string to an array
    convertIntoArray(arr, buffer, idx);  
    if (arr.empty()) {
        cerr << "Invalid input." << endl;
        return -1;  
    }

    // Print the array
    // for (const auto& num : arr) {
    //     cout << num << " ";
    // }
    // cout << endl;

    // Sort the array
    sort(arr.begin(), arr.end()); 
     // Find duplicates and missing numbers 
    findDuplicateAndMissing(arr); 

    return 0;
}
