#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <queue>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor for Node
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    // Inserts a value into the binary tree
    void insert(int value) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            insert_helper(root, value);
        }
    }

    // Prints the tree in level order starting from a specific node
    void print_tree(Node* node) {
        if (!node) {
            std::cout << "[ NULL ]" << std::endl;
            return;
        }

        // Store the nodes in level order
        std::vector<int> result;
        std::queue<Node*> queue;
        queue.push(node);

        while (!queue.empty()) {
            Node* temp = queue.front();
            queue.pop();
            result.push_back(temp->data);

            // Add children to queue if they exist
            if (temp->left) queue.push(temp->left);
            if (temp->right) queue.push(temp->right);
        }

        // Output the results in the desired format
        std::cout << "Output: [ ";
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i != result.size() - 1) std::cout << ", ";
        }
        std::cout << " ]" << std::endl;
    }

    // Finds a node with the specified value in the binary tree
    Node* find_node(int value) {
        return find_data(root, value);
    }

private:
    Node* root;

    // Recursive helper for inserting a new node based on value
    void insert_helper(Node* node, int value) {
        if (value < node->data) {
            // Insert in the left subtree
            if (!node->left) {
                node->left = new Node(value);
            } else {
                insert_helper(node->left, value);
            }
        } else if (value > node->data) {
            // Insert in the right subtree
            if (!node->right) {
                node->right = new Node(value);
            } else {
                insert_helper(node->right, value);
            }
        } else {
            // Duplicate value case: insert in the left subtree
            if (!node->left) {
                node->left = new Node(value);
            } else {
                insert_helper(node->left, value);
            }
        }
    }

    // Recursive helper for finding a node with a specific value
    Node* find_data(Node* node, int value) {
        if (!node || node->data == value) return node;
        if (value < node->data) return find_data(node->left, value);
        return find_data(node->right, value);
    }
};

// Trims leading and trailing whitespace and any extra quotes from a string
void trim_string(std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\"'");
    size_t end = str.find_last_not_of(" \t\n\r\"'");
    str = (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Converts a string to an integer, supporting hexadecimal, octal, and decimal formats
int to_decimal(const std::string& strr) {
    const char* str = strr.c_str();
    int decimal = 0;

    // Determine the format based on the prefix and convert accordingly
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        decimal = std::strtoul(str, nullptr, 16);  // Hexadecimal
    } else if (str[0] == '0' && str[1] != 'x' && str[1] != 'X') {
        decimal = std::strtoul(str, nullptr, 8);   // Octal
    } else if ((str[0] == '-' && isdigit(str[1])) || isdigit(str[0])) {
        decimal = std::strtoul(str, nullptr, 10);  // Decimal
    } else if (isalpha(str[0]) && strr.length() == 1) {
        decimal = str[0];  // Single character
    } else {
        std::cerr << "Error: Invalid decimal value." << std::endl;
        exit(EXIT_FAILURE);
    }
    return decimal;
}

// Converts a delimited string of numbers to an array of integers
void convert_into_array(std::vector<int>& array, const std::string& str, int& idx) {
    size_t start = str.find('[');
    size_t end = str.find(']');
    if (start == std::string::npos || end == std::string::npos || start >= end) {
        std::cerr << "Error: Invalid input format." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Extract and trim content between brackets
    std::string content = str.substr(start + 1, end - start - 1);
    trim_string(content);

    // Split the content by commas
    size_t pos = 0;
    while ((pos = content.find(',')) != std::string::npos) {
        std::string token = content.substr(0, pos);
        trim_string(token);
        if (token != "NULL" && token != "null") {
            if (token == "-0") {
                std::cerr << "Error: Invalid value -0." << std::endl;
                exit(EXIT_FAILURE);
            }
            array.push_back(to_decimal(token));
            idx++;
        }
        content.erase(0, pos + 1);
    }

    // Handle the last token in the content
    trim_string(content);
    if (content != "NULL" && content != "null") {
        array.push_back(to_decimal(content));
        idx++;
    }
}

int main() {
    BinaryTree tree;
    std::string input;
    std::cout << "Input: ";
    std::getline(std::cin, input);

    trim_string(input);
    if (input.empty()) {
        std::cerr << "Error: Empty input." << std::endl;
        return EXIT_FAILURE;
    }

    // Convert input string to array of integers
    std::vector<int> arr;
    int idx = 0;
    convert_into_array(arr, input, idx);

    if (idx == 0) {
        std::cerr << "Error: No valid elements found." << std::endl;
        return EXIT_FAILURE;
    }

    // Prompt for the key and convert it to decimal
    std::string key;
    std::cout << "Key: ";
    std::cin >> key;
    trim_string(key);

    if (key.empty() || key.find("-0") != std::string::npos) {
        std::cerr << "Error: Invalid key input." << std::endl;
        return EXIT_FAILURE;
    }

    int kk = to_decimal(key);

    // Insert elements from the array into the binary tree
    for (const auto& val : arr) {
        tree.insert(val);
    }

    // Search for the node with the given key value
    Node* node = tree.find_node(kk);
    if (node) {
        tree.print_tree(node);
    } else {
        std::cout << "[ NULL ]" << std::endl;
    }

    return EXIT_SUCCESS;
}
