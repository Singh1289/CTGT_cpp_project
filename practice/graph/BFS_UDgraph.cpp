// leetcode - 1971,997

#include<iostream>
#include <vector>
#include <queue>
using namespace std;

void addEdge(vector<int> list[],int start,int end);
void printGraph(vector<int> list[],int vextex);
void grapgTraversal_BSF(vector<int> list[],int vertex,int source);
void bfsDisCountinousGraph(vector<int> list[],int vertex);
void bfs(vector<int> list[], int source, vector<bool> &visited);

int main()
{
    //no of vertex in the graph
    int v=5;
    int source=0;
    vector<int> list[v];
    addEdge(list,0,1);
    addEdge(list,0,2);
    addEdge(list,1,2);
    addEdge(list,1,3);
    addEdge(list,2,3);
    addEdge(list,4,3);
    addEdge(list,4,2);

    printGraph(list,v);
    cout<<"\nGraph traversal from source vertex "<<source<<": ";
   
    grapgTraversal_BSF(list,v,source);
    cout<<"\nGraph traversal from source vertex 1"<<": ";
    grapgTraversal_BSF(list,v,1);
    cout<<"\nGraph traversal from source vertex "<<2<<": ";
    grapgTraversal_BSF(list,v,2);
    cout<<"\nGraph traversal from source vertex "<<3<<": ";
    grapgTraversal_BSF(list,v,3);
    cout<<"\nGraph traversal from source vertex "<<4<<": ";
    grapgTraversal_BSF(list,v,4);

    bfsDisCountinousGraph(list,v);
    return 0;
}


void addEdge(vector<int> list[],int start,int end)
{
    list[start].push_back(end);
    list[end].push_back(start);  
}
void printGraph(vector<int> list[],int vextex)
{
    for(int i=0;i<vextex;i++)
    {
        cout<<"Vertex "<<i<<"-> ";
        for(auto x : list[i])
        {
            cout<<x<<" ";
        }
        cout<<endl;
    }
}

void grapgTraversal_BSF(vector<int> list[],int vertex,int source)
{
    vector<bool> visited(vertex+1, false);
    queue<int> Que;
    int front;
    visited[source]=true;
    Que.push(source);
    while(!Que.empty())
    {
        front = Que.front();
        Que.pop();
        cout<<front<<" ";
        
        for(auto x : list[front])
        {
            if(!visited[x])
            {
                visited[x]=true;
                Que.push(x);
            }
        }
    }
    cout<<endl;
}


void bfsDisCountinousGraph(vector<int> list[],int vertex)
{

    vector<bool> visited(vertex+1, false);
    int count =0;
    for(int i=0;i<vertex;i++){
        if(!visited[i])
        {
            count++;
            cout<<"Connected Component of vertex "<<i<<": ";
            bfs(list, i, visited);
            cout<<endl;
        }
    }
    cout<<"Number of Connected Components: "<<count<<endl;
}

void bfs(vector<int> list[], int source, vector<bool> &visited)
{
    queue<int> Que;
    int front;
    visited[source]=true;
    Que.push(source);

    while(!Que.empty())
    {
        front = Que.front();
        Que.pop();
        cout<<front<<" ";
        
        for(auto x : list[front])
        {
            if(!visited[x])
            {
                visited[x]=true;
                Que.push(x);
            }
        }
    }
}