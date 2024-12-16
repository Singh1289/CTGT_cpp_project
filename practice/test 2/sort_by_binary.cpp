// Abhishek Pratap Singh - Time complexity: O(nlogn+ klogn) and space complexity: O(n).
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

void trimString(string &str)
{
    int start = 0;
    int end = str.size() - 1;
    while (start <= end && (isspace(str[start]) || str[start] == '"' || str[start] == '\''))
        start++;
    while (start <= end && (isspace(str[end]) || str[end] == '"' || str[end] == '\''))
        end--;
    if (start > end)
    {
        str = "";
        return;
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

void convertIntoArray(vector<int> &array, const string &str, int &idx)
{
    int temp = 0;

    size_t start = str.find('[');
    size_t end = str.find(']');
    size_t zero = str.find("-0");
    if (start == string::npos || end == string::npos || start >= end || zero != string::npos)
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
            array.push_back(temp);
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
        array.push_back(temp);
        idx++;
    }
    else
    {
        cout << "Invalid input ";
        exit(-1);
    }
}

int countOnes(int num)
{
    int count = 0;
    string res = "";
    bool isNegative = false;
    if (num < 0)
    {
        num = ~num;
        isNegative = true;
    }

    while (num > 0)
    {
        if (num % 2 == 1)
            count++;
        res = to_string(num % 2) + res;
        num /= 2;
    }
    if (res.length() < 32)
    {
        if (isNegative)
        {
            for (int i = 0; i < res.length(); i++)
            {
                if (res[i] == '1')
                    res[i] = '0';
                else
                    res[i] = '1';
            }

            res = string(32 - res.length(), '1') + res;
            count = 0;
            for (int i = 0; i < res.length(); i++)
            {
                if (res[i] == '1')
                    count++;
            }
            return count;
        }
    }

    return count;
}

void creatingfreqArr(vector<int> &arr, vector<pair<int, int>> &arr2, int idx)
{
    for (int i = 0; i < idx; i++)
    {
        int count = countOnes(arr[i]);
        arr2.push_back({count, arr[i]});
    }
}


void merge(vector<pair<int, int>> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<pair<int, int>> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].first <= R[j].first)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<pair<int, int>> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main()
{
    string input;
    cout << "Input: list = ";
    getline(cin, input);
    trimString(input);
    if (input.size() < 1)
    {
        cout << "Invalid input: empty string" << endl;
        return 0;
    }
    vector<int> arr;
    int idx = 0;
    convertIntoArray(arr, input, idx);
    if (idx == 0)
    {
        cout << "Invalid input: input is not a valid array" << endl;
        return 0;
    }
    

    vector<pair<int, int>> arr2;
    creatingfreqArr(arr, arr2, idx);

    mergeSort(arr2, 0, idx - 1);
    cout<<"Output: Sorted list = [";
    for (int i = 0; i < arr2.size(); i++)
    {
        cout <<arr2[i].second;
        // cout <<arr2[i].second<<" "<<arr2[i].first;
        if(i < arr2.size() - 1) cout<<", ";
    }
    cout<<"]\n";
    return 0;
}
/*
1000000000  = 00111011100110101100101000000000 13
-1000000000 = 11000100011001010011011000000000 11
5000000000  = 00011101110011010110010100000000 13
-5000000000 = 11100010001100101001101100000000 12
*/
