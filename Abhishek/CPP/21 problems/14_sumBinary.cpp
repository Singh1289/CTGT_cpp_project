/*
Given a binary search tree (BST), convert it to a greater sum tree. The value of each node in the tree should be replaced with the sum of all nodes greater than or equal to it.
For example:
Input:
         4
        / \
       1   6
      / \  / \
     0  2 5   7
Output:
          22
        /   \
       25    13
     /   \   /  \
    25   24 18   7

Input:
A binary search tree.
Output:
The transformed binary search tree.
Constraints:
The tree can have up to 10^5 nodes.
*/

#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include<cctype>
#include<cstdlib>
using namespace std;

// Global variables for storing node values and sum map
vector<int> vec;
map<int, int> sumMap;

// Function to convert a string to its decimal equivalent based on its format (hex, octal, decimal, or ASCII)
int toDecimal(string strr)
{
    int decimal = 0;
    const char *str = strr.c_str();

    // If the string represents a hexadecimal number
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        decimal = strtoul(str, nullptr, 16);  // Convert from hexadecimal
    }
    // If the string represents an octal number
    else if (str[0] == '0' && (str[1] != 'x' || str[1] != 'X'))
    {
        decimal = strtol(str, nullptr, 8);  // Convert from octal
    }
    // If the string represents a decimal number
    else if ((str[0] == '-' && str[1] >= '0' && str[1] <= '9') || (str[0] >= '0' && str[0] <= '9'))
    {
        decimal = strtol(str, nullptr, 10);  // Convert from decimal
    }
    // If the string represents an ASCII character (single character string)
    else if ((str[0] >= 32 && str[0] <= 126))
    {
        if (strr.length() > 1)
        {
            cout << "Invalid input: cannot convert letter to number.";
            exit(1);
        }
        decimal = str[0];  // Convert character to its ASCII value
    }
    else
    {
        cout << "Invalid input: 12 " << str << endl;
        exit(1);  // If input is invalid, exit the program
    }

    return decimal;
}

// Definition of a Node in the binary tree with a flag for its existence
class Node
{
public:
    int data;  // Data stored in the node
    bool flag = true;  // Flag to indicate if the node is valid
    Node *left, *right;  // Pointers to left and right children

    // Constructor to initialize node with data
    Node(int data) : data(data), left(nullptr), right(nullptr) {}
    // Constructor to initialize node with data and flag
    Node(int data, bool flag) : data(data), flag(flag) {}
};

// Definition of a TreeNode class to manage the root and add nodes
class TreeNode
{
public:
    Node *root;  // Root of the tree

    TreeNode() : root(nullptr) {}  // Constructor to initialize the root

    // Function to add a node with given data to the tree
    void addNode(string data)
    {
        root = addNodeHelper(root, data);  // Call helper function to add node
    }

    // Function to print the tree in level order traversal
    void printTree(bool flag)
    {
        if (!root || !root->flag)  // Check if the tree is empty
        {
            cout << "Tree is empty.";
            return;
        }

        queue<Node *> q;  // Queue for level order traversal
        q.push(root);

        // Level order traversal
        while (!q.empty())
        {
            int levelSize = q.size();
            while (levelSize > 0)
            {
                Node *current = q.front();
                q.pop();
                // Print the data of the current node
                if(flag)        
                    cout << sumMap[current->data] << " ";  // If flag is true, print sum
                else
                    cout << current->data << " ";  // Otherwise, print node's data

                // Push left and right children to the queue if they exist and are valid
                if (current->left && current->left->flag)
                    q.push(current->left);
                if (current->right && current->right->flag)
                    q.push(current->right);

                levelSize--;
            }

            cout << endl;
        }
    }

private:
    // Helper function to add a node recursively
    Node *addNodeHelper(Node *node, string data)
    {   
        int temp;
        if (node == nullptr)  // If the node is empty
        {
            // If the data is "null", create an invalid node
            if (data == "null" || data == "NULL" || data == "Null")
                return new Node(-9999, false);  // Representing null as -9999

            temp = toDecimal(data);  // Convert data to decimal
            vec.push_back(temp);  // Add the data to the vector
            return new Node(temp);  // Create a new node with the data
        }

        queue<Node *> q;  // Queue for level order traversal
        q.push(node);

        // Traverse the tree to find the right place to add the new node
        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();

            if (current->flag)  // If the current node is valid
            {
                // Check if the left child is empty
                if (!current->left)
                {
                    if (data == "null" || data == "NULL" || data == "Null")
                        current->left = new Node(-9999, false);  // Create an invalid left node
                    else {
                        temp = toDecimal(data);  // Convert the data to decimal
                        vec.push_back(temp);  // Add it to the vector
                        current->left = new Node(temp);  // Create a new left child
                    }
                    return node;
                }
                else
                {
                    q.push(current->left);  // If left child exists, add it to the queue
                }

                // Check if the right child is empty
                if (!current->right)
                {
                    if (data == "null" || data == "NULL" || data == "Null")
                        current->right = new Node(-9999, false);  // Create an invalid right node
                    else {
                        temp = toDecimal(data);  // Convert the data to decimal
                        vec.push_back(temp);  // Add it to the vector
                        current->right = new Node(temp);  // Create a new right child
                    }
                    return node;
                }
                else
                {
                    q.push(current->right);  // If right child exists, add it to the queue
                }
            }
        }
        return node;
    }
};

