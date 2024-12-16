/*
Given a binary tree, find the maximum path sum. The path sum is the sum of the values of the nodes in the path, where a path is any sequence of nodes from some starting node to any node in the tree.
Input:
A binary tree (root node given).
Output:
The maximum path sum.

*/


// over All time complexity is O(n)
/*
    Approch- creating a tree with the given array of data and then find the max path sum. the path sum is the sum of the values of the nodes in the path by travers the tree use DFS algorithm
*/

#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

// Definition of TreeNode structure to represent each node in the binary tree
class TreeNode
{
public:
    int val;          // Value of the node
    TreeNode *left, *right;  // Pointers to left and right children

    // Constructor to initialize a node with a given value
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Definition of BinaryTree class to represent the binary tree structure
class BinaryTree
{
public:
    TreeNode *root;  // Root of the tree

    // Constructor to initialize an empty tree
    BinaryTree() : root(nullptr) {}

    // Function to insert a node into the binary tree
    // Time complexity: O(n), where n is the number of nodes in the tree
    void insertNode(int value)
    {
        TreeNode *newNode = new TreeNode(value);  // Create a new node with the given value

        if (!root)
        {
            root = newNode;  // If the tree is empty, set the new node as root
            return;
        }

        queue<TreeNode *> q;  // Queue to perform level order traversal
        q.push(root);  // Start with the root node

        // Traverse the tree to find an empty spot for the new node
        while (!q.empty())
        {
            TreeNode *current = q.front();
            q.pop();

            // If left child is empty, insert the new node there
            if (!current->left)
            {
                current->left = newNode;
                return;
            }
            else
            {
                q.push(current->left);  // Otherwise, push left child to queue for further exploration
            }

            // If right child is empty, insert the new node there
            if (!current->right)
            {
                current->right = newNode;
                return;
            }
            else
            {
                q.push(current->right);  // Otherwise, push right child to queue for further exploration
            }
        }
    }

    // Function to print the binary tree in level order
    // Time complexity: O(n), where n is the number of nodes in the tree
    void printTree()
    {
        if (!root)
        {
            cout << "The tree is empty." << endl;
            return;
        }

        queue<TreeNode *> q;  // Queue to perform level order traversal
        q.push(root);  // Start with the root node

        // Traverse the tree level by level
        while (!q.empty())
        {
            int levelSize = q.size();  // Get the number of nodes at the current level
            for (int i = 0; i < levelSize; i++)
            {
                // Get the front node in the queue
                TreeNode *current = q.front();  
                q.pop();
                cout << current->val << " ";  

                // Push left and right children of the current node to the queue
                if (current->left)
                    q.push(current->left);
                if (current->right)
                    q.push(current->right);
            }
            cout << endl;  // Print a new line after each level
        }
    }

    // Function to find the maximum path sum. Both root -> leaf and node -> node
    // Time complexity: O(n), where n is the number of nodes in the tree
    tuple<int, int> maxPathSum()
    {
        int sum = 0, maxSumLeaf = -99, maxSumNode = -99;

        // Find the maximum path sum from root to a leaf
        maxPathToLeaf(root, sum, maxSumLeaf);
        // Find the maximum path sum from node to node (including non-root nodes)
        maxPathDown(root, maxSumNode);

        // Return both maximum sums as a tuple (maxSumNode, maxSumLeaf)
        tuple<int, int> result{maxSumNode, maxSumLeaf};
        return result;
    }

private:
    // Helper function to find the maximum path sum from a node to another node
    // This function updates the global maxSum with the maximum path sum seen so far
    int maxPathDown(TreeNode *node, int &maxSum)
    {
        if (!node)
            return 0;  // Base case: if the node is null, return 0

        // Recursively find the maximum path sum for left and right children
        int left = max(0, maxPathDown(node->left, maxSum));  // Ignore negative paths
        int right = max(0, maxPathDown(node->right, maxSum));

        // Update the global maxSum with the current node's value plus the max of left and right
        maxSum = max(maxSum, left + right + node->val);

        // Return the maximum path sum extending from the current node to either left or right child
        return max(left, right) + node->val;
    }

    // Helper function to find the maximum path sum from root to a leaf
    // This function updates the maxSum for the path sum from root to leaf
    int maxPathToLeaf(TreeNode *node, int sum, int &maxSum)
    {
        if (!node)
        {
            maxSum = max(maxSum, sum);  // Update the maximum sum found so far
            return 0;  // Return 0 for null nodes
        }

        sum += node->val;  // Add the current node's value to the running sum

        // Recursively find the maximum path sum for left and right children
        int left = maxPathToLeaf(node->left, sum, maxSum);
        int right = maxPathToLeaf(node->right, sum, maxSum);

        // Return the maxSum (this will be updated during the recursion)
        return maxSum;
    }
};

int main()
{
    BinaryTree tree;  // Create a new binary tree

    int arr[] = {1, 3, 2, 5, 7, 1, 8, 5};  // Array of values to insert into the tree
    int n = sizeof(arr) / sizeof(arr[0]);

    // Insert nodes into the tree
    for (int i = 0; i < n; i++)
    {
        tree.insertNode(arr[i]);
    }

    // Print the binary tree in level order
    tree.printTree();

    // Find the maximum path sum from node to node and root to leaf
    auto it = tree.maxPathSum();

    // Output the results
    cout << "Max Path from one node to another: " << get<0>(it) << endl;
    cout << "Max Path from root node to leaf: " << get<1>(it) << endl;

    return 0;
}
