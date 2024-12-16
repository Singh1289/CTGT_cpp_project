/*
Given a string s and a list of words, determine if the string can be segmented into space-separated words that are found in the list.
For example:
"applepenapple" and the word dictionary ["apple", "pen"] should return true.
"catsandog" and the word dictionary ["cats", "dog", "sand", "and", "cat"] should return false.
Input:
A string s and a list of words (strings).
Output:
Return true if the string can be segmented, otherwise false.
Constraints:
The length of s can be up to 10^5.

*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

int check(string word, int index, string input)
{   
    // Find word starting from the 'index' position.
    auto index1 = input.find(word, index);  
    // If the word is not found.
    if (index1 == string::npos)  
    {
        return -1;
    }
    return index1; 
}

bool findwords(string input, vector<string>& wordDict)
{   // Initialize index to start from the beginning of the input string.
    int index = 0;  
    
    // Loop through each word to check if it exists in input.
    for (int i = 0; i < wordDict.size(); i++)
    {
        // Get the index of the word.
        int foundIndex = check(wordDict[i], index, input);  
        
        if (foundIndex == -1)
        {
            return false;
        }
        else
        {
            // Move index forward to check for the next word.
            index = foundIndex + wordDict[i].length();
        }
    }
    // If all words were found in sequence, return true.
    return true;
}

int main()
{
    string input;
    int n;
    cout << "Enter the string s: ";
    cin >> input;
 
    cout << "Enter the number of words in the dictionary: ";
    cin >> n;
 
    vector<string> wordDict(n);
    cout << "Enter the words in the dictionary: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> wordDict[i];
    }
 
    bool result = findwords(input, wordDict);
   
    cout << "Result: " << (result ? "true" : "false") << endl;  
 
    return 0;
}