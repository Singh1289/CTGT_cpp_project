// test_cases.c
#include "02_test_framework.h"


void test_mergeSort(int arr[], int expected[], int n) {
    mergeSort(arr, 0, n - 1);
    ASSERT_ARRAY_EQUALS(expected, arr, n);
}

void test_factorial(int input, int expected) {
    ASSERT_EQUALS(expected, factorial(input));
}

void test_reverseString(char input[], const char *expected) {
    reverseString(input);
    ASSERT_STRING_EQUALS(expected, input);
}

void test_capitalizeString(char str[], const char *expected) {
    capitalizeString(str);
    ASSERT_STRING_EQUALS(expected, str);
}

