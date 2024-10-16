#include <iostream>
#include <string>
using namespace std;

// Abstract base class Employee
class Employee {
protected:
    string name;
    int emply_ID;

public:
    // Constructor
    Employee(string emply_Name, int emply_ID) : name(emply_Name), emply_ID(emply_ID) {}

    // Pure virtual functions
    virtual void printDetails() = 0;
    virtual double calculateSalary() = 0;

    // Virtual destructor to ensure proper cleanup
    virtual ~Employee() {}
};

// Derived class for Full-Time Employees
class FullTimeEmployee : public Employee {
private:
    double basic_salary;

public:
    // Constructor
    FullTimeEmployee(string emp_Name, int emp_ID, double salary)
        : Employee(emp_Name, emp_ID), basic_salary(salary) {}

    // Override printDetails
    void printDetails() override {
        cout << "\nFull-Time Employee: " << name << ", ID: " << emply_ID << endl;
        cout << "Basic Salary: $" << basic_salary << endl;
    }

    // Override calculateSalary
    double calculateSalary() override {
        return basic_salary;
    }
};

// Derived class for Part-Time Employees
class PartTimeEmployee : public Employee {
private:
    double Wage_hr;
    int hours_worked;

public:
    // Constructor
    PartTimeEmployee(string emp_Name, int emp_ID, double wage, int hours)
        : Employee(emp_Name, emp_ID), Wage_hr(wage), hours_worked(hours) {}

    // Override printDetails
    void printDetails() override {
        cout << "Part-Time Employee: " << name << ", ID: " << emply_ID << endl;
        cout << "Hourly Wage: $" << Wage_hr << ", Hours Worked: " << hours_worked << endl;
    }

    // Override calculateSalary
    double calculateSalary() override {
        return Wage_hr * hours_worked;
    }
};

int main() {
    int num_Employees;

    // Ask for the number of employees
    cout << "Enter the number of employees: ";
    cin >> num_Employees;

    // Dynamically create an array of pointers to Employee
    Employee* employees[num_Employees];

    for (int i = 0; i < num_Employees; ++i) {
        string name;
        int empID, empType;
        cout << "\nEnter details for Employee #" << (i + 1) << ":" << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Employee ID: ";
        cin >> empID;

        // Ask for the type of employee (Full-Time or Part-Time)
        cout << "Enter 1 for Full-Time or 2 for Part-Time: ";
        cin >> empType;

        if (empType == 1) {
            double basicSalary;
            cout << "Enter the basic salary: $";
            cin >> basicSalary;

            // Create FullTimeEmployee and store in the array
            employees[i] = new FullTimeEmployee(name, empID, basicSalary);
        } else if (empType == 2) {
            double hourlyWage;
            int hoursWorked;
            cout << "Enter the hourly wage: $";
            cin >> hourlyWage;
            cout << "Enter the number of hours worked: ";
            cin >> hoursWorked;

            // Create PartTimeEmployee and store in the array
            employees[i] = new PartTimeEmployee(name, empID, hourlyWage, hoursWorked);
        } else {
            cout << "Invalid input. Please enter 1 or 2." << endl;
            --i;  // Retry current employee input
        }
    }

    // Display details and calculate salary for all employees
    cout << "\nEmployee Details and Salaries:\n";
    for (int i = 0; i < num_Employees; ++i) {
        employees[i]->printDetails();
        cout << "Calculated Salary: $" << employees[i]->calculateSalary() << "\n" << endl;
    }

    // Free dynamically allocated memory
    for (int i = 0; i < num_Employees; ++i) {
        delete employees[i];
    }

    return 0;
}
