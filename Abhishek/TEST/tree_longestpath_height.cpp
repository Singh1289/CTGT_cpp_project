/*
Problem: Given a binary tree, find its height. The height or depth of a binary tree is
defined as the total number of nodes on the longest path from the root node to
any leaf node. A leaf node is a node that has no children.
Input:
An array representing the binary tree where each array element represents a node
in the binary tree. Nodes of the tree may contain alphanumeric data values. If an
element is null, it indicates that the corresponding node does not exist. A valid
value other than null represents a node in the tree. ($$0 \le length(array) \le 10^9$$)
Output:
1. Print an integer representing the height of the binary tree, 2. output at least
one longest path identified.
Instructions: Please adhere to the input and output formats as depicted in the examples. If
your approach is optimal, you will get full marks, otherwise half. Further, separate
marks will be awarded for each output, i.e. seperate marks for height and longest path.
Examples:
Input: [1, 2, 3, 4, 5, null, 7]
Output: Height of the binary tree = 3
Longest Path = (1, 3, 7)
Input: [A, B, C]
Output: Height of the binary tree = 2
Longest Path = (A, B)
*/


#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;


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
    size_t zeor = str.find("-0");

    if (str[end] != ']' ||start == string::npos || end == string::npos || start >= end || zeor != string::npos)
    {
        cout << "Invalid input: b " << endl;
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



class Node
{
public:
    string data;
    bool flag = true;
    Node *left, *right;

    Node(string data) : data(data), left(nullptr), right(nullptr) {}
    Node(string data, bool flag) : data(data), flag(flag) {}
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


 

    int height(Node *root)
    {
         if (!root || !root->flag)
        {
            cout << "Tree is empty.";
            exit(-1);
        }
        int count = 0;
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int levelSize = q.size();
            
            count++;
            for (int i = 0; i < levelSize; ++i)
            {
                Node *current = q.front();
                q.pop();

                if (current->left && current->left->flag)
                    q.push(current->left);
                if (current->right && current->right->flag)
                    q.push(current->right);
            }
        }
        return count;
    }

   
void findLongestPath() {
        if (!root || !root->flag) {
            cout << "Tree is empty." << endl;
            return;
        }

        string longestPath = "";
        string currentPath = "";
        maxPathToLeaf(root, currentPath, longestPath);

        cout << "\tLongest Path: { " << longestPath << "}" << endl;
    }
    

private:

    void maxPathToLeaf(Node *node, string currentPath, string &longestPath) {
        if (!node || !node->flag)
            return;


        
        currentPath += node->data + " ";

        
        if (!node->left && !node->right) {
            if (currentPath.length() > longestPath.length()) {
                longestPath = currentPath;
            }
        } else {
            
            maxPathToLeaf(node->left, currentPath, longestPath);
            maxPathToLeaf(node->right, currentPath, longestPath);
        }
    }


    Node *addNodeHelper(Node *node, string data)
    {
        if (node == nullptr)
        {
            if (data == "null" || data == "NULL" || data == "Null")
                return new Node("-1", false);

            return new Node(data);
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
                        current->left = new Node("-1", false);
                    else
                        current->left = new Node(data);
                    return node;
                }
                else
                {
                    q.push(current->left);
                }

                if (!current->right)
                {
                    if (data == "null" || data == "NULL" || data == "Null")
                        current->right = new Node("-1", false);
                    else
                        current->right = new Node(data);
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
int main(){
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

    // for(int i = 0; i < arr.size(); i++)
    // {
    //     cout<<arr[i]<<" ";
    // }

    cout << endl;

    for (const string &val : arr)
    {
        tree.addNode(val);
    }

    // cout << "Level order traversal: \n";
    // tree.printTree();
    // cout << endl;

    int height = tree.height(tree.root);
    cout<<"Output:";
    cout<<" Height of binary tree: "<<height<<endl;
    tree.findLongestPath();
    return 0;

}