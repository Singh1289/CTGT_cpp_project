#include "LRU_utility.h"

// Default constructor with a default capacity of 5
template <typename T>
LRUCache<T>::LRUCache() : capacity(5), count(0) {}

// Constructor with user-defined capacity
template <typename T>
LRUCache<T>::LRUCache(int cap) : capacity(cap), count(0) {}

// Set a new capacity for the cache
template <typename T>
void LRUCache<T>::setCapacity(int cap) {
    this->capacity = cap;
}

// Method to insert or update a key-value pair in the cache
template <typename T>
void LRUCache<T>::put(int key, T value) {
    if (this->map.find(key) != this->map.end()) {
        // If the key is already present, update the value and move it to the front
        Node<T> *it = this->map[key];
        it->data = value;
        // Move the node to the front
        list.changeLL(it);  
    } else {
        // If the key is not present, create a new node
        // Push node to the front of the list
        Node<T> *newNode = list.push(key, value);  
        map[key] = newNode;
        
        if (count != capacity) {
            // Increment the count if the cache is not yet full
            count++;  
        } else {
            // If the cache is full, remove the least recently used (LRU) item
            // Get the key of the LRU node 
            int lruKey = list.head->key;  
            // Remove the key from the map
            map.erase(lruKey); 
            // Remove the LRU node from the list 
            list.pop();  
        }
    }
    return;
}

// Method to get the value associated with a key
template <typename T>
T LRUCache<T>::get(int key) {
    if (map.find(key) != map.end()) {
        // If the key is found, move the corresponding node to the front
        Node<T> *it = map[key];
        list.changeLL(it);
         // Return the value associated with the key
        return it->data; 
    } else {
        // If the key is not found, return -1
        return -1;  
    }
}

// Destructor to clear the map when the cache is destroyed
template <typename T>
LRUCache<T>::~LRUCache() {
    // Clears the map when the cache is destroyed
    map.clear();  
}
