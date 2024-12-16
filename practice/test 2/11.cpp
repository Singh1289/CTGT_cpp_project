/*
Note:
Please close all the Browser and IDE tabs and other open applications
(except VS code, MS Teams or any other IDE) before proceeding with
this test. You are not allowed to browse internet, use any other
application, gadget/device besides the laptop you are using during the
test. Maintain professional decorum and complete silence during the test
and don't disturb others in any way. Your cooperation is deeply appreciated.
Problem:
Given a k-sorted array of n elements, each element is at most k positions
away from its correct position in the sorted order, your task is to sort
the array efficiently both in terms of time and space. An array is k-sorted
if each element is at most k positions away from its correct sorted position.
Input:
1. An array of n integers, where 0 ≤ n ≤ 10^9
2. A non-negative integer k where 0 ≤ k ≤ n
Output: Print sorted array of integers. If the array isn't k-sorted, print the
message: "Array isn't k-sorted". If input isn't valid, print "Invalid input".
Instructions: Please adhere to the input and output formats as depicted in the examples. If
your approach takes less than O(n*log(n)) time, you will get marks, otherwise not.
Write before your code, in comments, your name, total time and space complexity of
your approach (e.g.,//Name Surname Time complexity: O(N), Space Complexity: O(N))
Examples:
Input: Enter a k-sorted array: [1, 4, 5, 2, 3, 7, 8, 6, 10, 9]
Enter value of k: 2
Output: Sorted array: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Input: Enter a k-sorted array: [30, 1, 2, -1]
Enter value of k: 1
Output: Array isn't k-sorted
*/


// Abhishek Pratap Singh Time Complexity: O(nlog(K)) and Space Complexity: O(N)

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <string.h>
using namespace std;

void trimString(string &str, bool flag = false)
{
    int start = 0, end = str.size() - 1;
    while (start <= end && (str[start] == ' ' || str[start] == '\t'))
        start++;
    while (start <= end && (str[end] == ' ' || str[end] == '\t'))
        end--;
    if (start > end)
    {
        str = "";
        return;
    }
    if (flag)
    {
        size_t start = str.find("-0");
        size_t neg = str.find('-');
        size_t end = str.find("null");
        if (start != string::npos || end != string::npos || neg != string::npos)
        {
            cout << "Invalid input2: " << endl;
            exit(-1);
        }
    }
    str = str.substr(start, end - start + 1);
}

int toDecimal(string strr)
{
    int decimal = 0;
    const char *str = strr.c_str();
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        decimal = strtoul(str, nullptr, 16);
    else if (str[0] == '0' && (str[1] != 'x' || str[1] != 'X'))
        decimal = strtoul(str, nullptr, 8);
    else if ((str[0] == '-' && str[1] > '0' && str[1] <= '9') || (str[0] > '0' && str[0] <= '9'))
        decimal = strtoul(str, nullptr, 10);
    else if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z'))
    {
        if (strlen(str) > 1)
        {
            cout << "invalid decimal";
            exit(1);
        }
        decimal = str[0];
    }
    else
    {
        cout << "invalid decimal sp :" << str;
        exit(1);
    }

    return decimal;
}

void convertIntoArray(vector<pair<int, int>> &array, const string &str, int &idx)
{
    int temp = 0;

    size_t start = str.find('[');
    size_t end = str.find(']');
    if (start == string::npos || end == string::npos || start >= end)
    {
        cout << "Invalid input2: " << endl;
        exit(-1);
    }

    string content = str.substr(start + 1, end - start - 1);
    trimString(content);
    size_t pos = 0;
    while ((pos = content.find(',')) != string::npos)
    {
        string token = content.substr(0, pos);
        trimString(token);
        if (token != "NULL" && token != "null" && token != "Null")
        {
            if (token == "-0")
            {
                cout << "Invalid input ";
                exit(-1);
            }
            temp = toDecimal(token);
            array.push_back({temp, idx});

            idx++;
        }
        else
        {
            cout << "Invalid input ";
            exit(-1);
        }

        content.erase(0, pos + 1);
    }

    trimString(content);
    if (content != "NULL" && content != "null" && content != "Null")
    {
        temp = toDecimal(content);
        array.push_back({temp, idx});

        idx++;
    }
    else
    {
        cout << "Invalid input ";
        exit(-1);
    }
}

void mergerSort(vector<pair<int, int>> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return;

    int mid = n / 2;
    vector<pair<int, int>> left(arr.begin(), arr.begin() + mid);
    vector<pair<int, int>> right(arr.begin() + mid, arr.end());

    mergerSort(left);
    mergerSort(right);

    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i].first <= right[j].first)
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left.size())
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right.size())
    {
        arr[k] = right[j];
        j++;
        k++;
    }

    return;
}

vector<pair<int,int>> K_sort_Array(vector<pair<int,int>> arr, int key){
    // max heap size key+1
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
    //priority_queue<pair<int, int>> pq;
    vector<pair<int,int>> res;
    for (int i = 0; i < arr.size(); i++)
    {
        pq.push(arr[i]);
        if (pq.size() > key + 1)
            {   res.push_back(pq.top()); 
                pq.pop();}
    }
    while(!pq.empty()){
        res.push_back(pq.top());
        pq.pop();
    }
    return res;

}

bool isSortingCorect(vector<pair<int, int>> &arr, int key)
{
    for (int i = 0; i < arr.size(); i++)
    {
        int min = arr[i].second - key;
        int max = arr[i].second + key;
        if (i>= min && i<=max){}
        else{
            return false;
        }
    }
    return true;
}

int main()
{
    string input, k;
    cout << "Input: Enter a Kth sorted array: ";
    getline(cin, input);
    vector<pair<int, int>> arr;
    int idx = 0, key;

    trimString(input);
    if (input.size() == 0)
    {
        cout << "Invalid input" << endl;
        return 0;
    }

    cout << "Enter the value of K: ";
    cin >> k;
    trimString(k, true);
    key = toDecimal(k);

    convertIntoArray(arr, input, idx);
    if (idx == 0)
    {
        cout << "Invalid input: empty array" << endl;
        return 0;
    }

    // print array

    // sort array
    //mergerSort(arr);

    vector<pair<int,int>> arr2= K_sort_Array(arr,key);
        cout << "Sorted Array: [";
        for (int i = 0; i < arr2.size(); i++)
        {
            cout <<arr2[i].first;
            if (i < arr2.size() - 1) cout << ", ";
        }
        cout <<"]"<< endl;

    cout<<"Ouput: ";
    if (isSortingCorect(arr2, key))
    {
        cout << "Sorted Array: [";
        for (int i = 0; i < arr2.size(); i++)
        {
            cout <<arr2[i].first;
            if (i < arr2.size() - 1) cout << ", ";
        }
        cout <<"]"<< endl;
    }else{
        cout<<"Array isn't sorted"<<endl;
    }

    return 0;
}
// 
//[1, 4, 5, 2, 6, 7, 8, 3, 10, 9]