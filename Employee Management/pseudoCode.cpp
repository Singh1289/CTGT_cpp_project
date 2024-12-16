#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Global variables
int Role_ID = 11;
int EMP_ID = 4010;
int DEPT_ID = 1101;
int LEAVE_ID = 101;
int PROJECT_ID = 101;

// Forward declarations of classes
class Department;
class Employee;
class Role;
class Project;
class Manager;
class HR_Manager;
class CEO;
class EmployeeType;

class Company
{
public:
    string name;
    string address;
    vector<Department> departments;

    void addDepartment()
    {
        // Pseudocode: Create a new department
        // Start of pseudocode
        // Department department;
        // add to departments vector
        // End of pseudocode
    }
    void removeDepartment(Department &department)
    {
        // Pseudocode: Remove a department from the company
        // Start of pseudocode
        // for loop
        //    if department == given department
        //        departments.isActive = false
        //        break;
        //    end if
        // end for
        // End of pseudocode
    }
    void viewDepartments()
    {
        // Pseudocode: Print all departments in the company
        // Start of pseudocode
        // for loop
        //    if department.isActive
        //        print department.getName()
        //    end if
        // end for
        // End of pseudocode
    }
};

class Department
{
public:
    int deptID;
    bool isActive;
    string name;
    Department(string name) : name(name), isActive(true)
    {
        // deptID = ++Role_ID;
    }

    string getName()
    {
        return name;
    }

    int getDept_ID()
    {
        return deptID;
    }
};

class HRDepartment : public Department
{
public:
};

class Development : public Department
{
public:
};

class Emp_dept
{
public:
    int empID;
    int deptID;
    // Constructor
    Emp_dept(int empID, int deptID)
    {
        // Pseudocode: assign depart to employee
    }
    Emp_dept(int empID)
    {
        // Pseudocode: assign department to employee
        // Start of pseudocode
        // this.empID = empID;
        // End of pseudocode
    }
    void assignDepartment(int deptID)
    {
        // Pseudocode: Assign department to employee
        // Start of pseudocode
        // this.deptID = deptID;
        // End of pseudocode
    }
};

class Role
{
public:
    int id;
    string name;
    bool isActive;
    vector<Role> roles;

    Role(string name)
    {
        // Pseudocode: Initialize role with name
        // Start of pseudocode
        // id = Role_ID++;
        // isActive = true;
        // this.name = name;
        // End of pseudocode
    }

    void addRole(string roleName)
    {
        // Pseudocode: Add a new role to the current role
        // Start of pseudocode
        // Role newRole;
        // newRole.name = roleName;
        // roles.push_back(newRole);
        // End of pseudocode
    }
    void removeRole(int roleID)
    {
        // Pseudocode: Remove a role from the current role
        // Start of pseudocode
        // for loop
        //    if match role.id to roleID
        //        isActive = false
        //      break;
        //    end if
        // end for
        // End of pseudocode
    }
    void assignRoleToEmployee(Employee &id, string role)
    {
        // Pseudocode: Assign a role to an employee
        // Start of pseudocode
        // emp.role = this;
        // End of pseudocode
    }
    vector<Role> getAllRoles()
    {
        // Pseudocode: Return all roles in the current role
        // Start of pseudocode
        // for loop
        //    roles.push_back(role);
        //    break;
        // end for
        // return roles
        // End of pseudocode
    }
};

class Manager : public Role
{
    vector<LeaveTransaction> leavesRequests;

public:
    void showPendingApproval()
    {
        // Pseudocode: Approve or reject leave requests of employees under this manager
        // Start of pseudocode
        // if size of vector is greater than zero then
        // for loop
        //    print leave requests -> viewLeaveRequest
        //    ask to approve or reject
        //    if approve
        //        update leave status
        //    else
        //        reject leave request
        //      break;
        //    end if
        // end for
        // End of pseudocode
    }
};

class HR_Manager : public Role
{
public:
    void approveAndRejectLeave()
    {
        // Pseudocode: Approve or reject leave requests of employees under this manager
        // Start of pseudocode
        // if size of vector is greater than zero then
        // for loop
        //    print leave requests -> viewLeaveRequest
        //    ask to approve or reject
        //    if approve
        //        update leave status
        //    else
        //        reject leave request
        //      break;
        //    end if
        // end for
        // End of pseudocode
    }

