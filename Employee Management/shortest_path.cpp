/*

Problem: Given a source vertex s from a set of vertices V in a weighted directed graph,
where all edge weights $$w(u, v)$$ are non-negative, compute the shortest path weights
$$d(s, v)$$ from the source vertex s to all vertices v in the graph.
Input:
1. An $$n \times n$$ matrix representing the adjacency matrix of the graph where:
matrix(i, j) represents the weight of the edge from vertex i to vertex j.
If there is no edge between i and j, then matrix(i, j) will be -1.
matrix(i, i) will be 0 since the distance from a node to itself is 0.
2. Source vertex (s): Index of the source vertex ($$1 \le s \le n$$).
Output: For each vertex v in the graph, print the shortest distance $$d(s, v)$$ from the source
vertex s to vertex v. If there is no path from vertex s to a vertex v, output -1.
Instructions: Please adhere to the input and output formats as depicted in the examples.
Examples:
Input: Graph: [0 10 5 -1 -1], [-1 0 2 -1 3], [-1 -1 0 1 2], [-1 -1 -1 0 1], [-1 -1 -1 -1 0]
Source vertex: 1
Output: Shortest distance $$d(s,v)$$: [0, 10, 5, 7, 7]
Input: Graph: [0 2 -1], [-1 0 4], [-1 -1 0]
Source vertex: 1
Output: Shortest distance $$d(s,v)$$: [0, 2, 6]

*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <climits>
using namespace std;

void trimString(string &str)
{
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if (start == string::npos || end == string::npos)
    {
        str = "";
    }
    else
    {
        str = str.substr(start, end - start + 1);
    }
}

int toDecimal(string str)
{
    int decimal = 0;
    const char *strr = str.c_str();
    if (strr[0] == '0' && (strr[1] == 'x' || strr[1] == 'X'))
        decimal = strtoul(strr, nullptr, 16);
    else if (strr[0] == '0' && str.length() > 1)
        decimal = strtoul(strr, nullptr, 8);
    else if (isdigit(strr[0]) || (strr[0] == '-' && isdigit(strr[1])))
        decimal = strtol(strr, nullptr, 10);
    else
    {
        cout << "Invalid decimal: " << str << endl;
        exit(1);
    }
    return decimal;
}

void convertIntoArray(vector<int> &array, const string &str)
{
    size_t start = str.find('[');
    size_t end = str.find(']');
    if (start == string::npos || end == string::npos || start >= end)
    {
        cout << "Invalid input: " << str << endl;
        exit(-1);
    }

    string content = str.substr(start + 1, end - start - 1);
    trimString(content);

    size_t pos = 0;
    while ((pos = content.find(' ')) != string::npos)
    {
        string token = content.substr(0, pos);
        trimString(token);
        if (token == "-0")
        {
            cout << "Invalid input: " << token << endl;
            exit(-1);
        }
        array.push_back(toDecimal(token));
        content.erase(0, pos + 1);
    }

    trimString(content);
    if (!content.empty())
    {
        if (content == "-0")
        {
            cout << "Invalid input: " << content << endl;
            exit(-1);
        }
        array.push_back(toDecimal(content));
    }
}

vector<vector<int>> extractGraph(string &content)
{
    vector<vector<int>> result;
    size_t pos = 0;
    int size = 0;

    while ((pos = content.find("],")) != string::npos)
    {
        string token = content.substr(0, pos + 1);
        trimString(token);
        vector<int> row;
        convertIntoArray(row, token);

        if (size == 0)
            size = row.size();
        else if (row.size() != size)
        {
            cout << "Error: Rows are of inconsistent size." << endl;
            exit(-1);
        }

        result.push_back(row);
        content.erase(0, pos + 2); // Remove "],"
    }

    trimString(content);
    if (!content.empty())
    {
        vector<int> row;
        convertIntoArray(row, content);
        if (row.size() != size)
        {
            cout << "Error: Rows are of inconsistent size." << endl;
            exit(-1);
        }
        result.push_back(row);
    }

    if (result.size() != size)
    {
        cout << "Error: Matrix is not square." << endl;
        exit(-1);
    }

    return result;
}

int minDistance(vector<int> &dist, vector<bool> &visited, int n)
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++)
    {
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    }
    return min_index;
}

int main()
{
    string input;
    cout << "Enter input string: ";
    getline(cin, input);

    trimString(input);
    if (input.empty())
    {
        cout << "Invalid input!" << endl;
        return 0;
    }

    vector<vector<int>> graph = extractGraph(input);

    // Print the graph
    cout << "Graph:" << endl;
    for (const auto &row : graph)
    {
        for (int val : row)
            cout << setw(3) << val << " ";
        cout << endl;
    }

    // dikstra graph
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    dist[0] = 0;
    vector<bool> visited(n, false);

    for (int count = 0; count < n - 1; count++)
    {
        int u = minDistance(dist, visited, n);
        visited[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && graph[u][v] != -1 &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    cout << "Shortest distance d(s,v) from source vertex 1:" << endl;
    for (int i = 0; i < n; i++)
        cout << "d(" << 1 << "," << i + 1 << ") = " << dist[i] << endl;

    return 0;
}
