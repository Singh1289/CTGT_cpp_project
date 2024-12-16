#include<iostream>
#include<string>
using namespace std;

/*
string skipChar(const string& str, char c, int idx) {
    if(idx >= str.size())return "";

    char ch = str[idx];

    if(ch == c)
        return skipChar(str, c, idx+1);
    else
        return ch + skipChar(str, c, idx+1);
}

int main(){
    string str = "baadfad";
    char ch = 'a';

    cout<<skipChar(str,ch,0)<<endl;

    return 0;
}
*/

// string skipString(const string& str, const string& tar, int idx){
//     if(idx >= str.size()- tar.size()) return "";
    
//     char ch;
// }

string skipString(const string& str, const string& tar, int idx){
    if(idx >= str.size()- tar.size()) return "";
    
    char ch = str[idx];
    string sub = str.substr(idx,tar.size());
    
    if(sub == tar)
        return skipString(str,tar,idx+1);
    else
        return ch + skipString(str,tar,idx+1);
 
}

int main(){
    string str = "baadmangofad";
    string target = "mango";

    cout<<skipString(str,target,0)<<endl;
    return 0;
    
}