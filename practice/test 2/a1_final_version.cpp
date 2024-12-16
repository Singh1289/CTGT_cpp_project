/*
Problem:
Given a string s, print all the unique substrings that occur between any two
equal characters, excluding the two equal characters. If no such substrings
exist, print an appropriate message. A substring is defined as a contiguous
sequence of characters within the string.
Input:
A string s (0 ≤ length (s) ≤ 10^9).
Output:
If there are substrings between two equal characters, print each substring in
a format as depicted in examples. If no such substrings exist, print the
message: "No substrings found". If input isn't valid, print "Invalid input".
Instructions: Please adhere to the input and output formats as depicted in the examples. If
your approach is optimal, you will get full marks, otherwise half. Write before
your code, in comments, your name, total time and space complexity of your approach
(e.g ., // Name - Time complexity: O(N^2) and Space Complexity: O(N)).
----
-...
Examples:
Input: Enter a string: "abcab"
Output: Substrings between equal characters: ["bc", "ca"]
Input: Enter a string: "Monkey"
Output: No substrings found
*/

//Abhishek Pratap Singh. Time complexity O(N^2+K) and Space complexity O(K)
// where K is the number of subtrings

#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

void trimString(string &str)
{
    int start = 0, end = str.size() - 1;
    while (start <= end && (str[start] == ' ' || str[start] == '\t'))
    {
        start++;
    }
    while (start <= end && (str[end] == ' ' || str[end] == '\t'))
    {
        end--;
    }
    try
    {
        if (str[start] == '"')
            start++;
        else
            throw "error";
        if (str[end] == '"')
            end--;
        else
            throw "error";
        if (start > end)
            throw "error";
    }
    catch (...)
    {
        cout << "invalid input" << endl;
        exit(1);
    }
    str = str.substr(start, end - start + 1);
}


void printSubstrings(const string &s) {
    int n = s.length();
    set<string> uni;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                string tt = s.substr(i+1, j - i -1);
                if(tt != "")
                uni.insert("\""+tt+"\"");
            }
        }
    }
    cout<<"\nOutput: ";;
    if (uni.empty()) {
        cout << "No substring found" << endl;
    } else {
        int i = 1;
        cout << "Substring: [";
        for (const auto &a : uni) {
            cout << a;
            if (i < uni.size()) {
                cout << ", ";
            }
            i++;
        }
        cout << "]" << endl;
    }
}

int main() {
     string input;
     cout << "Input: Enter a string: ";
     getline(cin, input);

    trimString(input);
    if(input.size()==0){
        cout<<"Invalid input";
        return 0;
    }
    printSubstrings(input);
    return 0;
   
}