    void addEmployee(Employee &emp)
    {
        // Pseudocode: Add an employee to the manager's team
        // Start of pseudocode
        // emp.adddepartment()
        // emp.role()
        // emp.leaveEntilement()
        // open file in binary mode
        // write the object into the file
        // close file
        // End of pseudocode
    }

    void deactivateEmployee(Employee &emp)
    {
        // Pseudocode: Deactivate an employee from the manager's team
        // Start of pseudocode
        // emp.isActive= false;
        // End of pseudocode
    }
    void viewEmployee(Employee &emp)
    {
        // Pseudocode: View an employee's details
        // Start of pseudocode
        //  printing all details
        //   print emp.name
        //   print emp.role.name
        //   print emp.isActive
        // End of pseudocode
    }
   
     void addAllowance_wrapper(Employee& emp, string allowancesName, int amt)
    {
        // Pseudocode: add allowances of an employee
        // Start of pseudocode
        // emp.salaryStructure.addAllowances(allowanceName, amt);
        // End of pseudocode
    }

    void viewAllEmployees()
    {
        // Pseudocode: List all employees in the department
        // Start of pseudocode
        // for loop
        //    print emp.name
        //    print emp.role.name
        //    print emp.isActive
        // end for
        // End of pseudocode
    }

    void viewAllActiveEmployees()
    {
        // Pseudocode: List all active employees in the department
        // Start of pseudocode
        // for loop
        //    if emp.isActive
        //        print emp.name
        //        print emp.role.name
        //        print emp.isActive
        //    end if
        // end for
        // End of pseudocode
    }

    void viewAllInactiveEmployees()
    {
        // Pseudocode: List all inactive employees in the department
        // Start of pseudocode
        // for loop
        //    if not emp.isActive
        //        print emp.name
        //        print emp.role.name
        //        print emp.isActive
        //    end if
        // end for
        // End of pseudocode
    }

    Employee searchByEmployeeByID()
    {
        // Pseudocode: Search for an employee by ID
        // Start of pseudocode
        // for loop
        //    if match employee.id to ID
        //        return employee
        //      break;
        //    end if
        // end for
        // return null
        // End of pseudocode
    }


    void addEmployeeType()
    {
        // Pseudocode: Add new employee type
        // Start of pseudocode
        //  create new EmployeeType
        // End of pseudocode
    }

    void removeEmployeeType()
    {
        // Pseudocode: Remove an employee type
        // Start of pseudocode
        //  remove employee type
        // End of pseudocode
    }

    void generateSalarySlip(Employee &emp)
    {
        // Pseudocode: Generate salary slip for an employee
        // Start of pseudocode
        //  calculate salary
        //  print salary slip
        // End of pseudocode
    }

   
    void addType_wapper(string type){
        // Pseudocode: Add new employee type
        // Start of pseudocode
        // this.EmployeeType.addType(type);
        // End of pseudocode
    }

    void removeType_wrapper(string type){
        // Pseudocode: Remove an employee type
        // Start of pseudocode
        // this.EmployeeType.removeType(type);
        // End of pseudocode
    }

};

class CEO : public Manager
{
public:
   
    void assignProject(Employee &emp, Project &project)
    {
        // Pseudocode: Assign a project to an employee
        // Start of pseudocode
        // emp.role = this;
        // project.assignedTo = emp;
        // End of pseudocode
    }
    void assignTask(Employee &emp, Task &task)
    {
        // Pseudocode: Assign a task to an employee
        // Start of pseudocode
        // project.taskList.push_back(task);
        // assigning to the employee
        // emp.taskArray.push_back(task);
        // End of pseudocode
    }
};

class Project
{
    int projectID;
    string name;
    string description;
    string startDate;
    string endDate;
    int budget;
    string status;
    vector<Task> taskList;
    bool isCompleted;

public:
    // constructor
    Project(string name, string description, string startDate, string endDate, int budget)
    {
        // Pseudocode: Initialize project with details
        // Start of pseudocode
        // projectID = Project_ID++;
        // this.name = name;
        // this.description = description;
        // this.startDate = startDate;
        // this.endDate = endDate;
        // this.budget = budget;
        // this.status = "Not Started";
        // this.isCompleted = false;
        // End of pseudocode
    }