// Function to trim whitespace and quotes from a string
void trimString(string &str)
{
    int start = 0;
    int end = str.size() - 1;
    while (start < end && (isspace(str[start]) || str[start] == '"' || str[start] == '\''))
        start++;  // Trim from the left
    while (start < end && (isspace(str[end]) || str[end] == '"' || str[end] == '\''))
        end--;  // Trim from the right
    str = str.substr(start, end - start + 1);  // Get the trimmed string
}

// Function to convert a string representation of an array into a vector of strings
void convertIntoArray(vector<string> &array, string str)
{
    int end = str.size() - 1;
    size_t start = str.find('[');  // Find the start of the array

    if (str[end] != ']' || start == string::npos || end == string::npos || start >= end)
    {
        cout << "Invalid input: mismatched brackets" << endl;
        exit(-1);  // If brackets are mismatched, exit
    }

    // Extract the content inside the brackets
    string content = str.substr(start + 1, end - start - 1);
    trimString(content);  // Trim the content

    size_t pos = 0;
    // Split the content by commas to get individual elements
    while ((pos = content.find(',')) != string::npos)
    {
        string token = content.substr(0, pos);
        trimString(token);  // Trim each token
        array.push_back(token);  // Add token to the array
        content.erase(0, pos + 1);  // Remove the processed token
    }

    trimString(content);  // Trim the last element
    array.push_back(content);  // Add the last element to the array
}

int main()
{
    TreeNode tree;  // Create a tree object
    string input;
    cout << "Input: ";
    getline(cin, input);  // Read input string from user

    trimString(input);  // Trim any leading or trailing whitespace

    int inval = input.find("-0");  // Check for invalid "-0" in input
    if (input.size() < 1)  // Check if the input is empty
    {
        cout << "Invalid input: empty string" << endl;
        return 0;  // Exit if input is empty
    }
    else if (inval != string::npos)
    {
        cout << "Invalid input: input contains -0" << endl;
        return 0;  // Exit if input contains "-0"
    }

    vector<string> arr;  // Vector to store the array of string elements
    convertIntoArray(arr, input);  // Convert input string to array of strings

    // Print the array elements
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    // Add nodes to the tree based on input array
    for (const string &val : arr)
    {
        tree.addNode(val);
    }

    cout << "Level order traversal: \n";
    tree.printTree(false);  // Print the tree with normal values
    cout << endl;

    // Sort the values in ascending order
    sort(vec.begin(), vec.end());

    // Compute the cumulative sum of the sorted values and store in sumMap
    int sum = 0;
    for (int i = vec.size() - 1; i >= 0; i--)
    {
        sum = sum + vec[i];
        // Store the sum in the map
        sumMap[vec[i]] = sum;  
    }

    // Print the cumulative sum of each value
    for (auto &vec : sumMap)
    {
        cout << "Sum of values at level " << vec.first << ": " << vec.second << endl;
    }

    // Print the tree with cumulative sum values
    tree.printTree(true);  

    return 0; 
}

