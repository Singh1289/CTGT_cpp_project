#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void graphTraversal_BFS(vector<vector<int>> &list, int vertex, int source) {
    vector<bool> visited(vertex + 1, false);
    queue<int> Que;
    visited[source] = true;
    Que.push(source);

    while (!Que.empty()) {
        int front = Que.front();
        Que.pop();
        cout << front << " ";

        for (auto x : list[front]) {
            if (!visited[x]) {
                visited[x] = true;
                Que.push(x);
            }
        }
    }
    cout<<endl;
}

int main() {
    int vertex = 5; 
    vector<vector<int>> adjList(vertex + 1);

    // for a directed graph
    adjList[1] = {2, 3};
    adjList[2] = {4};
    adjList[3] = {4, 5};
    adjList[4] = {};
    adjList[5] = {};

    cout << "BFS starting from vertex 0: ";
    graphTraversal_BFS(adjList, vertex, 0);
    cout << "BFS starting from vertex 1: ";
    graphTraversal_BFS(adjList, vertex, 1);
    cout << "BFS starting from vertex 2: ";
    graphTraversal_BFS(adjList, vertex, 2);
    cout << "BFS starting from vertex 3: ";
    graphTraversal_BFS(adjList, vertex, 3);
    cout << "BFS starting from vertex 4: ";
    graphTraversal_BFS(adjList, vertex, 4);
    cout << "BFS starting from vertex 5: ";
    graphTraversal_BFS(adjList, vertex, 5);
    cout << endl;

    return 0;
}
