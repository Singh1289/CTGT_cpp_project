#include<iostream>
#include<vector>
using namespace std;

void quickSort(vector<int>& arr, int low, int high){
    if(low >= high) return;

    int start = low;
    int end = high;
    int pivot = arr[low + (high - low) / 2];
    while(start<= end){
        while(arr[start] < pivot)
            start++;
        while (arr[end] > pivot)
            end--;

        if(start<= end){
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }
   
    if(low<end)quickSort(arr, low, end);
    if(start<high)quickSort(arr, start, high);
}

int main(){
    vector<int> arr = {4,3,6,9,1};

    cout<<"Original Array: ";
    for(int i=0; i<arr.size(); i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    
    // vector<int> arr2=mergeSort(arr);
    quickSort(arr, 0, arr.size()-1);
    
    cout<<"Sorted Array:   ";
    for(int i=0; i<arr.size(); i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    return 0;
}