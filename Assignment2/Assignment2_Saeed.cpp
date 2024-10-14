#include <iostream>
#include <string>
using namespace std;

// Abstract base class Employee
class Employee {
protected:
    string name;
    int empID;

public:
    Employee(string empName, int empId) : name(empName), empID(empId) {}
    
    // Pure virtual functions
    virtual void printDetails() = 0;
    virtual double calculateSalary() = 0;
    
    
    virtual ~Employee() {}
};

// Derived class for Full-Time Employees
class FullTimeEmployee : public Employee {
private:
    double basicSalary;

public:
    FullTimeEmployee(string empName, int empId, double salary) 
        : Employee(empName, empId), basicSalary(salary) {}

    
    void printDetails() override {
        cout << "Full-Time Employee: " << endl;
        cout << "Name: " << name << ", ID: " << empID << ", Basic Salary: $" << basicSalary << endl;
    }

    
    double calculateSalary() override {
        return basicSalary;
    }
};

// Derived class for Part-Time Employees
class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;

public:
    PartTimeEmployee(string empName, int empId, double wage, int hours) 
        : Employee(empName, empID), hourlyWage(wage), hoursWorked(hours) {}

    
    void printDetails() override {
        cout << "Part-Time Employee: " << endl;
        cout << "Name: " << name << ", ID: " << empID << ", Hourly Wage: $" << hourlyWage << ", Hours Worked: " << hoursWorked << endl;
    }

    // Override calculateSalary() to return hourly wage × hours worked
    double calculateSalary() override {
        return hourlyWage * hoursWorked;
    }
};


int main() {
    int numEmployees;
    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    // Create an array
    Employee* employees[numEmployees];

    // Input employee details
    for (int i = 0; i < numEmployees; i++) {
        cout << "\nEnter details for employee " << (i + 1) << ":" << endl;
        string name;
        int empID, empType;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter employee ID: ";
        cin >> empID;
        cout << "Enter employee type (1 for Full-Time, 2 for Part-Time): ";
        cin >> empType;

        if (empType == 1) {  // Full-Time Employee
            double basicSalary;
            cout << "Enter basic salary: ";
            cin >> basicSalary;
            employees[i] = new FullTimeEmployee(name, empID, basicSalary);
        } else if (empType == 2) {  // Part-Time Employee
            double hourlyWage;
            int hoursWorked;
            cout << "Enter hourly wage: ";
            cin >> hourlyWage;
            cout << "Enter hours worked: ";
            cin >> hoursWorked;
            employees[i] = new PartTimeEmployee(name, empID, hourlyWage, hoursWorked);
        } else {
            cout << "Invalid employee type!" << endl;
            i--;  
        }
    }

    // Display employee details and calculate their salaries
    cout << "\nEmployee Details and Salaries:\n";
    for (int i = 0; i < numEmployees; i++) {
        employees[i]->printDetails();
        cout << "Calculated Salary: $" << employees[i]->calculateSalary() << endl << endl;
    }

    // Free dynamically allocated memory
    for (int i = 0; i < numEmployees; i++) {
        delete employees[i];
    }

    return 0;
}