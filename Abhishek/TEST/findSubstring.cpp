/*
Problem: Given an array of strings, print all strings in the array that is a substring of another string in the array. You can print the answer in any order. A substring is a contiguous sequence of characters within a string.
Input: An array of strings (0 ≤ length(array) ≤ 10^9).
Output: An array containing those strings which are a substing of another string in the input array. Note that string "More" and "more" are different strings and neither is a substring of another.
Instructions: Please adhere to the input and output formats as depicted in the examples. If your approach is optimal, you will get full marks, otherwise half. Write before your code, in comments, your name, total time and space complexity of your approach (e.g., // Bhagyashree Patil - Time complexity: O(N+logN) and Space Complexity: O(N)).
Examples:
Input: array of strings = ["Code", "Load", "Firefighter", "Fire", "Desire"]
Output: array of substrings = ["Fire"]
Input: array of strings = ["Chop", "Stop", "Laptop", "Monkey"]
Output: Array of strings doesn't include any string which is a substring of another
*/

//Abhishek Pratap Singh - Time complexity: O(M*N^2) and Space Complexity: O(1).
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <string.h>
using namespace std;

bool flag = false;

void trimString(string& str){
   // cout<<"token: "<<str<<endl;
    int start = 0, end = str.length() - 1;
    while(start<end && (str[start]==' ' || str[start]=='\t' || str[start]=='\n' || str[start]=='\r')) start++;
    while(start<end && (str[end]==' ' || str[end]=='\t' || str[end]=='\n' || str[end]=='\r')) end--;
    try{
    if(flag)
    {if(str[start] == '"') start++; else throw "error";
    if(str[end] == '"') end--; else throw "error";}
    if(start>end)  str = ""; 
    else
    str = str.substr(start, end - start + 1);
    }catch(...){
        cout<<"Invalid input string provided.2"<<endl;
        exit(-1);
    }
}

void convertIntoArray(vector<string> &array, string str, int &idx)
{
    flag = true;
    size_t start = str.find('[');
    size_t end = str.find(']');

    if (start == string::npos || end == string::npos || start >= end)
    {
        cout << "Invalid input: b " << endl;
        exit(-1);
    }

    string content = str.substr(start + 1, end - start - 1);

    if (content.length() < 1)
    {
        cout << "Invalid input: b " << endl;
        exit(-1);
    }
    size_t pos = 0;
    while ((pos = content.find(',')) != string::npos)
    {
        string token = content.substr(0, pos);
        trimString(token);
        if (token.length() < 1)
        {
            cout << "Invalid input: c " << endl;
            exit(-1);
        }
        //cout<< "token: "<<token<<endl;
        // token = token.substr(1, token.length() - 1);
        array.push_back(token);
        idx++;
        content.erase(0, pos + 1);
    }

    trimString(content);
    if (content.length() <1)
    {
        cout << "Invalid input: d " << endl;
        exit(-1);
    }
    //content = content.substr(1, content.length() - 1);
    array.push_back(content);
    idx++;
}

vector<string> findSubstring(vector<string>& array) {
    vector<string> substrings;
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array.size(); j++) {
            if (i != j && array[j].find(array[i])!= string::npos) {
                substrings.push_back(array[i]);
                break;
            }
        }
    }
    if (substrings.empty()) {
        substrings.push_back("Array of strings doesn't include any string which is a substring of another");
    }
    
    return substrings;
}


int main()
{
    string input;
    cout << "Enter a string: ";
    getline(cin, input);
    trimString(input);
    if(input.length()==0){
        cout << "Invalid input" << endl;
        return 0;
    }
    vector<string> arr;
    int idx = 0;

    convertIntoArray(arr,input,idx);
    if(arr.size()==0){
        cout << "Invalid input" << endl;
        return 0;
    }
    // cout << "Array of strings: ";
    // for (int i = 0; i < arr.size(); i++)
    // {
    //     cout << arr[i] << " ";
    // }
    // cout<<endl;

    vector<string> res = findSubstring(arr);
    cout<<"Output: [";
    for(int i = 0; i < res.size(); i++)
    {
        cout<<"\""<<res[i]<<"\"";
        if(i< res.size()-1)cout<<", ";
    }
    cout<<"]"<<endl;

    return 0;

}
// ["app", "Application", "vacation", "intution", "institution", "mention", "apPlIcation", "aPPle", "1", "i"]

