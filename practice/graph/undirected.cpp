#include<iostream>
#include <vector>
using namespace std;

void addEdge(vector<int> list[],int start,int end);
void printGraph(vector<int> list[],int vextex);

int main()
{
    //no of vertex in the graph
    int v=4;
    vector<int> list[v];
    addEdge(list,0,1);
    addEdge(list,2,0);
    addEdge(list,2,1);
    addEdge(list,2,3);

    printGraph(list,v);

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