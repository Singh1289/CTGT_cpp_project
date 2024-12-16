/*
// nth number of fibonacci series
#include <iostream>
using namespace std;

int fib(int n){
    if (n<2)
    return n;
    
    return fib(n-1) + fib(n-2);
}

int main(){
    
    int res = fib(8);
    cout<<"res: "<<res<<endl;
    
    return 0;
}
*/

// fibonacci series function by recursion
#include <iostream>
using namespace std;

void fibonacciSeries(int n) {
    int a = 0, b = 1, c;

   cout<<"Fibonacci series: "<<a<<" "<<b<<" ";

    for (int i = 2; i < n; i++) {
        c = a + b;
        a = b;
        b = c;
        cout<<c<<" ";
    }
}

int fibonacci(int n) {
                                //  base case -> body -> recursion call
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

void printFibonacciSeries(int n) {
    for (int i = 1; i <= n; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of terms: ";
    cin >> n;

    cout << "Fibonacci Series: ";
    printFibonacciSeries(n);

    fibonacciSeries(n);

    return 0;
}




