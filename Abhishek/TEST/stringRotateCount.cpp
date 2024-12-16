/*
Problem: Given two strings, s1 and s2, determine the minimum number of rotations
required to make s1 equal to s2 by applying left-to-right shifts on s1.
A left-to-right shift involves moving the leftmost character of the string
to the rightmost position. For example: a left-to-right shift on "abcde"
results in "bcdea". Print the number of shifts required to make s1 identical
to s2 after a finite number of rotations. If no number of shifts can make the
strings equal, print appropriate message.
Input: Two strings, s1 and s2 where length of both the string is no more than 10^9.
Output: The number of left-to-right shifts required to transform s1 into s2.
Instructions: Please adhere to the input and output formats as depicted in the examples.
Examples:
Input: s1 = "abcde"
s2 = "deabc"
Output: Left-to-Right Shifts Required to make s1 identical to s2 = 3
Input: s1 = "abcde"
s2 = "abced"
Output: No rotation of s1 will make it identical to s2.
*/

#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
using namespace std;

void trimString(string &str)
{
    int start = 0;
    int end = str.size() - 1;
    while ((start < end && isspace(str[start]) ))
        start++;
    while ((start < end && isspace(str[end])))
        end--;
    if(str[start] == '"')start++;
    if(str[end] == '"')end--;
    
    str = str.substr(start, end - start + 1);
    return;
}

bool validate_string(string &s1, string &s2){
    if (s1.length() != s2.length()) {
        return false; 
    }
    string temp = s1 + s1;
    return temp.find(s2) != string::npos;

}

int countRotations(string &a, string &b){
    int count = 0;

    if(!validate_string(a, b)){
        throw "No rotation of s1 will make it identical to s2.";
    }

    char s1[1024];
    char s2[1024];
    strcpy(s1, a.c_str());
    strcpy(s2, b.c_str());

    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) {
        return -1; 
    }

    while (strcmp(s1, s2) != 0) {
        char temp = s1[0];
        for (int i = 0; i < len1 - 1; i++) {
            s1[i] = s1[i + 1];
        }
        s1[len1 - 1] = temp;
        count++;
    }
    return count;
}

int main()
{
    try
    {
        string s1;
        cout << "Enter string s1: ";
        getline(cin, s1);
        trimString(s1);

        string s2;
        cout << "Enter string s2: ";
        getline(cin, s2);
        trimString(s2);
        if(s1.size() != s2.size() || s1.size()<1 || s2.size()<1 ){
            throw "Both strings must be at least 1 characters long and have same lenght.";  
        }

        int count = countRotations(s1, s2);
        if (count == -1) {
            throw "Both strings must be of same length.";
        }
        else  if(count == 0){
            cout << "Output: No Rotation is required both string are equal." << endl;
        }else{
        cout << "Output: Left-to-Right Shifts Required to make s1 identical to s2 : " << count << endl;}

    }
    catch (const char* msg)
    {
        cout << "Output: " << msg << endl;
    }
    catch (...){
        cout << "An unexpected error occurred." << endl;
    }

    return 0;
}