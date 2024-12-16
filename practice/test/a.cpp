#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <string.h>
using namespace std;

long long TotalSum = 0;

void trimString(string &str)
{
    int start = 0;
    int end = str.size() - 1;
    while (start < end && (str[start] == ' ' || str[start] == '\t'))
        start++;
    while (start < end && (str[end] == ' ' || str[end] == '\t'))
        end--;

    str = str.substr(start, end - start + 1);
    return;
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
            TotalSum += temp;
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
        TotalSum += temp;
        idx++;
    }
    else
    {
        cout << "Invalid input ";
        exit(-1);
    }
}

void printResult(int idx, long long &sum)
{
    cout << "Output:  Pivot Index: " << idx << endl;
    cout << "         Left array sum: " << sum << endl;
    cout << "         Right array sum: " << sum << endl;
}

void checkPivotIndex(vector<int> &values, int idx)
{
    long long leftSum = 0;
    long long totalSum = TotalSum;

    for (int i = 0; i < idx; i++)
    {

        if (leftSum == totalSum - leftSum - values[i])
        {

            printResult(i, leftSum);
            return;
        }

        leftSum += values[i];
    }
    cout << "Output: There is no index satisfied the pivot condition." << endl;
}

int main()
{
    string str;
    cout << "Input: ";
    getline(std::cin, str);

    trimString(str);
    if (str.size() == 0)
    {
        cout << "Invalid input:2 empty string" << endl;
        return 0;
    }
    vector<int> values;
    int idx = 0;
    convertIntoArray(values, str, idx);
    if (idx == 0)
    {
        cout << "Invalid input 3" << endl;
        return 0;
    }

    // for(auto i:values)
    // {
    //     cout<<i<<" ";
    // }
    // cout<<endl<<"Total Sum: "<<TotalSum<<endl;

    checkPivotIndex(values, idx);

    return 0;
}
// [ 0x80000000,0x80000000,0x80000000, 0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000]