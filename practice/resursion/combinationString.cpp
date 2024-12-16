#include<iostream>
#include <string>
#include <set>
using namespace std;

int permutations(string out, string in, set<string>&res){
    if(in.empty())
    {
        res.insert("\""+out+"\"");
        return 1;
    }
    int count = 0;
    char ch = in[0];
    for(int i=0; i<=out.size(); i++){
        string first = out.substr(0, i);
        string rest = out.substr(i);
        count = count + permutations(first+ch+rest, in.substr(1), res);
    }
    return count;
}

int main()
{
    string str = "abhis";
    set<string> res;
    cout<<"Total permutaion : "<<permutations("",str,res)<<endl;
    int i = 1;
    cout<<"Output: [";
    for(auto& st:res){
        cout<<st;
        if(i < res.size()) cout<<", ";
        i++;
    }
    cout<<"]"<<endl;

    return 0;
}