/*
Implement a Trie (Prefix Tree) to support auto-completion of words. The system should allow:
Insertion of words.
Searching for a word.
Searching for all words that start with a given prefix.
Input:
A list of words.
A prefix to search for.
Output:
All words in the Trie that start with the given prefix.
Constraints:
The number of words can be up to 10^5.
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// TrieNode class represents each node in the trie
class TrieNode
{
public:
    char data; // Character stored in the current node
    bool isEndOfWord; // Flag to check if it's the end of a word
    int count; // To track how many words pass through this node
    // Array to store children nodes (for each letter of the alphabet)
    TrieNode *children[26]; 

    // Constructor initializes the node with a character and default values
    TrieNode(char data, bool is = false) : data(data), isEndOfWord(is)
    {   
        // Initialize all children to nullptr
        for (int i = 0; i < 26; i++) 
            children[i] = nullptr;
        count = 0; // Initially no children
    }

    // Destructor recursively deletes all children nodes to free memory
    ~TrieNode()
    {
        for (int i = 0; i < 26; i++)
            if (children[i])
                delete children[i];
    }
};

// Trie class to handle trie operations
class Trie
{
    TrieNode *root; // Root node of the Trie

public:
// Constructor initializes the root node
    Trie() : root(new TrieNode('\0')) {} 

    // Insert a word into the trie
    void insertWord(string word)
    {
        // Convert to lowercase to handle case insensitivity
        for (char &c : word) 
            c = tolower(c);
            // Start recursive insertion from root
        insertWord_rec(root, word, 0); 
    }

    // Search for a word in the trie
    bool searchWord(string word)
    {
        return searchWord_rec(root, word, 0); // Start recursive search from root
    }

    // Remove a word from the trie
    bool removeWord(string word)
    {    // Start recursive removal from root
        return removeWord_rec(root, word, 0);
    }

    // Find all words starting with a given prefix
    vector<string> searchPrefix(string word)
    {   // Convert prefix to lowercase
        for (char &c : word) 
            c = tolower(c);
        // To store words starting with the prefix
        vector<string> result; 
        TrieNode *node = root;

        // Traverse the trie to find the end of the prefix
        for (char c : word)
        {
            // Calculate the index for the current character
            int index = c - 'a'; 
            // If prefix not found, return empty result
            if (node->children[index] == nullptr) 
            {
                return result;
            }
            // Move to the next node
            node = node->children[index]; 
        }

        // Recursively find all words starting with the prefix
        searchPrefix_rec(node, word, result);
        return result;
    }
    // Destructor to clean up the root node
    ~Trie() { delete root; } 

private:
    // Recursive function to search for a word in the trie
    bool searchWord_rec(TrieNode *root, string word, int idx)
    {
        if (root == nullptr)
            return false;
        // If we've reached the end of the word
        if (word.length() == idx) 
        {   // Return whether it's a valid word
            return root->isEndOfWord; 
        }
        // Calculate the index of the current character
        int index = word[idx] - 'a';
        // Continue search recursively 
        return searchWord_rec(root->children[index], word, (idx + 1)); 
    }

    // Recursive function to insert a word into the trie
    void insertWord_rec(TrieNode *node, string word, int idx)
    {   // If we've reached the end of the word
        if (word.length() == idx) 
        {
            // Mark the node as the end of a word
            node->isEndOfWord = true; 
            return;
        }
        // Calculate the index for the current character
        int index = word[idx] - 'a'; 
        TrieNode *temp;

        // If the node already exists, move to it
        if (node->children[index] != nullptr) 
        {
            temp = node->children[index];
        }
        else
        {   
            // Create a new node if it doesn't exist
            temp = new TrieNode(word[idx]); 
            node->children[index] = temp;
            // Increment count for this node
            node->count++; 
        }
        // Continue insertion recursively
        insertWord_rec(temp, word, (idx + 1)); 
    }

    // Recursive function to remove a word from the trie
    bool removeWord_rec(TrieNode *node, string word, int idx)
    {
        if (node == nullptr)
            return false;
        // If we've reached the end of the word
        if (word.length() == idx) 
        {
            if (node->isEndOfWord)
            {// Mark the node as not the end of a word
                node->isEndOfWord = false; 
            }
            return true;
        }

        // Calculate the index for the current character
        int index = word[idx] - 'a'; 
        // If the character exists, continue removal recursively
        if (node->children[index] != nullptr) 
        {
            return removeWord_rec(node->children[index], word, (idx + 1));
        }
        else
        {
            return false; // If the character doesn't exist, return false
        }
    }

    // Recursive function to find all words starting with the prefix
    void searchPrefix_rec(TrieNode *node, string currentWord, vector<string> &result)
    {
        if (node == nullptr)
            return;

        if (node->isEndOfWord) // If it's the end of a word, add it to the result
            result.push_back(currentWord);

        // Traverse all children nodes to find all possible words
        for (int i = 0; i < 26; i++)
        {
            if (node->children[i])
            {
                searchPrefix_rec(node->children[i], currentWord + node->children[i]->data, result);
            }
        }
    }
};

int main()
{
    Trie dictionary;

    // List of words to insert into the trie
    vector<string> library = {"apple", "air", "airport", "airline", "arm", "article","abhi","ace", "black", "red", "green", "lime", "limegreen", "love", "lonely", "about", "that", "found","find", "get","big","bigger", "greater", "got","hot", "ice", "juice", "acid", "salad", "sampoo","peaceful", "country", "dogs","cheese", "yes", "upcoming", "events", "festival", "kitten", "voice", "xray", "zombie", "white", "queen", "rabbit","xyz", "bubble", "cut", "vectors", "map", "search", "hive", "fruits", "windows", "months", "days", "sudoku", "histograms"};

    // Insert words from library into the trie
    for (auto word : library)
    {
        dictionary.insertWord(word);
    }

    string text;
    cout << "Enter a word: ";
    cin >> text;

    // Search for words starting with the given prefix
    vector<string> result = dictionary.searchPrefix(text);
    if (result.empty())
    {
        cout << "No words found that start with " << text << endl;
        return 0;
    }
    else
    {
        cout << "Words starting with " << text << ": \n";
        for (auto word : result)
        {
            cout << "\t\t\t" << word << endl;
        }
    }

    return 0;
}
