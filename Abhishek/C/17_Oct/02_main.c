// main.c
#include "02_test_framework.h"

// Declare test functions with parameters
extern void test_mergeSort(int arr[], int expected[], int n);
extern void test_factorial(int input, int expected);
extern void test_reverseString(char input[], const char *expected);
extern void test_capitalizeString(char str[], const char *expected);



int main(void) {
    // Test mergeSort
    int arr1[] = {5, 3, 8, 6, 2, 7, 4, 1};
    int sortedArr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    test_mergeSort(arr1, sortedArr1, 8);

    // Test factorial
    test_factorial(5, 120);
    test_factorial(3, 6);
    test_factorial(4, 25);

    // Test reverseString
    char str1[] = "hello";
    char str2[] = "world";
    test_reverseString(str1, "olleh");
    test_reverseString(str2, "dlrow");

    // Test capitalizeString
    char str3[] = "Abhishek Pratap Singh";
    char str4[] = "ABHISHEK PRATAP SINGH";
    test_capitalizeString(str3, str4);

    print_test_summary();     

    return 0;
}