    void createProject()
    {
        // Pseudocode: Create a new project
        // Start of pseudocode
        //  project.status = "In Progress"
        // End of pseudocode
    }
    void updateProject()
    {
        // Pseudocode: Update project details
        // Start of pseudocode
        //  project.status = "In Progress"
        // End of pseudocode
    }
    void viewProjectDetails()
    {
        // Pseudocode: View project details
        // Start of pseudocode
        //  print details
        // End of pseudocode
    }
};

class Task
{
    int taskID;
    string taskName;
    string description;
    string status;
    string priority;
    string dependency;
    vector<Employee> employees;
    bool isCompleted;

public:
    // constructor
    Task(string taskName, string description, string priority, string dependency)
    {
        // Pseudocode: Initialize task with details
        // Start of pseudocode
        // taskID = Task_ID++;
        // this.taskName = taskName;
        // this.description = description;
        // this.priority = priority;
        // this.dependency = dependency;
        // this.status = "Pending";
        // this.isCompleted = false;
        // End of pseudocode
    }

    void createTask()
    {
        // Pseudocode: Create a new task
        // Start of pseudocode
        //  task.status = "Pending"
        // End of pseudocode
    }
    void updateTask()
    {
        // Pseudocode: Update task details
        // Start of pseudocode
        //  task.status = "Pending"
        // End of pseudocode
    }
    void viewTaskDetails()
    {
        // Pseudocode: View task details
        // Start of pseudocode
        //  print details
        // End of pseudocode
    }
    void assignTaskToEmployee(Employee &emp)
    {
        // Pseudocode: Assign a task to an employee
        // Start of pseudocode
        // task.employee.push_back(emp);
        // End of pseudocode
    }
};

class LeaveEntitlement
{
    int sickLeaves;
    int personalLeaves;
    int casualLeaves;

public:
    LeaveEntitlement(string typeOfEmployee = "onPayRoll")
    {
        sickLeaves = 20;
        personalLeaves = 15;
        if (typeOfEmployee == "onContract")
            casualLeaves = 0;
        else
            casualLeaves = 10;
    }

    void updateLeaveEntitlement(string leaveType, int days)
    {
        // Pseudocode: Update leave entitlement
        // Start of pseudocode
        //  if leaveType equals "sickleaves"
        //      sickLeaves -= days
        //    else if leaveType equals "personalLeaves"
        //      personalLeaves -= days
        //    else if leaveType equals "casualLeaves"
        //      casualLeaves -= days
        //  else
        //      print "Invalid leave type"
        //  End if
        // End of pseudocode
    }
    void viewLeaveEntitlement()
    {
        // Pseudocode: View leave entitlement
        // Start of pseudocode
        //  print leave entitlement
        // End of pseudocode
    }

};

class BankDetails
{
public:
    string bankName;
    string bankBranch;
    string bankIFSCode;
    long accountNo;
    BankDetails()
    {
        // default constructor
    }

    BankDetails(string bankName, string bankBranch, string bankIFSCode, long accountNo)
    {
        // assign details
    }

    void viewBankDetails()
    {
        // Pseudocode: View bank details
        // Start of pseudocode
        //  print bank details
        // End of pseudocode
    }
};

class SalaryStructure
{
    int CTC;
    int basicSalary;
    int deduction;
    Allowances *allow;

public:
    SalaryStructure(int ctc, int basicSalary, int deduction)
    {
        // CTC =ctc;
        // basicSalary = ctc * 0.5;
        // deduction = deduction;
        // allow = new Allowances();
    }
};

class Allowances
{
    vector<pair<string, int>> listOfAllowances;

public:
    Allowances()
    {
        // initialize allowances with default values
    }

    void addAllowance(string name, int amount)
    {
        //listOfAllowances.push_back(make_pair(name, amount));
    }

    void viewAllowances()
    {
        // Pseudocode: View allowances
        // Start of pseudocode
        // for each allowance in listOfAllowances
        //     print allowance.name, allowance.amount
        // end for
        // End of pseudocode
    }
};

