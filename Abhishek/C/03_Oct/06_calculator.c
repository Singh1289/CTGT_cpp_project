#include <stdio.h>

// Function declaration
float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);
void showMenu();

// Function pointer type
typedef float (*operationFunc)(float, float);

int main() {
    int choice;
    float num1, num2;
    
    // Array of function pointers
    operationFunc operations[4] = {add, subtract, multiply, divide};
    const char *operationNames[] = {"Addition", "Subtraction", "Multiplication", "Division"};

    do {
        showMenu();
        printf("\nEnter your choice (1-4, 0 to exit): ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            printf("\nEnter two numbers: ");
            scanf("%f %f", &num1, &num2);

            // Finction call- the selected operation using the function pointer
            float result = operations[choice - 1](num1, num2);
            printf("\nResult of %s: %.2f", operationNames[choice - 1], result);
        } else if (choice != 0) {
            printf("\nInvalid choice. Please try again.");
        }
    } while (choice != 0);

    printf("\n~~~ See You Soon ~~~");
    return 0;
}

// Function to display the menu
void showMenu() {
    printf("\n~~~ Basic Calculator ~~~");
    printf("\n1. Addition");
    printf("\n2. Subtraction");
    printf("\n3. Multiplication");
    printf("\n4. Division");
    printf("\n0. Exit");
}

// Function definitions
float add(float a, float b) {
    return a + b;
}

float subtract(float a, float b) {
    return a - b;
}

float multiply(float a, float b) {
    return a * b;
}

float divide(float a, float b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("\nError: Division by zero!");
        return 0; 
    }
}
