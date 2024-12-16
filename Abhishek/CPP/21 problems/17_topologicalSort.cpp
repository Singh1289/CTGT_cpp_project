/*
Given a directed acyclic graph (DAG), perform a topological sort of the vertices. The topological order of a directed graph is a linear ordering of the vertices such that for every directed edge uv, vertex u comes before v in the ordering.
For example:
Input:
Graph:
  5 → 2
  5 → 0
  4 → 0
  4 → 1
  2 → 3
  3 → 1
Output: [5, 4, 2, 3, 1, 0]
Input:
A directed acyclic graph represented as an adjacency list.
Output:
A list of vertices in topologically sorted order.
Constraints:
The graph can have up to 10^5 vertices.
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Define Graph as a vector of vectors of integers
#define Graph vector<vector<int>>

// DFS function to explore the graph and store vertices in the stack after exploration
void dfs(Graph &graph, int vertex, vector<bool> &visited, stack<int> &st) {
    // Mark the current vertex as visited
    visited[vertex] = true;

    // Recursively visit all the unvisited neighbours
    for (int neighbour : graph[vertex]) {
        if (!visited[neighbour]) {
            dfs(graph, neighbour, visited, st);
        }
    }

    // After visiting all neighbours, push the current vertex onto the stack
    st.push(vertex);
}

// Topological Sort function that returns the topologically sorted vertices
vector<int> topologicalSort(Graph &graph) {
    // Create a visited array to keep track of the visited vertices
    vector<bool> visited(graph.size(), false);

    // Vector to store the topological sort result
    vector<int> result;

    // Stack to store vertices in the order of their processing (for reverse topological order)
    stack<int> st;

    // Traverse all the vertices in the graph
    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            // Perform DFS for unvisited vertices
            dfs(graph, i, visited, st);
        }
    }

    // Pop elements from the stack to get the topological sort (reverse order)
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

// Helper function to detect cycles in the graph using DFS recursion
bool isCyclePresent_rec(Graph &graph, int vertex, vector<bool> &visited, vector<bool> &stack) {
    // Mark the current vertex as visited and part of the recursion stack
    visited[vertex] = true;
    stack[vertex] = true;

    // Recursively visit all the unvisited neighbours
    for (int neighbour : graph[vertex]) {
        if (!visited[neighbour] && isCyclePresent_rec(graph, neighbour, visited, stack)) {
            return true;
        }
        // If the neighbour is already in the recursion stack, a cycle is detected
        else if (stack[neighbour]) {
            return true;
        }
    }

    // Remove the current vertex from the recursion stack as we backtrack
    stack[vertex] = false;
    return false;
}

// Function to check if the graph contains a cycle using DFS
bool isCyclePresent(Graph &graph) {
    // Visited array to track if a vertex has been visited
    vector<bool> visited(graph.size(), false);

    // Stack array to track the recursion stack
    vector<bool> stack(graph.size(), false);

    // Traverse all the vertices in the graph
    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i] && isCyclePresent_rec(graph, i, visited, stack)) {
            // If cycle is detected, return true
            return true;
        }
    }
    // No cycle found, return false
    return false;
}

int main() {
    Graph graph;
    int n, m;

    // Prompt the user to enter the number of vertices and edges
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    // Resize the graph to accommodate 'n' vertices
    graph.resize(n);

    // Loop to take 'm' edges as input and build the graph
    for (int i = 0; i < m; i++) {
        int u, v;

        // Ask the user to input each edge (u, v)
        cout << "Enter edge " << i + 1 << " (u, v): ";
        cin >> u >> v;

        // Add the edge to the graph (from u to v)
        graph[u].push_back(v);
    }

    // Check if the graph contains a cycle
    if (isCyclePresent(graph)) {
        cout << "Cycle present in the graph. So solution possible." << endl;
        return 0;  // If cycle is detected, exit the program
    }

    // Perform topological sorting if no cycle is present
    vector<int> res = topologicalSort(graph);
    int j = res.size();

    // Output the topological sort result
    cout << "Topological Sorting arrangement: [ ";
    for (int i : res) {
        cout << i << " ";
        if (j > 1) {
            cout << ", ";
        }
        j--;
    }
    cout << "]" << endl;

    return 0;
}
