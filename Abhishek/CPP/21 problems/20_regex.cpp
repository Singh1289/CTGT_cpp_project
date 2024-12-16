/*
Implement regular expression matching with support for '.' and '*' where:
. Matches any single character.
* Matches zero or more of the preceding element.
For example:
Input: s = "aa", p = "a*"
Output: true (because a* matches "aa")
Input:
A string s representing the input string.
A string p representing the pattern.
Output:
true if the pattern matches the string, otherwise false.
Constraints:
The length of s can be up to 100.
The length of p can be up to 100.

*/

#include<iostream>
#include<string>
#include <vector>

using namespace std;

// Recursive helper function for regex matching
bool isMatchRecursive(const string &s, const string &p, int i, int j) {
    // If the pattern is completely traversed, check if the string is also fully traversed
    if (j == p.length()) {
        return i == s.length();
    }

    // Check if the current characters match or if the pattern has a dot ('.')
    bool firstMatch = (i < s.length() && (s[i] == p[j] || p[j] == '.'));

    // If the next character in the pattern is '*', there are two cases to consider:
    // 1. We skip the current character and '*' (i.e., treat '*' as matching zero occurrences).
    // 2. We move to the next character in the string if there is a match (i.e., '*' matches one or more occurrences).
    if (j + 1 < p.length() && p[j + 1] == '*') {
        // Case 1: '*' matches zero occurrences.
        // Case 2: '*' matches one or more occurrences.
        return isMatchRecursive(s, p, i, j + 2) ||  
               (firstMatch && isMatchRecursive(s, p, i + 1, j)); 
    } else {
        // If no '*', simply check if the current characters match and move both string and pattern forward
        return firstMatch && isMatchRecursive(s, p, i + 1, j + 1);
    }
}

// Wrapper function to start the matching process
bool isMatch(string s, string p) {
    // Start with the first characters of both string and pattern
    return isMatchRecursive(s, p, 0, 0); 
}

int main() {
    string input, regex;
    cout << "Enter the string: ";
    cin >> input; // Input string for matching
    cout << "Enter the regex (\".\" ,\" *\"): ";
    cin >> regex; // Input regular expression pattern

    // Output whether the string matches the pattern
    cout << "Output: " << (isMatch(input, regex) ? "true" : "false") << endl;

    return 0;
}


// bool checkRegex(string s, string reg){
//     int m = s.length();
//     int n = reg.length();
//     int pos = s.find("*");
//     if(pos != -1){
//         s = s.substr(0, pos);
//         reg = reg.substr(0, pos-1);
//         if(reg.length() == 1 && reg[0] == '.'){
//             if(s[0]<= 32 && s[0]>= 126)
//                 return true;
//             else
//                 return false;           
//         }
//         else{
//             pos = s.find(reg);
//             if(pos == -1 || pos== 0) return true; else return false;
//         }
//     }else{
//         return false;
//     }
// }
