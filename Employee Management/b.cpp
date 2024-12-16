
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

void trimString(string& str){

    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if (start == string::npos || end == string::npos) {
        str = "";
    } else {
    if(str[start] != '"' || str[end]!= '"')
    {
        cout<<"ERROR: Invalid input string";
        exit(0);
    }
        start++;   end--;
        str = str.substr(start, end - start+1 );
    }
}
void findPalindromes(const string& str, int left, int right, unordered_set<string>& set) {
    while (left >= 0 && right < str.length() && str[left] == str[right]) {
     
        set.insert("\""+str.substr(left, right - left + 1)+"\"");
        --left;
        ++right;
    }
}
 
unordered_set<string> findSubString(const string& str) {
    unordered_set<string> sets;
 
 
    for (int i = 0; i < str.length(); ++i) {
        findPalindromes(str, i, i, sets);
        findPalindromes(str, i, i + 1, sets);
    }
 
    return sets;
}

int main() {
    //string s = "google";
    string input;
    cout<<"Enter a string: ";
    getline(cin, input);
    trimString(input);

    if(input.size()==0){
        cout<<"Invalid input!"<<endl;
        return 0;
    }

    unordered_set<string> res = findSubString(input);
   
    int i =0;
    cout<<"Palindromic Substrings of "<<input<<" are : { ";
    for(auto str: res)
       { cout<<str;
            if(i<res.size()-1)
             cout<<", ";
        i++;
       }
    cout<<"}"<<endl;
    return 0;
}

