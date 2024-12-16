#include <iostream>
#include <vector>
using namespace std;

#define Array vector<vector<int>>

void generateSubsets(vector<int>& arr, int index, vector<int>& current, Array& res) {
    
    if (index == arr.size()) {
        res.push_back(current);
        return;
    }

    
    generateSubsets(arr, index + 1, current, res);
  
    current.push_back(arr[index]);
    generateSubsets(arr, index + 1, current, res);
    current.pop_back();
}

int main() {
    vector<int> arr = {1, 2, 3}; 

    Array res; 
    vector<int> current; 

    
    generateSubsets(arr, 0, current, res);

    // Print result
    for (int i = 0; i < res.size(); i++) {
        cout << "[";
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
