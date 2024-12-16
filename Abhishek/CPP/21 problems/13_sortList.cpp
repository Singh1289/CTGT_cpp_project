/*
Given k sorted linked lists, merge them into a single sorted linked list.
For example:
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Input:
An array of k sorted linked lists.
Output:
A merged sorted linked list.
Constraints:
The number of lists k can be up to 10^4, and each list can have up to 10^4 nodes.

*/
#include<iostream>
#include<string>
#include<vector>
#include<queue>

using namespace std;

// Definition of a singly linked list node
struct ListNode {
    int val;  // Value of the node
    ListNode* next;  // Pointer to the next node
    // Constructor to initialize the node with a value
    ListNode(int x) : val(x), next(nullptr) {}
};

// Comparator struct for the priority queue to sort the nodes by their value
struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        // Return true if a's value is greater than b's, for min-heap
        return a->val > b->val;
    }
};

// Function to merge multiple sorted linked lists
ListNode* mergeLinkedList(vector<ListNode*>& lists) {
    // Create a priority queue (min-heap) to store nodes
    priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

    // Push the first node of each list into the priority queue
    for (auto list : lists) {
        if (list) pq.push(list);  
    }

    // Create a dummy node to simplify the merge process
    ListNode* dummy = new ListNode(0);

     // Pointer to build the merged list
    ListNode* curr = dummy; 

    // Process the nodes in the priority queue
    while (!pq.empty()) {

        // Get the node with the smallest value
        curr->next = pq.top();
        // Remove the node from the queue
        pq.pop();  
        // Move the current pointer to the next node
        curr = curr->next;  
        
        // If there is a next node in the current list, push it to the queue
        if (curr->next) pq.push(curr->next);
    }

    // Return the merged list (skip the dummy node)
    return dummy->next;
}

// Function to print the linked list
void printList(ListNode* head) {
    // Traverse and print each node's value
    while (head) {
        cout << head->val << " -> ";
        // Move to the next node
        head = head->next;  
    }
    cout << "end" << endl;  
}

// Function to create a linked list from a vector of integers
ListNode* createList(const vector<int>& nums) {
    ListNode* head = nullptr;  
    ListNode* tail = nullptr;  

    // Iterate through the vector and create a linked list
    for (int num : nums) {
        if (!head) {
            // If the list is empty, create the first node
            head = new ListNode(num);
            tail = head;
        } else {
            // If the list is not empty, append a new node
            tail->next = new ListNode(num);
            // Move the tail pointer to the new node
            tail = tail->next;  
        }
    }
    return head;  
}


int main() {
    // Define the input as a 2D vector of integers representing sorted lists
    vector<vector<int>> input = {{1, 4, 5}, {1, 3, 4}, {2, 6}};
    vector<ListNode*> lists; 

    // Create linked lists from the input vectors and add them to the lists vector
    for (auto& nums : input) {
        lists.push_back(createList(nums));
    }

    // Merge the linked lists
    ListNode* result = mergeLinkedList(lists);

    // Print the merged linked list
    printList(result);

    return 0;  // End of the program
}


