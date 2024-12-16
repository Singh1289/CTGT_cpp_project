// 1. Program to manage a list of employees for a company where each employee record includes personal details,
// job information, and payroll data. Use structs to manage employee records.
// Include fields for personal information (name, ID, address), job details (position, department), and compensation.
//  Define a union to handle different types of compensation, such as hourly wages, salaries, or commission-based pay.
//   Allow adding, updating, and querying and filtering employee records on various criteria, and handle compensation
//   calculations based on the type of compensation.
// Include functionality for generating payroll reports, department-wise breakdowns, and employee lists.

#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 200

typedef enum { HOURLY, DAILY, COMMISSION } PayType;

typedef struct {
    float hourly_rate;
    int hours_worked;
} HourlyPay;

typedef struct {
    float daily_rate;
    int days_worked;
} DailyPay;

typedef struct {
    float commission_rate;
    float sales_amount;
} CommissionPay;

typedef union {
    HourlyPay hourly;
    DailyPay daily;
    CommissionPay commission;
} Payroll;

typedef struct {
    char name[25];
    int id;
    char address[50];
    char department[25];
    PayType pay_type;
    Payroll payroll;
} Employee;

Employee employees[MAX_EMPLOYEES];
int employee_count = 0;

void add_employee() {
    if (employee_count >= MAX_EMPLOYEES) {
        printf("Employee limit reached.\n");
        return;
    }

    Employee *e = &employees[employee_count];
    printf("Enter employee name: ");
    fgets(e->name, sizeof(e->name), stdin);
    e->name[strcspn(e->name, "\n")] = 0;  

    e->id = employee_count + 1;  
    printf("Enter employee address: ");
    fgets(e->address, sizeof(e->address), stdin);
    e->address[strcspn(e->address, "\n")] = 0;

    printf("Enter department: ");
    fgets(e->department, sizeof(e->department), stdin);
    e->department[strcspn(e->department, "\n")] = 0;

    printf("Select pay type (0: Hourly, 1: Daily, 2: Commission): ");
    int pay_choice;
    scanf("%d", &pay_choice);
    getchar(); 
    e->pay_type = pay_choice;

    switch (e->pay_type) {
        case HOURLY:
            printf("Enter hourly rate: ");
            scanf("%f", &e->payroll.hourly.hourly_rate);
            printf("Enter hours worked: ");
            scanf("%d", &e->payroll.hourly.hours_worked);
            break;
        case DAILY:
            printf("Enter daily rate: ");
            scanf("%f", &e->payroll.daily.daily_rate);
            printf("Enter days worked: ");
            scanf("%d", &e->payroll.daily.days_worked);
            break;
        case COMMISSION:
            printf("Enter commission rate: ");
            scanf("%f", &e->payroll.commission.commission_rate);
            printf("Enter total sales amount: ");
            scanf("%f", &e->payroll.commission.sales_amount);
            break;
    }

    employee_count++;
    printf("Employee added successfully!\n");
}

void display_employees() {
    for (int i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        printf("ID: %d, Name: %s, Address: %s, Department: %s\n",
               e->id, e->name, e->address, e->department);
    }
}

void payroll_reports() {
    for (int i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        float salary = 0;

        switch (e->pay_type) {
            case HOURLY:
                salary = e->payroll.hourly.hourly_rate * e->payroll.hourly.hours_worked;
                break;
            case DAILY:
                salary = e->payroll.daily.daily_rate * e->payroll.daily.days_worked;
                break;
            case COMMISSION:
                salary = e->payroll.commission.commission_rate * e->payroll.commission.sales_amount;
                break;
        }
        printf("ID: %d, Name: %s, Salary: %.2f\n", e->id, e->name, salary);
    }
}

void display_department_wise() {
    char department[25];
    printf("Enter department name to display: ");
    fgets(department, sizeof(department), stdin);
    department[strcspn(department, "\n")] = 0;  

    printf("Employees in Department: %s\n", department);
    for (int i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        if (strcmp(e->department, department) == 0) {
            printf("ID: %d, Name: %s\n  ", e->id,e->name);
        }
    }
}

int menu() {
    int choice;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n|           ~ W E L C O M E ~         |");
    printf("\n|1 : Add Employee                     |");
    printf("\n|2 : Display Employees                |");
    printf("\n|3 : Payroll Reports                  |");
    printf("\n|4 : Display Employees by Department  |");
    printf("\n|0 : Exit                             |");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\nWhat would you like to do: ");
    scanf("%d", &choice);
    getchar(); 
    return choice;
}

int main() {
    int choice;
    while ((choice = menu()) != 0) {
        switch (choice) {
            case 1:
                add_employee();
                break;
            case 2:
                display_employees();
                break;
            case 3:
                payroll_reports();
                break;
            case 4:
                display_department_wise();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
