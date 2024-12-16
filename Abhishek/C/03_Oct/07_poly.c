/*
    Program to Evaluate a Given Polynomial Equation
*/

#include<stdio.h>
#include<math.h>

// evaluate the equation 
double evaluateEquation(double *co, int degree, double x) {
    double result = 0.0;

    for (int i = 0; i <= degree; i++) {
        result += co[i] * pow(x, degree - i);
    }

    return result;
}


void main()
{
    // declaring variables
    int degree;
    printf("\nHighest power : ");
    scanf("%d",&degree);

    // Coefficients array
   double coefficients[degree + 1]; 

   printf("Enter the coefficients (from highest power to lowest):");
    for (int i = degree; i >= 0; i--) {
        printf("\nCoefficient of x^%d: ", i);
        scanf("%lf", &coefficients[i]);
    }
    //taking value of x
    double x;

    printf("Enter the value of x: ");
    scanf("%lf", &x);

    // evaluating the equation
    double result = evaluateEquation(coefficients, degree, x);
    printf("\nThe polynomial evaluates: %.3lf", result);


}