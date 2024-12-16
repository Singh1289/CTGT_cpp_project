#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

void trimString(string &str)
{
    int start = 0, end = str.length() - 1;
    while (start < end && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r'))
        start++;
    while (start < end && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r'))
        end--;
    if(str[end] == ',') end--;
    str = str.substr(start, end - start + 1);
}

long toDecimal(string strr)
{
    long decimal = 0;
    const char *str = strr.c_str();
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        decimal = strtoul(str, nullptr, 16);
    else if (str[0] == '0' && (str[1] != 'x' || str[1] != 'X'))
        decimal = strtoul(str, nullptr, 8);
    else if ((str[0] == '-' && str[1] > '0' && str[1] <= '9') || (str[0] > '0' && str[0] <= '9'))
        decimal = strtoul(str, nullptr, 10);
    else if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z'))
    {
        if (strlen(str) > 1)
        {
            cout << "invalid string";
            exit(1);
        }
        decimal = str[0];
    }
    else
    {
        cout << "invalid string :" << str;
        exit(1);
    }

    return decimal;
}

void convertIntoArray(vector<long> &array, const string &str, int &idx)
{
    long temp = 0;

    size_t start = str.find('[');
    size_t end = str.find(']');
    if (start == string::npos || end == string::npos || start >= end)
    {
        cout << "Invalid input2: " << endl;
        exit(-1);
    }

    string content = str.substr(start + 1, end - start - 1);
    trimString(content);
    size_t pos = 0;
    while ((pos = content.find(',')) != string::npos)
    {
        string token = content.substr(0, pos);
        trimString(token);
        if (token != "NULL" && token != "null" && token != "Null")
        {
            if (token == "-0")
            {
                cout << "Invalid input ";
                exit(-1);
            }
            temp = toDecimal(token);
            array.push_back(temp);

            idx++;
        }
        else
        {
            cout << "Invalid input ";
            exit(-1);
        }

        content.erase(0, pos + 1);
    }

    trimString(content);
    if (content != "NULL" && content != "null" && content != "Null")
    {
        temp = toDecimal(content);
        array.push_back(temp);

        idx++;
    }
    else
    {
        cout << "Invalid input ";
        exit(-1);
    }
}

void printGrid(vector<vector<long> >& grid){
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
}


void printpath(vector<long>& path) {
    cout << "[ ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

void findAllPaths_rec(vector<vector<long>>& grid, vector<vector<bool>>& visited, int x, int y, int n, int m, vector<long>& path) {
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] == 0) {
        return;
    }
    visited[x][y] = true;
    path.push_back(grid[x][y]);

    if (x == n - 1 && y == m - 1) {
        if(path.size() < (n+m))  printpath(path);
    } else {
        findAllPaths_rec(grid, visited, x + 1, y, n, m, path); 
        findAllPaths_rec(grid, visited, x, y + 1, n, m, path); 
        // findAllPaths_rec(grid, visited, x - 1, y, n, m, path); 
        // findAllPaths_rec(grid, visited, x, y - 1, n, m, path); 
    }
    visited[x][y] = false;
    path.pop_back();
}

void findALlPaths(vector<vector<long>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    if (n == 0 || m == 0) {
        cout << "Grid is empty" << endl;
        return;
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<long> path;

    findAllPaths_rec(grid, visited, 0, 0, n, m, path);
}


int main()
{
    string input;
    cout << "Input: ";
    getline(cin, input);

    trimString(input);
    if (input.size() == 0 || input == "NULL" || input == "null" || input == "Null" || input == "-0")
    {
        cout << "Invalid input" << endl;
        return 0;
    }
    
    int idx;
    vector<long> temp;
    vector<vector<long>> grid;
    try
    {
        int prev = 0;
        size_t pos = 0;
        while ((pos = input.find(' ')) != string::npos){
            if(prev != 0 && prev != idx){ cout<<"invalid input:idx"<<endl; return 0; }
            idx = 0;
            string token = input.substr(0, pos);
            //cout<<"token: "<<token<<endl;
            convertIntoArray(temp, token,idx);
            if(idx==0){ cout<<"invalid input: 0"<<endl; return 0; }
            prev = idx;
            input.erase(0, pos + 1);
            grid.push_back(temp);
            temp.clear();
        }
        idx = 0;
        convertIntoArray(temp, input, idx);
        if(prev!= idx || idx == 0){ cout<<"invalid input: idx"<<endl; return 0; }
       // if(idx==0){ cout<<"invalid input: 0"<<endl; return 0; }
        grid.push_back(temp);
        temp.clear();
    }
    catch (...)
    {
        cout << "Invalid input:" << endl;
        return 0;
    }

    printGrid(grid);

    cout<<"output:"<<endl;
    findALlPaths(grid);

    return 0;
}


// [1,2,3,], [4,5,6], [7,8,9]