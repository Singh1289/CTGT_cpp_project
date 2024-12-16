#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <string.h>

using namespace std;

void findMinAndMaxPairs(vector<long> &arr, set<pair<long, long>> &minPairs, set<pair<long, long>> &maxPairs)
{
    long long minDiff = INT_MAX, maxDiff = INT_MIN;
    for (int i = 0; i < arr.size() - 1; i++)
    {
        for (int j = i + 1; j < arr.size(); j++)
        {
            long long diff = abs(arr[i] - arr[j]);
            if (diff < minDiff)
            {
                minDiff = diff;
                minPairs.clear();
                minPairs.insert(make_pair(min(arr[i], arr[j]), max(arr[i], arr[j])));
            }
            else if (diff == minDiff)
            {
                minPairs.insert(make_pair(min(arr[i], arr[j]), max(arr[i], arr[j])));
            }
            if (diff > maxDiff)
            {
                maxDiff = diff;
                maxPairs.clear();
                maxPairs.insert(make_pair(min(arr[i], arr[j]), max(arr[i], arr[j])));
            }
            else if (diff == maxDiff)
            {
                maxPairs.insert(make_pair(min(arr[i], arr[j]), max(arr[i], arr[j])));
            }
        }
    }
}

void printPairs(set<pair<long,long>> &pairs)
{
    int s = pairs.size();
    if (s == 0)
    {
        cout << "No pairs found." << endl;
        return;
    }
    cout << "[";
    for (auto &p : pairs)
    {
        cout << "(" << p.first << ", " << p.second << ")";
        if (s > 1)
            cout << ", ";
        s--;
    }
    cout << "]" << endl;
}

void trimString(string &str)
{
    int start = 0, end = str.length() - 1;
    while (start < end && (str[start] ==' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r'))
        start++;
    while (start < end && (str[end] ==' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r'))
        end--;
    str = str.substr(start, end - start + 1);
}

long toDecimal(string strr)
{
    long decimal = 0;
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
            cout << "invalid string";
            exit(1);
        }
        decimal = str[0];
    }
    else
    {
        cout << "invalid string :" << str;
        exit(1);
    }
 
    return decimal;
}
 
void convertIntoArray(vector<long> &array, const string &str, int &idx)
{
    long temp = 0;
 
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



int main()
{

    string input;
    cout << "Input: arr = ";
    getline(cin, input);

    trimString(input);
    if(input.size()== 0 || input == "NULL" || input =="null" || input == "Null"|| input == "-0"){
        cout << "Invalid input" << endl;
        return 0;
    }
    vector<long> arr ;
    int idx = 0;
    convertIntoArray(arr, input, idx);

    if(idx == 0){
        cout << "Invalid input: empty string" << endl;
        return 0;
    }
    
    for(int i = 0; i < arr.size();i++)
        cout<< arr[i] <<" ";

    cout<<endl;

    //vector<int> arr = {4, 2, 1, 3};

    set<pair<long, long>> minPairs, maxPairs;
    findMinAndMaxPairs(arr, minPairs, maxPairs);
    cout<<"Output: "<<endl;
    cout << "Pairs having minimum absolute distance = ";
    printPairs(minPairs);
    cout << "Pairs having maximum absolute distance = ";
    printPairs(maxPairs);


    return 0;
}