class SalarySlip
{
    int slipID;
    int employeeID;
    string monthYear;
    SalaryStructure *structure;

public:
    void viewSalarySlip()
    {
        // Pseudocode: View salary slip
        // Start of pseudocode
        // for loop
        // if SalarySlip.employeeID == this->employeeID
        //      print salary slip from the filesystem
        // end if
        // End of for
        // End of pseudocode
    }
    void generateSlip()
    {
        // Pseudocode: Generate salary slip
        // Start of pseudocode
        // Calculate Basic Salary
        // basicSalary = ctc * 0.5 // basic salary is 50% of ctc
        // for loop on structure.allow
        //  add all allowances
        // allowances += allow.second;
        // end of for loop
        // deductions = 1200 // for PF and insurance
        // Calculate Total salary
        // totalSalary = basicSalary + allowances - deductions;
        // taxDeduction = totalSalary * 0.10; // tax 10% of total salary
        // netSalary = totalSalary - taxDeduction
        // End of pseudocode
    }
};

class LeaveTransaction
{
    int leaveID;
    int employeeID;
    string leaveType;
    string reason;
    string startDate;
    string endDate;
    int days;
    string status;

public:
    // constructor
    LeaveTransaction(int employeeID, string leaveType, string reason, string startDate, string endDate, int days)
    {
        // Pseudocode: Initialize leave transaction with details
        // Start of pseudocode
        // leaveID = Leave_ID++;
        // this.employeeID = employeeID;
        // this.leaveType = leaveType;
        // this.reason = reason;
        // this.startDate = startDate;
        // this.endDate = endDate;
        // this.days = days;
        // this.status = "Pending";
        // End of pseudocode
    }

    void logLeaveRequest(LeaveTransaction &leaveTransaction)
    {
        // Pseudocode: Log leave request
        // Start of pseudocode
        // open leaveTransaction file in append mode
        // write leave transaction details to the file
        // close the file
        // End of pseudocode
    }
    void updateLeaveBalance()
    {
        // Pseudocode: Update leave balance
        // Start of pseudocode
        // open leaveTransaction file in append mode
        // if leaveTransaction.status is approved
        //      updateLeaveEntitlement(string leaveType, int days)  
        //     
        //  else if leaveTransaction.status is rejected
        //      do nothing
        //
        //  open log file in append mode
        //      write leave transaction details to the file
        //  close the log file
        // erase transaction in trasaction file
        // close the file
        // End of pseudocode

    }

    void viewLeaveHistory()
    {
        // Pseudocode: View leave history
        // Start of pseudocode
        // open leaveTransaction file in read mode
        // for loop log file
        // if leaveTransaction.employeeID == this.employeeID
        //      print leaveTransaction details
        // close the file
        // End of pseudocode
    }
};

class EmployeeType {
private:
    static vector<string> typeList;

public:
    EmployeeType() {
        // initialize typeList with default values
        // open file in read mode
        // for loop file
        //  typeList.push_back(line);
        // close the file
        // End of pseudocode
    }

    void addType(string typeName) {
        // Pseudocode: Add a type
        // Start of pseudocode
        //  open file in append mode
        //  write typeName to the file
        //  close the file
        // End of pseudocode
    }

    void removeType(string typeName) {
        // Pseudocode: Remove a type
        // Start of pseudocode
        //  open file and search for the type
        //  if typeName is found
        //       erase typeName from file
        //  else
        //       print typeName not found
        //  close file
        // End of pseudocode
       
    }

    vector<string> getAllType() {
       // return typeList;
    }

    void viewTypeList() {
        // Pseudocode: View all types
        // Start of pseudocode
        // for each typeName in typeList
        //      print typeName
        // End of pseudocode        
    }
};

class Employee
{
    int E_ID;
    string userName;
    string name;
    string email;
    string password;
    string addreass;
    string alternateEmail;
    long alternaleContactNumber;
    string EmergencyContactName;
    long EmergencyContactNumber;
    string NomineeName;
    int NomineeShare;
    int ManagerID;
    bool isActive;

    // Relationships
    Role *role;
    EmployeeType *employeeType;
    Emp_dept *emp_dept;
    LeaveEntitlement *leaveEntitlement;
    BankDetails *bankDetails;

public:
    // Constructor
    Employee(string userName, string name, string email, string addreass, string alternateEmail, long alternaleContactNumber, string emergencyContactName, long emergencyContactNumber, string NomineeName, int NomineeShare, bool isActive)
    {
        // Pseudocode: Initialize employee with details
        // Start of pseudocode
        // E_ID = generateEmployeeID();
        // this.userName = userName;
        // this.name = name;
        // this.email = email;
        // this.addreass = addreass;
        // this.alternateEmail = alternateEmail;
        // this.alternaleContactNumber = alternaleContactNumber;
        // this.emergencyContactName = emergencyContactName;
        // this.emergencyContactNumber = emergencyContactNumber;
        // this.NomineeName = NomineeName;
        // this.NomineeShare = NomineeShare;
        // this.isActive = isActive;
        // this.ManagerID = 0;
        // End of pseudocode
    }

