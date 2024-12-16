#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Forward declarations
class Department;
class Employee;
class Role;
class LeaveTransaction;

// Enum for EmployeeType (flexible)
class EmployeeType {
private:
    vector<string> types;

public:
    void addType(string typeName) {
        types.push_back(typeName);
    }

    void removeType(string typeName) {
        types.erase(remove(types.begin(), types.end(), typeName), types.end());
    }

    vector<string> getAllTypes() {
        return types;
    }

    void viewTypes() {
        for (const string &type : types) {
            cout << type << endl;
        }
    }
};

// Department class
class Department {
public:
    int Dept_ID;
    string name;

    string getName() {
        return name;
    }

    int getDept_ID() {
        return Dept_ID;
    }
};

// Role class
class Role {
public:
    int id;
    string name;

    static vector<Role> getAllRoles() {
        // Placeholder: return all roles
        return {};
    }
};

// Employee class
class Employee {
public:
    int e_id;
    string userName;
    string name;
    string email;
    Role role;
    string password;
    string address;
    string alternateEmail;
    long alternateContactNumber;
    string emergencyContactName;
    long emergencyContactNumber;
    string nomineeName;
    int nomineeShare;
    bool isActive;

    EmployeeType employeeType;
    Department *department;

    void viewDetails() {
        cout << "Employee ID: " << e_id << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
    }

    void updateNomineeName(string newNomineeName) {
        nomineeName = newNomineeName;
    }

    void updateAddress(string newAddress) {
        address = newAddress;
    }
};

// Manager class
class Manager : public Role {
public:
    void assignRole(Employee &employee, Role newRole) {
        employee.role = newRole;
    }
};

// HR_Manager class
class HR_Manager : public Role {
public:
    void addEmployee(vector<Employee> &employees, Employee newEmployee) {
        employees.push_back(newEmployee);
    }

    void viewAllEmployees(const vector<Employee> &employees) {
        for (const auto &employee : employees) {
            employee.viewDetails();
        }
    }

    void generateSalarySlip(Employee &employee) {
        cout << "Salary slip generated for Employee ID: " << employee.e_id << endl;
    }
};

// LeaveTransaction class
class LeaveTransaction {
public:
    int id;
    int employeeId;
    string leaveType;
    int days;
    string status;

    void logLeaveRequest() {
        cout << "Leave request logged for Employee ID: " << employeeId << endl;
    }
};

// Main function
int main() {
   
    EmployeeType empType;
    empType.addType("Onpayroll");
    empType.addType("OnContractPay");

    Department devDept;
    devDept.Dept_ID = 1;
    devDept.name = "Development";

    Employee emp;
    emp.e_id = 101;
    emp.name = "John Doe";
    emp.email = "john.doe@example.com";
    emp.department = &devDept;
    emp.employeeType = empType;

    HR_Manager hr;
    vector<Employee> employees;
    hr.addEmployee(employees, emp);
    hr.viewAllEmployees(employees);

    LeaveTransaction leave;
    leave.employeeId = emp.e_id;
    leave.leaveType = "Sick Leave";
    leave.days = 2;
    leave.logLeaveRequest();

    return 0;
}
