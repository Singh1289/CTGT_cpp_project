#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int pass_count ;
extern int fail_count;
extern int test_count;

#define ASSERT_EQUALS(expected, actual) \
    do { \
        test_count++; \
        if ((expected) != (actual)) { \
            fprintf(stderr, "Assertion failed: %s == %s\n", #expected, #actual); \
            fail_count++; \
        } else { \
            pass_count++; \
        } \
    } while (0)

#define ASSERT_ARRAY_EQUALS(expected, actual, n) \
    do { \
        test_count++; \
        int test_passed = 1; \
        for (int i = 0; i < n; i++) { \
            if ((expected)[i] != (actual)[i]) { \
                fprintf(stderr, "Assertion failed at index %d: expected %d, got %d\n", i, (expected)[i], (actual)[i]); \
                fail_count++; \
                test_passed = 0;\
                break;  \
            } \
        } \
        if (test_passed) { \
            pass_count++; \
        } \
    } while (0)


#define ASSERT_STRING_EQUALS(expected, actual) \
    do { \
        test_count++; \
        if (strcmp((expected), (actual)) != 0) { \
            fprintf(stderr, "Assertion failed: expected \"%s\", got \"%s\"\n", (expected), (actual)); \
            fail_count++; \
        } else { \
            pass_count++; \
        } \
    } while (0)

static void print_test_summary() {
    printf("\nTest Summary:\n");
    printf("Total Tests: %d  ", test_count);
    printf("Passed: %d  ", pass_count);
    printf("Failed: %d\n", fail_count);
}

#define TEST_CASE(name) \
    void name(void)

#define RUN_TEST(name) \
    do { \
        printf("Running test: %s\n", #name); \
        name(); \
    } while (0)

void mergeSort(int arr[], int left, int right);
int factorial(int n);
void reverseString(char str[]);
void capitalizeString(char str[]);

#endif
