// binary search
#include <iostream>
#include <vector>
using namespace std;

int binarySearch_rec(vector<int> &arr, int target, int start, int end)
{

    // body (same thing)
    int mid = (start + end) / 2;
    // int mid = start + (end - start) / 2;

    // base condition
    if (start > end)
        return -1;
    if (arr[mid] == target)
        return mid;

    // recursive call
    if (arr[mid] < target)
        return binarySearch_rec(arr, target, mid + 1, end);
    else
        return binarySearch_rec(arr, target, start, mid - 1);
}

int linearSearch(vector<int> &arr, int target, int idx)
{
    if (idx == arr.size())
        return -1;
    if (arr[idx] == target)
        return idx;
    return linearSearch(arr, target, idx + 1);
}

// binary search in rotated sorted array
int binarySearch_rotatedSorted(vector<int> &arr, int target, int s, int e)
{
    if (s > e)
        return -1;

    int mid = s + (e - s) / 2;
    if (arr[mid] == target)
        return mid;

    if (arr[s] <= arr[mid])
    {
        if (target >= arr[s] && target <= arr[mid])
            return binarySearch_rotatedSorted(arr, target, s, mid - 1);
        else
            return binarySearch_rotatedSorted(arr, target, mid + 1, e);
    }

    if (target >= arr[mid] && target <= arr[e])
    {
        return binarySearch_rotatedSorted(arr, target, mid + 1, e);
    }

    return binarySearch_rotatedSorted(arr, target, s, mid - 1);
}

int main()
{
    //vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    vector<int> arr = {10, 3, 50, 27, 9, 1, 13, 150, 17, 199};
    int temp;
    cout << "Target: ";
    cin >> temp;

    // int res = binarySearch_rec(arr, temp, 0, arr.size());
    // cout << "Binary Search Index: " << ((res < 0) ? "Not found" : to_string(res)) << endl;

    // int out = linearSearch(arr, temp, 0);
    // cout << "Liner Search index: " << ((out < 0) ? "Not found" : to_string(out)) << endl;
    
    int out = binarySearch_rotatedSorted(arr, temp, 0, arr.size() - 1);
    cout << "Binary Search (Non-sorted) index: " << ((out < 0) ? "Not found" : to_string(out)) << endl;
   
    return 0;
}