/*
Implement a program that checks if an undirected graph has a cycle. The graph is represented as an adjacency list.
Input:
A number of nodes and edges defining the graph in the adjacency list form.
A graph is undirected, meaning each edge connects two nodes bidirectionally.
Output:
Return true if there is a cycle, otherwise false.

*/

#include <iostream>
#include <vector>

using namespace std;

// Function to print the adjacency list representation of the graph
void printGraph(vector<vector<int>> &graph)
{
    for (int i = 0; i < graph.size(); i++)
    {
        cout << i << " -> "; // Print current node
        for (int j : graph[i])
        {
            cout << j << " "; // Print all connected nodes
        }
        cout << endl;
    }
}

// Function to take input for the graph edges
void takeInput(vector<vector<int>> &graph, int num)
{
    for (int i = 0; i < graph.size(); i++)
    {
        cout << "Enter Edges (u, v): ";
        int u, v;
        cin >> u >> v; // Input edge between nodes u and v
        graph[u].push_back(v); // Add v to u's adjacency list
        graph[v].push_back(u); // Add u to v's adjacency list (undirected graph)
    }
}

// Helper function to detect a cycle in the graph using DFS
bool isCyclic(int node, vector<vector<int>> &graph, vector<bool> &visited, int parent)
{
    visited[node] = true; // Mark the current node as visited

    // Traverse all neighbors of the current node
    for (auto neighbor : graph[node])
    {
        // If the neighbor is not visited, recursively check for cycles
        if (!visited[neighbor])
        {
            if (isCyclic(neighbor, graph, visited, node))
                return true;
        }
        // If the neighbor is visited and not the parent, a cycle exists
        else if (neighbor != parent)
        {
            return true;
        }
    }
    return false; // No cycle found
}

// Function to check if there is any cycle in the graph
bool checkForCycle(vector<vector<int>> &graph, vector<bool> &visited)
{
    // Iterate through all nodes in the graph
    for (int i = 0; i < graph.size(); i++)
    {
        // If the node is not visited, perform a DFS to check for cycles
        if (!visited[i])
        {
            if (isCyclic(i, graph, visited, -1))
                return true;
        }
    }
    return false; // No cycle found in the graph
}

int main()
{
    int num; // Number of nodes in the graph
    cout << "No. of Nodes: ";
    cin >> num;

    // Initialize adjacency list and visited array
    vector<vector<int>> graph(num);
    vector<bool> visited(num, false);

    // Input graph edges
    takeInput(graph, num);

    // Print the adjacency list of the graph
    printGraph(graph);

    // Check for the presence of a cycle in the graph
    bool hasCycle = checkForCycle(graph, visited);

    // Output the result
    if (hasCycle)
        cout << "There is a cycle in the graph." << endl;
    else
        cout << "There is no cycle in the graph." << endl;

    return 0;
}
