#include <iostream>
using namespace std;
int fact(int a){
    if (a==1) return a;

    return a * fact(a-1);
}

// sum 
int sum(int a){
    if (a==1) return a;

    return a + sum(a-1);
}

// count of digits
int count(int a){
    if (a==0) return 0;
    return 1 + count(a/10);
}

// sum of digits
int sumOfDigits(int a){
    if (a==0) return 0;
    return a%10 + sumOfDigits(a/10);
}

// reverse a number
int reverse(int a){
    if (a==0) return 0;
    int n = a%10;
    return n*10 + reverse(a/10);
}


int main(){
    int a;
    cout<<"Enter a number: ";
    cin>>a;
    // cout<< "factorial of num "<<a<<" is "<<fact(a)<<endl;
    // cout<< "sum of num "<<a<<" is "<<sum(a)<<endl;

    cout<< "count of digits in num "<<a<<" is "<<count(a)<<endl;
    cout<< "sum of digits in num "<<a<<" is "<<sumOfDigits(a)<<endl;
    cout<< "reverse of num "<<a<<" is "<<reverse(a)<<endl;


    return 0;
}