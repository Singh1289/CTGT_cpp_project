#include <iostream>
#include <vector>
using namespace std;


#define Array vector<vector<int>>  

int main(){
    vector<int> arr = {1,2,3};

    Array res;
    res.push_back( vector<int>());

    for(int i=0; i<arr.size(); i++)
    {
        int n = res.size();
        for(int j =0; j<n; j++){
            vector<int> internal(res[j]);
            internal.push_back(arr[i]);
            res.push_back(internal);        
        }
    }

    // print result
    for(int i=0; i<res.size(); i++){
        cout<<"[";
        for(int j=0; j<res[i].size(); j++){
            cout<<res[i][j]<<" ";
        }
        cout<<"]"<<endl;
    }


    return 0;
}