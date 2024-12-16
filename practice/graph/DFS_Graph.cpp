// DFS graph

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(vector<vector<int>> &graph, int start, vector<bool> &visited)
{
    visited[start] = true;
    cout << start << " ";
    for (int neighbor : graph[start])
    {
        if (!visited[neighbor])
        {
            dfs(graph, neighbor, visited);
        }
    }
    return;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
    }
    vector<bool> visited(n, false);
    dfs(graph, 0, visited);
    return 0;
}

/*
    // leet code 463
    class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, i, j,perimeter);
                    break;
                }
            }
        }
        return perimeter;
    }

    void dfs(vector<vector<int>>& grid, int i, int j, int& perimeter){
        if(i<0|| i>=grid.size() || j<0 || j>=grid[0].size()|| grid[i][j]==0){
            perimeter++;
            return;
        }

        if(grid[i][j]==-1) return;

        grid[i][j]= -1;

        dfs(grid,i-1,j,perimeter);
        dfs(grid,i,j+1,perimeter);
        dfs(grid,i+1,j,perimeter);
        dfs(grid,i,j-1,perimeter);

    }
};

*/