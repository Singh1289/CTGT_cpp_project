/*
Design an algorithm to serialize and deserialize a binary tree [Both in O(n)]. Serialization is the process of converting a tree into a string, and deserialization is the process of reconstructing the tree from that string. Use preorder traversal for serialization and queue-based level-order traversal for deserialization.
For example:
Input:
root = [1, 2, 3, null, null, 4, 5]
Output:
Serialized in binary: 1100000000000000000000000000000101000000000000000000000000000010000000000000000000000000000000011
Deserialize: The tree [1, 2, 3, null, null, 4, 5]
Input:
A binary tree.
Output:
A string representing the serialized binary tree in binary.
A binary tree reconstructed from the serialized string in binary.
Constraints:
The tree can have up to 10^5 nodes.

*/

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <cstring>
using namespace std;

// Defining a constant for Null value representation
#define Null_value (-99999)

// Function to trim leading and trailing whitespaces or quotes from a string
void trimString(string &str)
{
    int start = 0;
    int end = str.size() - 1;

    // Trim leading spaces, single quotes, and double quotes
    while (start < end && (isspace(str[start]) || str[start] == '"' || str[start] == '\''))
        start++;

    // Trim trailing spaces, single quotes, and double quotes
    while (start < end && (isspace(str[end]) || str[end] == '"' || str[end] == '\''))
        end--;

    // Assign the trimmed string back
    str = str.substr(start, end - start + 1);
}

// Function to convert a string representation of a number to its decimal value
int toDecimal(string strr)
{
    int decimal = 0;
    const char *str = strr.c_str();

    // Handling hexadecimal (0x or 0X) prefix
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        decimal = strtoul(str, nullptr, 16);
    // Handling octal (leading 0) but not followed by x
    else if (str[0] == '0' && (str[1] != 'x' || str[1] != 'X'))
        decimal = strtoul(str, nullptr, 8);
    // Handling positive or negative decimal numbers
    else if ((str[0] == '-' && str[1] > '0' && str[1] <= '9') || (str[0] > '0' && str[0] <= '9'))
        decimal = strtoul(str, nullptr, 10);
    // Handling single character input (both lowercase and uppercase)
    else if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z'))
    {
        if (strlen(str) > 1)
        {
            cout << "Invalid decimal";
            exit(1);
        }
        decimal = str[0];
    }
    else
    {
        cout << "Invalid decimal sp :" << str;
        exit(1);
    }

    return decimal;
}

// Function to convert a string containing array-like structure into a vector of integers
void convertIntoArray(vector<int> &array, string str, int &idx)
{
    int end = str.size() - 1;
    size_t start = str.find('[');
    size_t zeor = str.find("-0");

    // Ensure the string has proper array-like format, no invalid characters, or `-0`
    if (str[end] != ']' || start == string::npos || end == string::npos || start >= end || zeor != string::npos)
    {
        cout << "Invalid input: b " << endl;
        exit(-1);
    }

    // Extract content between brackets
    string content = str.substr(start + 1, end - start - 1);
    trimString(content);

    size_t pos = 0;
    // Process each element (separated by commas)
    while ((pos = content.find(',')) != string::npos)
    {
        string token = content.substr(0, pos);
        trimString(token);

        // Convert token to integer, if 'null' encountered, push Null_value
        if (token == "null" || token == "NULL")
            array.push_back(Null_value);
        else
            array.push_back(toDecimal(token));

        idx++;
        content.erase(0, pos + 1);
    }

    trimString(content);
    // Handle the last token
    if (content == "null" || content == "NULL")
        array.push_back(Null_value);
    else
        array.push_back(toDecimal(content));

    idx++;
}

// Function to convert an integer to its binary representation as a string
string toBinary(int num)
{
    string res = "";
    bool isNegative = false;

    // If number is negative, invert bits (two's complement representation)
    if (num < 0)
    {
        num = ~num; // Inverting all bits
        isNegative = true;
    }

    // Convert the absolute value to binary
    while (num > 0)
    {
        res = to_string(num % 2) + res;
        num /= 2;
    }

    // If the binary string length is less than 32, add leading zeros or handle two's complement
    if (res.length() < 32)
    {
        if (isNegative)
        {
            // Convert to two's complement if negative
            for (int i = 0; i < res.length(); i++)
            {
                res[i] = (res[i] == '1') ? '0' : '1';
            }
            res = string(32 - res.length(), '1') + res;
        }
        else
            res = string(32 - res.length(), '0') + res;
    }

    return res;
}

// Function to serialize an array of integers into a binary string
string serialize(vector<int> &array)
{
    string result = "";
    // Convert each integer in the array to its binary representation
    for (int i = 0; i < array.size(); i++)
    {
        result += toBinary(array[i]);
    }
    return result;
}

// Function to convert a 32-bit binary string to an integer
int binaryToInt(const string &binary)
{
    long num = strtoul(binary.c_str(), NULL, 2);
    // Handle the sign bit (for negative values)
    return (binary[0] == '1') ? num - 4294967296 : num;
}

// Function to deserialize a binary string back into a vector of integers
vector<int> deseriailize(const string &binaryString)
{
    vector<int> numbers;
    // Process each 32-bit chunk of the binary string
    for (size_t i = 0; i < binaryString.size(); i += 32)
    {
        string span = binaryString.substr(i, 32);
        numbers.push_back(binaryToInt(span));
    }
    return numbers;
}

// Main function where the program execution begins
int main()
{
    string input;
    cout << "Input: ";
    // Read the entire input string from the user
    getline(cin, input);

    // Trim leading and trailing whitespaces and quotes from the input
    trimString(input);

    // Check for the invalid '-0' case in input
    int inval = input.find("-0");
    if (input.size() < 1)
    {
        cout << "Invalid input: empty string" << endl;
        return 0;
    }
    else if (inval != string::npos)
    {
        cout << "Invalid input: input contains -0" << endl;
        return 0;
    }

    int idx = 0;
    vector<int> arr;
    // Convert the input string into an array of integers
    convertIntoArray(arr, input, idx);

    // Serialize the array of integers to a binary string
    string binary = serialize(arr);

    // Output the serialized binary string
    cout << "Output: " << endl;
    cout << "Serialized in binary: " << binary << endl;

    // Deserialize the binary string back to an array of integers
    vector<int> arr2 = deseriailize(binary);

    // Output the deserialized result
    cout << "Deserialize: The Tree [ ";
    for (int i = 0; i < arr2.size(); i++)
    {
        if (arr2[i] == Null_value)
            cout << "null";
        else
            cout << arr2[i];
        if (i < arr2.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
