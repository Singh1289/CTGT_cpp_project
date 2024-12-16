#include "myDoubleLL.h"

// Destructor
template <typename T>
myDoubleLL<T>::~myDoubleLL()
{
    // Start from the head and delete all nodes
    Node<T> *current = this->head;
    while (current)
    {
        Node<T> *temp = current;   // Temporarily store the current node
        current = current->next;   // Move to the next node
        delete temp;               // Free the memory of the current node
    }
}

// Constructor: Initializes an empty list
template <typename T>
myDoubleLL<T>::myDoubleLL()
{
    this->head = nullptr;  // Initially, there is no head
    this->tail = nullptr;  // Initially, there is no tail
}

// Insert a new node at the end (tail) of the list
template <typename T>
Node<T> *myDoubleLL<T>::push(int key, T data)
{
    // Create a new node with the given key and data
    Node<T> *newNode = new Node<T>(key, data);

    if (this->head == nullptr)
    {
        // If the list is empty, set both head and tail to the new node
        this->head = this->tail = newNode;
    }
    else
    {
        // Otherwise, insert the new node at the end (tail)
        newNode->prev = this->tail;    // Set the previous pointer of new node to the current tail
        this->tail->next = newNode;    // Set the next pointer of the current tail to the new node
        this->tail = newNode;          // Update the tail to the new node
    }
    return newNode; // Return the new node
}

// Remove a node from the front (head) of the list
template <typename T>
void myDoubleLL<T>::pop()
{  
    // Store the current head to delete it later
    Node<T>* node = this->head;

    // Move the head pointer to the next node
    this->head = this->head->next;

    // If there is a new head, set its previous pointer to nullptr
    if (this->head)
        this->head->prev = nullptr;

    // Delete the old head node
    delete node;
}

// Move a node to the back (tail) of the list
template <typename T>
void myDoubleLL<T>::moveToBack(Node<T> *node)
{
    // If the node is already the tail, do nothing
    if (node == this->tail)
        return;

    // Detach the node from its current position
    if (node == this->head)
    {
        // If it's the head, update the head pointer
        this->head = this->head->next;
        if (this->head)
            this->head->prev = nullptr; // Set the previous pointer of the new head to nullptr
    }
    else
    {
        // If it's somewhere in the middle, update the previous and next pointers
        node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
    }

    // Add the node to the back (tail)
    node->next = nullptr;            // Set the next pointer of the node to null (it will be the last)
    node->prev = this->tail;         // Set the previous pointer of the node to the current tail
    if (this->tail)
        this->tail->next = node;     // Update the current tail's next pointer to point to the node
    this->tail = node;               // Update the tail to the new node
}

// Print the entire linked list from head to tail
template <typename T>
void myDoubleLL<T>::printLL(){
    // If the list is empty, print a message and return
    if (head == nullptr) {
        cout << "Empty List" << endl;
        return;
    }

    // Otherwise, traverse the list and print each node's data
    Node<T> *temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";  // Print the data of the current node
        temp = temp->next;          // Move to the next node
    }
    cout << endl;  // Print a newline after the list
}

// Change the position of a node: Move it to the back (most recently used)
template <typename T>
void myDoubleLL<T>::changeLL(Node<T> *node)
{
    // Move the node to the back of the list
    this->moveToBack(node);
    return;
}
