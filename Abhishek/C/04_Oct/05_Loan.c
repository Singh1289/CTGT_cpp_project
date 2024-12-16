/*
    Program to generate a re-payment schedule for a loan. The user should provide 
    the loan amount, annual interest rate, and the number of years to repay. 
    The program should output the monthly payment and a detailed schedule showing 
    payments over time.
*/
#include <stdio.h>
#include <math.h>

// for taking inputs 
void takingInputs(int *months, int *principal, float *rate) {
    printf("\nEnter loan Amount: ");
    scanf("%d", principal);  
    printf("\nEnter time in months: ");
    scanf("%d", months);
    printf("\nEnter annual interest rate (ROI): ");
    scanf("%f", rate);
} 

int main() {
    // vaiables declration
    int months;
    int principal;
    float annualRate, monthlyRate, temp;
    float EMI;
    
    // taking inputs
    takingInputs(&months, &principal, &annualRate);
    
    // calculating monthly rate
    monthlyRate = annualRate / 1200;

    // calculation of EMI
    temp = pow(1 + monthlyRate, months);
    EMI = (principal * monthlyRate * temp) / (temp - 1);

    // printing EMI schedule
    printf("\nMonthly EMI: %.2f\n", EMI);
    printf("\nPayment Schedule:\n");
    printf("--------------------------\n");
    printf("Month\tPayment\n");
    printf("--------------------------\n");
    
    for (int i = 1; i <= months; i++) {
        printf("%-6d\t%.2f\n", i, EMI); 
    }

    return 0;
}
