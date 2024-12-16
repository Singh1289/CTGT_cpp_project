/*
Problem: Given a binary tree, calculate the average value of the nodes
at each level of the tree. The result should be returned as an array
of floating-point numbers where each element corresponds to the
average of the nodes at that level, rounded to two decimal places.
If it is not possible to determine average, print appropriate message.
Input: The input will be a binary tree as depicted in the examples.
Output: An array of floating-point numbers representing the average value of
nodes at each level of the binary tree.
Instructions: Please adhere to the input and output formats as depicted in the examples.
Examples:
Input: [1, 2, 3, 4, 5, 6]
Output: [1.00, 2.50, 5.00]
Input: [3, 9, 20, 15, 7]
Output: [3.00, 14.50, 11.00]
['a', 'b', 'c', null, -987, 12, 345]
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cctype>
#include <cstdlib>
using namespace std;

vector<double> vec;

int toDecimal(string strr)
{
    int decimal = 0;
    const char *str = strr.c_str();
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        decimal = strtoul(str, nullptr, 16);
    }
    else if (str[0] == '0' && (str[1] != 'x' || str[1] != 'X'))
    {
        decimal = strtol(str, nullptr, 8);
    }
    else if ((str[0] == '-' && str[1] >= '0' && str[1] <= '9') || (str[0] >= '0' && str[0] <= '9'))
    {
        decimal = strtol(str, nullptr, 10);
    }
    else if ((str[0] >= 32 && str[0] <= 126))
    {
        if (strr.length() > 1)
        {
            cout << "Invalid input: cannot convert letter to number.";
            exit(1);
        }
        decimal = str[0];
    }
    else
    {
        cout << "Invalid input: 12 " << str << endl;
        exit(1);
    }

    return decimal;
}

class Node
{
public:
    int data;
    bool flag = true;
    Node *left, *right;

    Node(int data) : data(data), left(nullptr), right(nullptr) {}
    Node(int data, bool flag) : data(data), flag(flag) {}
};

class TreeNode
{
public:
    Node *root;

    TreeNode() : root(nullptr) {}

    void addNode(string data)
    {
        root = addNodeHelper(root, data);
    }

    void printTree()
    {
        if (!root || !root->flag)
        {
            cout << "Tree is empty.";
            return;
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int levelSize = q.size();
            while (levelSize > 0)
            {
                Node *current = q.front();
                q.pop();
                cout << current->data << " ";

                if (current->left && current->left->flag)
                    q.push(current->left);
                if (current->right && current->right->flag)
                    q.push(current->right);

                levelSize--;
            }

            cout << endl;
        }
    }

    void averageAtEachLevel()
    {
        if (!root || !root->flag)
        {
            cout << "Tree is empty.";
            exit(-1);
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int levelSize = q.size();
            double levelSum = 0;

            for (int i = 0; i < levelSize; ++i)
            {
                Node *current = q.front();
                q.pop();
                levelSum += current->data;

                if (current->left && current->left->flag)
                    q.push(current->left);
                if (current->right && current->right->flag)
                    q.push(current->right);
            }

            double levelAverage = levelSum / levelSize;
            vec.push_back(levelAverage);
        }
    }

private:
    Node *addNodeHelper(Node *node, string data)
    {
        if (node == nullptr)
        {
            if (data == "null" || data == "NULL" || data == "Null")
                return new Node(-9999, false);

            return new Node(toDecimal(data));
        }

        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();

            if (current->flag)
            {
                if (!current->left)
                {
                    if (data == "null" || data == "NULL" || data == "Null")
                        current->left = new Node(-9999, false);
                    else
                        current->left = new Node(toDecimal(data));
                    return node;
                }
                else
                {
                    q.push(current->left);
                }

                if (!current->right)
                {
                    if (data == "null" || data == "NULL" || data == "Null")
                        current->right = new Node(-9999, false);
                    else
                        current->right = new Node(toDecimal(data));
                    return node;
                }
                else
                {
                    q.push(current->right);
                }
            }
        }
        return node;
    }
};

void trimString(string &str)
{
    int start = 0;
    int end = str.size() - 1;
    while (start < end && (isspace(str[start]) || str[start] == '"' || str[start] == '\''))
        start++;
    while (start < end && (isspace(str[end]) || str[end] == '"' || str[end] == '\''))
        end--;
    str = str.substr(start, end - start + 1);
}

void convertIntoArray(vector<string> &array, string str)
{
    int end = str.size() - 1;
    size_t start = str.find('[');
    //size_t end = str.find(']');

    if (str[end] != ']' ||start == string::npos || end == string::npos || start >= end)
    {
        cout << "Invalid input: mismatched brackets" << endl;
        exit(-1);
    }

    string content = str.substr(start + 1, end - start - 1);
    trimString(content);
    size_t pos = 0;
    while ((pos = content.find(',')) != string::npos)
    {
        string token = content.substr(0, pos);
        trimString(token);
        array.push_back(token);
        content.erase(0, pos + 1);
    }

    trimString(content);
    array.push_back(content);
}

int main()
{
    TreeNode tree;
    string input;
    cout << "Input: ";
    getline(cin, input);

    trimString(input);
    int inval = input.find("-0");
    if (input.size() < 1)
    {
        cout << "Invalid input: empty string" << endl;
        return 0;
    }else if(inval != string::npos){
        cout << "Invalid input: input contains -0" << endl;
        return 0;
    }

    vector<string> arr;
    convertIntoArray(arr, input);

    for(int i = 0; i < arr.size(); i++)
    {
        cout<<arr[i]<<" ";
    }

    cout << endl;

    for (const string &val : arr)
    {
        tree.addNode(val);
    }

    cout << "Level order traversal: \n";
    tree.printTree();
    cout << endl;

    tree.averageAtEachLevel();
    cout << "output: [ ";

    for (int i = 0; i < vec.size(); i++)
    {
        printf("%.2f", vec[i]);
        if (i != vec.size() - 1)
            cout << ", ";
    }
    cout << " ]" << endl;

    return 0;
}
