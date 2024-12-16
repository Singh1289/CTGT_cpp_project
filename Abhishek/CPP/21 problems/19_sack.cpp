/*
Given a list of n items with weights and values, and a knapsack with a maximum weight capacity, determine the maximum value that can be obtained by selecting a subset of items without exceeding the weight capacity.
For example:
Input:
weights = [2, 3, 4, 5]
values = [3, 4, 5, 6]
capacity = 5
Output: 7 (The optimal subset is {2, 3} with total value 7).
Input:
Two arrays: weights[] and values[] representing the items.
An integer capacity, representing the maximum weight of the knapsack.
Output:
The maximum total value that can be achieved without exceeding the weight limit.
Constraints:
The number of items n can be up to 100.
The capacity can be up to 1000.

*/

#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

// Function to compute the maximum value that can be obtained from the knapsack problem
int knapSack(vector<int> &weights, vector<int> &values, int capacity)
{
    // Create a vector of pairs (weight, value) for each item
    vector<pair<int, int>> pairs;
    for (int i = 0; i < values.size(); i++) {
        pairs.push_back({weights[i], values[i]});
    }

    // Sort the pairs based on the value-to-weight ratio in descending order
    // The lambda function computes the ratio for each pair (value/weight)
    sort(pairs.begin(), pairs.end(), [](pair<int, int> &a, pair<int, int> &b) {
        double ratioA = (double)a.second / a.first;
        double ratioB = (double)b.second / b.first;
        // Sort in descending order of ratio
        return ratioA > ratioB;  
    });

    // Initialize the maximum value that can be obtained
    int n = pairs.size();
    int result = 0;

    // Try adding items one by one and calculate the total value
    for (int i = 0; i < n; i++) {
        int tempWeight = 0, tempValue = 0;

        // Try adding items starting from the current one (greedy approach)
        for (int j = i; j < n; j++) {
            // If the item can fit into the knapsack, add it
            if (tempWeight + pairs[j].first <= capacity) {
                tempWeight += pairs[j].first;
                tempValue += pairs[j].second;
                // Update the maximum value obtained so far
                result = max(result, tempValue);
            }
        }
    }
    
    return result;  
}

int main()
{
    // Initialize vectors to hold the weights and values of the items
    vector<int> weights;
    vector<int> values;

    int n;  // Number of items
    cout << "Enter the number of items: ";
    cin >> n;

    // Resize the weight and value vectors based on the number of items
    weights.resize(n);
    values.resize(n);

    // Input the weights of the items
    for (int i = 0; i < n; i++) {
        cout << "Weight of item " << i + 1 << ": ";
        cin >> weights[i];
    }

    cout << "\n";

    // Input the values of the items
    for (int i = 0; i < n; i++) {
        cout << "Value of item " << i + 1 << ": ";
        cin >> values[i];
    }

    // Input the capacity of the knapsack
    int capacity;
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    // Call the knapSack function to calculate the maximum value
    int maxValue = knapSack(weights, values, capacity);

    // Output the maximum value that can be obtained
    cout << "Maximum value that can be obtained: " << maxValue << endl;

    return 0; 
}