    int generateEmployeeID()
    {
        // Implement logic to generate unique employee ID
        // return 1000 + rand() % 9000;
    }

    void setRole(Role role)
    {
        // Implement logic to set role
        // Start of pseudocode
        // this->role = role;
        // End of pseudocode
    }
    void setEmployeeType(EmployeeType &employeeType)
    {
        // Implement logic to set employee type
        // Start of pseudocode
        // this->employeeType = employeeType;
        // End of pseudocode
    }
    void setEmpDept(Department &department)
    {
        // Implement logic to set employee department
        // Start of pseudocode
        // this->emp_dept = department.id;
        // End of pseudocode
    }
    void setLeaveEntitlement(LeaveEntitlement &leaveEntitlement)
    {
        // Implement logic to set leave entitlement
        // Start of pseudocode
        // this->leaveEntitlement = leaveEntitlement;
        // End of pseudocode
    }
    void setBankDetails(BankDetails &bankDetails)
    {
        // Implement logic to set bank details
        // Start of pseudocode
        // this->bankDetails = bankDetails;
        // End of pseudocode
    }

    void setManagerID(int managerID)
    {
        // Implement logic to set manager
        // Start of pseudocode
        // ManagerID = managerID;
        // End of pseudocode
    }

    void viewDetails()
    {
        // Pseudocode: print all details
        // Start of pseudocode
        // print details of employee
        // End of pseudocode
    }
    void updateNomineeName(string newNomineeName)
    {
        // Implement logic to update nominee name
        // Start of pseudocode
        // nomineeName = newNomineeName;
        // End of pseudocode
    }
    void updateNomineeShare(int newNomineeShare)
    {
        // Implement logic to update nominee share
        // Start of pseudocode
        // nomineeShare = newNomineeShare;
        // End of pseudocode
    }
    void updateAlternateEmail(string newAlternateEmail)
    {
        // Implement logic to update alternate email
        // Start of pseudocode
        // alternateEmail = newAlternateEmail;
        // End of pseudocode
    }
    void updateAlternateNumber(long newAlternateNumber)
    {
        // Implement logic to update alternate contact number
        // Start of pseudocode
        // alternaleContactNumber = newAlternateNumber;
        // End of pseudocode
    }
    void updateEmergencyContactName(string newEmergencyContactName)
    {
        // Implement logic to update emergency contact name
        // Start of pseudocode
        // emergencyContactName = newEmergencyContactName;
        // End of pseudocode
    }
    void updateEmergencyContactNumber(long newEmergencyNumber)
    {
        // Implement logic to update emergency contact number
        // Start of pseudocode
        // emergencyContactNumber = newEmergencyNumber;
        // End of pseudocode
    }
    void updateAddress(string newAddress)
    {
        // Implement logic to update address
        // Start of pseudocode
        // addreass = newAddress;
        // End of pseudocode
    }

    void changePassword(string newPassword)
    {
        // Implement logic to change password
        // Start of pseudocode
        // password = newPassword;
        // End of pseudocode
    }

    void requestForLeave_wrapper(string leaveType, int days)
    {
        // Implement logic to request for leave
        // Start of pseudocode
        // leaveTransaction.requestForLeave(leaveType, days);
        // End of pseudocode
    }
    void viewSalarySlip_wrapper()
    {
        // Implement logic to view salary slip
        // Start of pseudocode
        // salarySlip.viewSalarySlip();
        // End of pseudocode
    }
    void viewLeaveBalance_wrapper()
    {
        // Implement logic to view leave balance
        // Start of pseudocode
        // leaveEntitlement.viewLeaveEntitlement();
        // End of pseudocode
    }
    void leaveHistory_wrapper()
    {
        // Implement logic to view leave history
        // Start of pseudocode
        // leaveTransaction.viewLeaveHistory();
        // End of pseudocode
    }
};
