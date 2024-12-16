#include <iostream>
#include <vector>
using namespace std;

void swapNumbers(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(vector<int>& arr, int n, int start){
    if(n==0)return;

    if(n>start)
    {
        if(arr[start] > arr[start+1])
            swapNumbers(arr[start],arr[start+1]);

        bubbleSort(arr,n,start+1);
    }else
    {
        bubbleSort(arr,n-1,0);
    }
}

void selectionSort(vector<int>& arr, int row, int start, int big){
    if(row == 0) return;
    
    if(row>start){
        if(arr[start]> arr[big])
            selectionSort(arr,row,start+1,start);
            else
            selectionSort(arr,row,start+1,big);
    }
    else{
        swapNumbers(arr[row-1],arr[big]);
        selectionSort(arr,row-1,0,0);
    }

}

int main(){
    vector<int> arr = {3,6,5,8,9,1,3,4,6,8};
    int n = arr.size();

    //bubbleSort(arr,n-1,0);

    selectionSort(arr,n,0,0);

    cout<<"Sorted Array: ";
    for(int i=0; i<n; i++)
        cout<<arr[i]<<" ";

    

    return 0;
}