#include<iostream>
#include<string>
#include <vector>
#include <memory>
#include <iomanip>
using namespace std;

// Abstract Employee class
class Employee {
protected:
    string name;
    int id;
public:
    Employee(string name, int id) : name(name), id(id) {}

    // Pure virtual function for calculating salary
    virtual double calculateSalary() const = 0;

    // Function to display common employee details
    virtual void display() const {
        cout << "Name: " << name << ", ID: " << id;
    }
    
    virtual ~Employee() {}  // Virtual destructor
};

// Full-time employee class
class FullTimeEmployee : public Employee {
private:
    double annualSalary;
public:
    FullTimeEmployee(string name, int id, double salary) 
        : Employee(name, id), annualSalary(salary) {}

    double calculateSalary() const override {
        return annualSalary / 12; // Monthly salary
    }

    void display() const override {
        cout << left << setw(20) << name 
             << setw(10) << id 
             << setw(20) << calculateSalary() << endl;
    }
};

// Part-time employee class
class PartTimeEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;
public:
    PartTimeEmployee(string name, int id, double rate, int hours)
        : Employee(name, id), hourlyRate(rate), hoursWorked(hours) {}

    double calculateSalary() const override {
         // Total salary
        return hourlyRate * hoursWorked; 
    }

    void display() const override {
        cout << left << setw(20) << name 
             << setw(10) << id 
             << setw(20) << hourlyRate 
             << setw(20) << calculateSalary() << endl;
    }
};

// Intern class
class Intern : public Employee {
private:
    double stipend;
public:
    Intern(string name, int id, double stipendAmount)
        : Employee(name, id), stipend(stipendAmount) {}

    double calculateSalary() const override {
        // Monthly stipend
        return stipend;  
    }

    void display() const override {
        cout << left << setw(20) << name 
             << setw(10) << id 
             << setw(20) << stipend << endl;
    }
};

// Department class to manage employees
class Department {
private:
    // List of employees
    vector<shared_ptr<Employee>> employees;  

public:
    // Add an employee to the department
    void addEmployee(shared_ptr<Employee> employee) {
        employees.push_back(employee);
    }

    // Calculate total salary of all employees
    double calculateTotalSalary() const {
        double totalSalary = 0;
        for (const auto& employee : employees) {
            totalSalary += employee->calculateSalary();
        }
        return totalSalary;
    }

    // Generate report for employees
    void generateReport() const {
        vector<shared_ptr<Employee>> fullTimeEmployees;
        vector<shared_ptr<Employee>> partTimeEmployees;
        vector<shared_ptr<Employee>> interns;

        // Categorize employees into Full-Time, Part-Time, and Interns
        for (const auto& employee : employees) {
            if (dynamic_cast<FullTimeEmployee*>(employee.get())) {
                fullTimeEmployees.push_back(employee);
            } else if (dynamic_cast<PartTimeEmployee*>(employee.get())) {
                partTimeEmployees.push_back(employee);
            } else if (dynamic_cast<Intern*>(employee.get())) {
                interns.push_back(employee);
            }
        }

        // Display Full-Time Employees
        cout << "\n---------------------------- Full-Time Employees ----------------------------\n";
        cout << left << setw(20) << "Name" 
             << setw(10) << "ID" 
             << setw(20) << "Monthly Salary" << endl;
        cout << "-------------------------------------------------------------------------\n";
        for (const auto& employee : fullTimeEmployees) {
            employee->display(); 
        }

        // Display Part-Time Employees
        cout << "\n---------------------------- Part-Time Employees ---------------------------\n";
        cout << left << setw(20) << "Name" 
             << setw(10) << "ID" 
             << setw(20) << "Hourly Rate" 
             << setw(20) << "Monthly Salary" << endl;
        cout << "-------------------------------------------------------------------------\n";
        for (const auto& employee : partTimeEmployees) {
            employee->display();  
        }

        // Display Interns
        cout << "\n---------------------------- Interns ----------------------------\n";
        cout << left << setw(20) << "Name" 
             << setw(10) << "ID" 
             << setw(20) << "Monthly Stipend" << endl;
        cout << "-------------------------------------------------------------------------\n";
        for (const auto& employee : interns) {
            employee->display(); 
        }

        cout << endl;
    }
};

// Display menu options for the user
void displayMenu() {
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << "\n|      Employee Management      |";
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << "\n|1 : Add Full-Time Employee     |";
    cout << "\n|2 : Add Part-Time Employee     |";
    cout << "\n|3 : Add Intern                 |";
    cout << "\n|4 : Calculate Total Salary     |";
    cout << "\n|5 : Generate Employee Report   |";
    cout << "\n|6 : Exit                       |";
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

int main() {
    Department dept;  // Create department instance
    int choice;

    // Display menu and handle user input
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        string name;
        int id;
        double salary;
        int hours;
        double rate;

        switch (choice) {
            case 1:  // Add Full-Time Employee
                cout << "Enter Full-Time Employee Name: ";
                getline(cin, name);
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Annual Salary: ";
                cin >> salary;
                dept.addEmployee(make_shared<FullTimeEmployee>(name, id, salary));
                break;

            case 2:  // Add Part-Time Employee
                cout << "Enter Part-Time Employee Name: ";
                getline(cin, name);
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Hourly Rate: ";
                cin >> rate;
                cout << "Enter Hours Worked: ";
                cin >> hours;
                dept.addEmployee(make_shared<PartTimeEmployee>(name, id, rate, hours));
                break;

            case 3:  // Add Intern
                cout << "Enter Intern Name: ";
                getline(cin, name);
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Monthly Stipend: ";
                cin >> salary;
                dept.addEmployee(make_shared<Intern>(name, id, salary));
                break;

            case 4:  // Calculate Total Salary
                cout << "Total Salary: " << dept.calculateTotalSalary() << endl;
                break;

            case 5:  // Generate Employee Report
                dept.generateReport();
                break;

            case 6:  // Exit
                cout << "~~~~ See You Soon ~~~~\n";
                break;

            default:  // Invalid choice
                cout << "Invalid choice, please try again.\n";
                break;
        }
    } while (choice != 6); 

    return 0;
}
