#include <iostream>
#include <vector>
using namespace std;

bool isSorted(vector<int>& arr, int start){
    if (start < arr.size()-1 && arr[start]>arr[start+1]) return false;
    if(start == arr.size()-1) return true;
    return isSorted(arr, start+1);
}

int main(){
    vector<int> arr ={1,2,3,4,7,6,7,8,9};

    if(isSorted(arr,0))
    cout<<"true"<<endl;
    else
    cout<<"false"<<endl;


    return 0;
}