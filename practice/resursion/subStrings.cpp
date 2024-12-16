
// C++ program to find all substrings of a given string

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void subString_rec(string s, vector<string>& substrings, string res,int idx) {
    if(idx == s.size()){
        substrings.push_back(res);
        return;
    }

    subString_rec(s, substrings, res, idx+1);
    subString_rec(s, substrings, res + s[idx], idx+1);

}

vector<string> findSubString(string s) {
    vector<string> substrings;
    string res ="";
    subString_rec(s, substrings,res,0);
    return substrings;
}

int main() {
    string s = "google";

    vector<string> res = findSubString(s);

    for(auto str: res)
        cout<<str<<" ";

    return 0;
}