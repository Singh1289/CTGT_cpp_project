

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <climits>
using namespace std;

long MINDIFF = INT_MAX;

void trimString(string &str)
{
    int start = 0, end = str.length() - 1;
    while (start < end && (str[start] ==' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r'))
        start++;
    while (start < end && (str[end] ==' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r'))
        end--;
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
 
    size_t start = str.find('{');
    size_t end = str.find('}');
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

// void partitionHelper(vector<long> &nums, long tempSum, long targetSum, vector<long> &subset1, vector<long> &subset2, vector<pair<vector<long>, vector<long>>> &res){
//     if(tempSum == targetSum){
//         res.push_back({subset1, subset2});
//         return;
//     }
    
//     if(tempSum > targetSum || subset1.size() + subset2.size() >= nums.size()){
//         return;
//     }
    
   
//         subset1.push_back(nums[i]);
//         partitionHelper(nums, tempSum + nums[i], targetSum, subset1, subset2, res);
//         subset1.pop_back();
        
//         subset2.push_back(nums[i]);
//         partitionHelper(nums, tempSum, targetSum, subset1, subset2, res);
//         subset2.pop_back();
    
// }


void partitionHelper(vector<long>& nums, int index, vector<long>& subset1, vector<long>& subset2, 
                     int sum1, int sum2, vector<pair<vector<long>, vector<long>>>& result) {
  
    if (index == nums.size()) {
        int diff = abs(sum1 - sum2);
        if (diff < MINDIFF) {
           
            MINDIFF = diff;
            result.clear();
            result.push_back({subset1, subset2});
        } else if (diff == MINDIFF) {
            
            result.push_back({subset1, subset2});
        }
        return;
    }

   
    subset1.push_back(nums[index]);
    partitionHelper(nums, index, subset1, subset2, sum1 + nums[index], sum2, result);
    subset1.pop_back();

 
    subset2.push_back(nums[index]);
    partitionHelper(nums, index + 1, subset1, subset2, sum1, sum2 + nums[index], result);
    subset2.pop_back();
}

vector<pair<vector<long>, vector<long>>> getPartitions(vector<long> &nums, long sum)
{
    vector<pair<vector<long>, vector<long>>> res;
    
    long tempSum = 0;
    vector<long> subset1, subset2;
    partitionHelper(nums, 0, subset1, subset2, tempSum, 0, res);
    return res;
}


void printResultSet(vector<pair<vector<long>, vector<long>>>&res){
    int m =0;
    for(auto& p : res){
        m=0;
        cout<<"S1 = {";
        for(auto& i : p.first)
           { cout<<i;
            if(m< p.first.size()-1) cout<<", ";
           }
        cout<<"}, S2 = {";
        m = 0;
        for(auto& i : p.second)
            {cout<<i<<" ";
             if(m< p.second.size()-1) cout<<", ";
            }
        cout<<"}"<<"min Diff : "<<MINDIFF<<endl;
    }
}




int main(){
    string input;
    cout<<"Input: ";
    getline(cin, input);
    trimString(input);
    if(input.size()==0){
        cout<<"Error: Invalid input"<<endl;
        return 0;
    }
    vector<long> nums;
    int idx = 0;

    convertIntoArray(nums, input, idx);
    if (idx==0){
        cout<<"Error: Invalid input"<<endl;
        return 0;
    }

    // print array {10, 20, 15, 5, 25}
    for(auto i : nums)
        cout<<i<<" ";
    
    cout<<endl;

    long sum = 0;
    for(int i=0; i<nums.size(); i++){
        sum += nums[i];
    }
    cout<<"Sum: "<<sum<<endl;
    

    // vector<pair<vector<long>, vector<long>>> res = getPartitions(nums,sum);
    // printResultSet(res);

    vector<pair<long,vector<long>>> res;
    res.push_back({0, vector<long>()});

    for(int i=0; i<nums.size(); i++)
    {
        int n = res.size();
        for(int j =0; j<n; j++){
            vector<long> internal(res[j].second);
            internal.push_back(i);
            //res[j].first += nums[i];
            long num = res[j].first + nums[i];
            res.push_back({num,internal});        
        }
    }
    

    int target = 0;
    for(auto& i : res){
        long diff = sum - i.first;
        if(i.second.size() == 0)continue;
        else
        if(abs(diff - i.first) < MINDIFF && i.second.size()!= nums.size()-1){ MINDIFF = diff - i.first;
            target = i.first;
        }
    }

    cout<<"Target Sum: "<<target<<" MinDiff: "<<MINDIFF<<endl;

    
    for(auto& i : res){
        if(i.first == target){
        cout<<"{ "<< MINDIFF<<"} \nS1 = [";
        for(auto& j : i.second)
            cout<<nums[j]<<" ";
        cout<<"]"<<endl;
        cout<<"S2 = [";
        for(int k = 0,l=0; k < nums.size(); k++){
            if(k== i.second[l])
                l++; 
            else
                cout<<nums[k]<<" ";
        }
        cout<<"]"<<endl;
    
    }}

    return 0;
}