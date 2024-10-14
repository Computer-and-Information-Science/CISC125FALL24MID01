#include <iostream>
#include <string>
#include <stdexcept>  // For throwing exceptions

using namespace std;

// Abstract base class Employee
class Employee {
protected:
    string name;
    int empID;

public:
    Employee(string empName, int id) : name(empName), empID(id) {}
    virtual ~Employee() {}  // Virtual destructor

    // Pure virtual functions
    virtual void printDetails() const = 0;
    virtual double calculateSalary() const = 0;

    // I really wanted to apply taxes, I think it would make this assignment more realistic  (deductions including 401k)
    double applyTaxes(double grossSalary) const {
        const double totalDeductions = 0.22;  // 6% income tax + 5% healthcare + 7% social security + 4% 401k

        // Net salary after all deductions
        return grossSalary * (1 - totalDeductions);
    }
};

// Derived class for Full-time Employee
class FullTimeEmployee : public Employee {
private:
    double basicSalary;

public:
    FullTimeEmployee(string empName, int id, double salary)
        : Employee(empName, id), basicSalary(salary) {}

    void printDetails() const override {
        cout << "Full-Time Employee\n";
        cout << "Name: " << name << ", Employee ID: " << empID << "\n";
        cout << "Basic Salary: $" << basicSalary << "\n";
    }

    double calculateSalary() const override {
        double grossSalary = basicSalary;
        return applyTaxes(grossSalary);
    }
};

// Derived class for Part-time Employee
class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;

public:
    PartTimeEmployee(string empName, int id, double wage, int hours)
        : Employee(empName, id), hourlyWage(wage), hoursWorked(hours) {
        // A Check to see if the part-time employee is working more than 40 hours
        if (hoursWorked > 40) {
            throw runtime_error("Error: Part-time employees cannot work more than 40 hours per week.");
        }
    }

    void printDetails() const override {
        cout << "Part-Time Employee\n";
        cout << "Name: " << name << ", Employee ID: " << empID << "\n";
        cout << "Hourly Wage: $" << hourlyWage << ", Hours Worked: " << hoursWorked << "\n";
    }

    double calculateSalary() const override {
        double grossSalary = hourlyWage * hoursWorked;
        return applyTaxes(grossSalary);
    }
};

// Main function
int main() {
    int numEmployees;

    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    // Dynamically allocate an array of Employee pointers
    Employee** employees = new Employee*[numEmployees];

    for (int i = 0; i < numEmployees; ++i) {
        string name;
        int id, type;

        try {
            cout << "\nEnter details for Employee #" << (i + 1) << ":\n";
            cout << "Name: ";
            cin.ignore();  // Clear input buffer
            getline(cin, name);
            cout << "Employee ID: ";
            cin >> id;
            cout << "Employee Type (1 for Full-Time, 2 for Part-Time): ";
            cin >> type;

            if (type == 1) {
                double salary;
                cout << "Enter basic salary: ";
                cin >> salary;
                employees[i] = new FullTimeEmployee(name, id, salary);
            } else if (type == 2) {
                double hourlyWage;
                int hoursWorked;
                cout << "Enter hourly wage: ";
                cin >> hourlyWage;
                cout << "Enter hours worked: ";
                cin >> hoursWorked;

                // Trying to create the part-time employee (throws error if hours exceed 40)
                employees[i] = new PartTimeEmployee(name, id, hourlyWage, hoursWorked);
            } else {
                cout << "Invalid employee type! Skipping...\n";
                --i;  // Invalid entry, retry for this employee
            }
        } catch (const runtime_error& e) {
            // Catches exception if part-time employee worked over 40 hours
            cout << e.what() << endl;
            --i;  // Retry for this employee
        }
    }

    // Displays details and calculates salaries after tax deductions
    cout << "\nEmployee Details and Salaries (After Taxes and 401k Deduction):\n";
    for (int i = 0; i < numEmployees; ++i) {
        employees[i]->printDetails();
        cout << "Net Salary (After Taxes and 401k): $" << employees[i]->calculateSalary() << "\n\n";
    }

    // Frees the dynamically allocated memory
    for (int i = 0; i < numEmployees; ++i) {
        delete employees[i];
    }
    delete[] employees;  // Frees the array of pointers

    return 0;
}
