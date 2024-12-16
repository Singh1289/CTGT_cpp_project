#ifndef Utility_H
#define Utility_H
#include <unordered_map>
// Include the user define doubly linked list header
#include "mydoubleLL.h" 

// LRU Cache class
template <typename T>
class LRUCache
{
private:
    // Keeps track of the current number of elements in the cache
    int count;

public:
    int capacity;                      // Maximum capacity of the cache
    myDoubleLL<T> list;                // Doubly linked list to maintain the order of usage (most recent to least recent)
    unordered_map<int, Node<T> *> map; // HashMap to store keys and pointers to nodes in the doubly linked list

    // Constructor with no arguments
    LRUCache();

    // Constructor with capacity
    LRUCache(int cap);

    // Method to set the capacity of the cache
    void setCapacity(int cap);

    // Method to add or update a key-value pair in the cache
    void put(int key, T value);

    // Method to get the value associated with a key
    T get(int key);

    // Destructor to clean up the cache
    ~LRUCache<T>();
};

// Include the template definitions for the methods
#include "LRU_utility.tpp"

#endif // Utility_H
