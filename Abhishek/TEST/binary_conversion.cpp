#include<queue>
#include<vector>
#include<bitset>
#include<limits>
#include <iostream>
using namespace std;
// 2147483647

string toBinary(int num) {
    /* if (num < 0) {
        return bitset<32>(num).to_string();
    }
    return bitset<32>(num).to_string();
*/
   
     string res = "";
    bool isNegative = false;
    if (num < 0) {
        // num = ~num | 1;
        num = ~num;
        // num = num ^ num;
        isNegative = true;
    }
    while (num > 0) {
        res = to_string(num % 2) + res; 
        num /= 2; 
    }
    if(res.length() < 32 ) {
        if(isNegative){
            for(int i =0 ;i<res.length();i++)
                if(res[i]=='1') res[i]='0';else res[i]='1'; 
        
        res = string(32 - res.length(), '1') + res;
            
        }
        else
        res = string(32 - res.length(), '0') + res;
    }
    return res;
    
}

int main()
{
    int a = -500000000;
    int b = 500000000;
    int c = 100000000;
    int d = -100000000;
    cout<< ~a<<endl;;
    cout<< (2147483647 > 500000000)<<endl;
    //string binary = "00000000000000000000000000001001";
    // string binary = "11111111111111111111111111111001";
    // cout <<~(stoul(binary, nullptr, 2))<<endl;
    
    cout<<"bits: "<<a<<" "<<bitset<32>(a).to_string()<<" "<<bitset<32>(a).count()<<" "<<bitset<64>(a).count()<<endl;
    cout<<"bits: "<<toBinary(a)<<endl;
    cout<<"bits: "<<b<<" "<<bitset<32>(b).to_string()<<" "<<bitset<32>(b).count()<<" "<<bitset<64>(b).count()<<endl;
    cout<<"bits: "<<toBinary(b)<<endl;
    cout<<"bits: "<<c<<" "<<bitset<32>(c).to_string()<<" "<<bitset<32>(c).count()<<" "<<bitset<64>(c).count()<<endl;
    cout<<"bits: "<<toBinary(c)<<endl;
    cout<<"bits: "<<d<<" "<<bitset<32>(d).to_string()<<" "<<bitset<32>(d).count()<<" "<<bitset<64>(d).count()<<endl;
    cout<<"bits: "<<toBinary(d)<<endl;
    
 
    return 0;
}