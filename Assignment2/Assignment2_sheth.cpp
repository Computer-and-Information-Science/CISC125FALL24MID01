#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Abstract Base Class Employee
class Employee {
protected:
    string name;
    int empID;

public:
    Employee(string empName, int empId) : name(empName), empID(empId) {}

    virtual void printDetails() const = 0;  // Pure virtual function
    virtual double calculateSalary() const = 0;  // Pure virtual function

    virtual ~Employee() {}  // Virtual destructor
};

// Full-time employee class
class FullTimeEmployee : public Employee {
private:
    double basicSalary;

public:
    FullTimeEmployee(string empName, int empId, double salary)
        : Employee(empName, empId), basicSalary(salary) {}

    void printDetails() const override {
        cout << "Full-Time Employee\n";
        cout << "Name: " << name << "\n";
        cout << "Employee ID: " << empID << "\n";
        cout << "Basic Salary: $" << basicSalary << "\n";
    }

    double calculateSalary() const override {
        return basicSalary;
    }
};

// Part-time employee class
class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;

public:
    PartTimeEmployee(string empName, int empId, double wage, int hours)
        : Employee(empName, empId), hourlyWage(wage), hoursWorked(hours) {}

    void printDetails() const override {
        cout << "Part-Time Employee\n";
        cout << "Name: " << name << "\n";
        cout << "Employee ID: " << empID << "\n";
        cout << "Hourly Wage: $" << hourlyWage << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
    }

    double calculateSalary() const override {
        return hourlyWage * hoursWorked;
    }
};

int main() {
    int numEmployees;
    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    vector<Employee*> employees;  // Vector to store employee pointers

    for (int i = 0; i < numEmployees; ++i) {
        string name;
        int empID;
        int type;
        
        cout << "Enter details for employee " << i + 1 << ":\n";
        cout << "Name: ";
        cin >> name;
        cout << "Employee ID: ";
        cin >> empID;
        cout << "Enter 1 for Full-Time, 2 for Part-Time: ";
        cin >> type;

        if (type == 1) {
            double salary;
            cout << "Enter basic salary: ";
            cin >> salary;
            employees.push_back(new FullTimeEmployee(name, empID, salary));
        } else if (type == 2) {
            double wage;
            int hours;
            cout << "Enter hourly wage: ";
            cin >> wage;
            cout << "Enter hours worked: ";
            cin >> hours;
            employees.push_back(new PartTimeEmployee(name, empID, wage, hours));
        } else {
            cout << "Invalid type entered!\n";
        }
    }

    // Display details and calculate salaries
    for (int i = 0; i < numEmployees; ++i) {
        employees[i]->printDetails();
        cout << "Salary: $" << employees[i]->calculateSalary() << "\n\n";
    }

    // Freeing dynamically allocated memory
    for (int i = 0; i < numEmployees; ++i) {
        delete employees[i];
    }

    return 0;
}