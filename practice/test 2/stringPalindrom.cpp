
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool validPalindrome(const std::string& s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

void deleteCharacter(string str, int ind) {
    cout<<"------------------------------------"<<endl;
    cout<<"Valid palindrome = "<<str.substr(0, ind) + str.substr(ind+1, str.size() - ind - 1)<<endl;
    cout<<"Deleted character = '"<<str[ind]<<"'"<<endl;
    cout<<"Position of deleted character = "<<ind<<endl;
    cout<<"------------------------------------"<<endl;
}

void checkPalindromeStrings(string str) {
    bool found = false;
    int len = str.length();
    for(int i=0; i<len; i++){
        string temp = str.substr(0, i) + str.substr(i+1, str.size() - i - 1);
        bool palindrome = validPalindrome(temp);
        if(palindrome)
          {  deleteCharacter(str, i);
                found = true;
              break;    
            }
    }
    if(!found && validPalindrome(str)){
        cout<<"Given string "<<str<<" is palindrome and no further palindrome is possible"<<endl;
        found = true;
    }

    if(!found)cout<<"No Valid palindrome string could be obtained from: "<<str<<endl;
}

void trimString(string& str){
    int start = 0, end = str.length() - 1;
    while(start<end && (str[start]==' ' || str[start]=='\t' || str[start]=='\n' || str[start]=='\r')) start++;
    while(start<end && (str[end]==' ' || str[end]=='\t' || str[end]=='\n' || str[end]=='\r')) end--;
    try{
    if(str[start]== '"')start++;else throw "error";
    if(str[end]=='"')end--;else throw "error";}
    catch(...){
        cout<<"Invalid input string provided.2"<<endl;
        exit(-1);
    }
    str = str.substr(start, end - start + 1);
}

int main() {
    string str;
    cout<<"enter string: ";
    getline(cin,str);

    // if(str=="NULL" || str=="null" || str=="Null" || str=="-0"){
    //     cout<<"Invalid input string provided.1"<<endl;
    //     return 0;
    // }

    trimString(str);
    if(str.size()==0){
        cout<<"Invalid input string provided.3"<<endl;
        return 0;
    }
    //cout<<"\nstring: "<<str<<endl;

    checkPalindromeStrings(str);

    
    return 0;
}