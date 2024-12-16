#ifndef MY_DOUBLE_LL_H
#define MY_DOUBLE_LL_H

#include <iostream>
using namespace std;

// Node class represents a node in the doubly linked list
template <typename T>
class Node
{
public:
    int key;   // Key for the node (used to identify the node, typically for caching)
    T data;    // Data stored in the node
    Node *next; // Pointer to the next node in the list
    Node *prev; // Pointer to the previous node in the list

    // Constructor to initialize the node with a key and data
    Node(int key, T data) : key(key), data(data), next(nullptr), prev(nullptr) {};

    // Destructor for Node (not necessarily needed, but defined for completeness)
    ~Node() {};
};

// Doubly Linked List class to manage the nodes
template <typename T>
class myDoubleLL
{
public:
    Node<T> *head; // Pointer to the head (front) of the list
    Node<T> *tail; // Pointer to the tail (end) of the list

    // Default constructor: initializes an empty list
    myDoubleLL();

    // Adds a new node to the front of the list and returns the new node
    Node<T>* push(int key, T data);

    // Prints the entire list from head to tail
    void printLL();

    // Removes the node from the tail of the list (least recently used)
    void pop();

    // Moves the specified node to the front of the list (most recently used)
    void changeLL(Node<T>* node);

    // Destructor to clean up
    ~myDoubleLL();

private:
    // Helper function to move the specified node to the back of the list (used for LRU logic)
    void moveToBack(Node<T> *node);
};
// Include the implementation file for the template functions
#include "myDoubleLL.tpp" 

#endif // MY_DOUBLE_LL_H
