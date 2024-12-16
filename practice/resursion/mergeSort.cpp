#include<iostream>
#include<vector>
using namespace std;
/*
vector<int> merge(vector<int>&left, vector<int>&right){
    vector<int> result;
    int i=0, j=0,k=0;

    while(j<right.size() && i<left.size()){
        if(left[i] <= right[j]){
            result.push_back(left[i]);
            i++;
        }
        else{
            result.push_back(right[j]);
            j++;
        }
    }
    
    while(i<left.size()){
        result.push_back(left[i]);
        i++;
    }
    while(j<right.size()){
        result.push_back(right[j]);
        j++;
    }
    
    return result;
}



vector<int> mergeSort(vector<int> &arr){
    if(arr.size() == 1) return arr;

    int mid = arr.size()/2;
    vector<int> left(arr.begin(),arr.begin()+mid);
    vector<int> right(arr.begin()+mid,arr.end());

    left = mergeSort(left);
    right = mergeSort(right);
    
    return merge(left, right);
}
*/
// mergerSort
void inPlaceMerge(vector<int> &arr, int start, int mid, int end) {
    int i = start;   
    int j = mid + 1; 

    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            i++;
        } else { 
            int value = arr[j];
            int index = j;

            while (index > i) {
                arr[index] = arr[index - 1];
                index--;
            }

            arr[i] = value;
            i++;
            mid++;
            j++;
        }
    }
}

void inPlaceMergeSortHelper(vector<int> &arr, int start, int end) {
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;

    inPlaceMergeSortHelper(arr, start, mid);
    inPlaceMergeSortHelper(arr, mid + 1, end);

    inPlaceMerge(arr, start, mid, end);
}

void inPlaceMergeSort(vector<int> &arr) {
    inPlaceMergeSortHelper(arr, 0, arr.size() - 1);
}


int main(){
    vector<int> arr = {4,3,6,9,1,4,2,7,9,5};

    cout<<"Original Array: ";
    for(int i=0; i<arr.size(); i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    
    // vector<int> arr2=mergeSort(arr);
    inPlaceMergeSort(arr);
    
    vector<int> arr2 = arr;
    
    cout<<"Sorted Array:   ";
    for(int i=0; i<arr2.size(); i++)
        cout<<arr2[i]<<" ";
    cout<<endl;

    return 0;
}