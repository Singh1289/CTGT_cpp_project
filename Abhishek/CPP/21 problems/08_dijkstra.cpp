/*
Given a weighted graph, find the shortest path from a source node to all other nodes using Dijkstra’s Algorithm. The graph is represented as an adjacency matrix or list.
Input:
A graph represented as an adjacency matrix/list.
A source node.
Output:
A list of the shortest distances from the source node to all other nodes.
Constraints:
The graph can have up to 10^5 nodes.
*/
 #include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Pair to represent (distance, node)
typedef pair<int, int> pairs; 

// Function to perform Dijkstra's algorithm to find the shortest paths
vector<int> dijkstra(int n, vector<vector<pairs>> &graph, int source) {
    // Initialize distances to all nodes as infinity
    vector<int> dist(n, INT_MAX); 
    // Min-heap priority queue to select the next node with the smallest distance
    priority_queue<pairs, vector<pairs>, greater<pairs>> pq; 
    
    // Distance to source node is 0
    dist[source] = 0; 
    // Start from the source node
    pq.push({0, source}); 

    // Process the priority queue
    while (!pq.empty()) {
        // Get the node with the smallest distance
        int currentDistance = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        // Skip if the current distance is greater than the already found shortest distance
        if (currentDistance > dist[currentNode]) continue;

        // Explore the neighbors of the current node
        for (auto neighbor : graph[currentNode]) {
            int nextNode = neighbor.first;
            int weight = neighbor.second;

            // Relax the edge if a shorter path is found
            if (dist[currentNode] + weight < dist[nextNode]) {
                dist[nextNode] = dist[currentNode] + weight;
                // Add the neighbor to the priority queue
                pq.push({dist[nextNode], nextNode}); 
            }
        }
    }
    // Return the final distances from the source
    return dist; 
}

int main() {
    int n, m;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<pairs>> graph(n); // Adjacency list to represent the graph

    // Read the graph's edges (u, v, w) where u and v are nodes and w is the edge weight
    cout << "Enter the edges (u v w) where u and v are nodes (0-based) and w is weight:\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // Add edge u-v with weight w
        graph[u].push_back({v, w}); 
        // Add edge v-u with weight w (for undirected graph)
        graph[v].push_back({u, w}); 
    }

    int source;
    cout << "Enter the source node: ";
    cin >> source;

    // Get the shortest distances from the source node
    vector<int> distances = dijkstra(n, graph, source);

    // Print the shortest distances
    cout << "Shortest distances from " << source << ":\n";
    for (int i = 0; i < n; i++) {
        if (distances[i] == INT_MAX) {
            // If the node is unreachable
            cout << " to " << i << ": Unreachable\n"; 
        } else {
            // Print the distance to the node
            cout << " to " << i << ": " << distances[i] << "\n"; 
        }
    }

    return 0;
}
