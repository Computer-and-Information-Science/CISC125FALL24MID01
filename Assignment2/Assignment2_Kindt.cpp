#include <iostream>
#include <string>

using namespace std;

// Abstract base class
class Employee {
protected:
    string name;
    int empID;

public:
    Employee(string n, int id) : name(n), empID(id) {}
    virtual void printDetails() = 0; // Pure virtual function
    virtual double calculateSalary() = 0; // Pure virtual function
};

// Full-time employee class
class FullTimeEmployee : public Employee {
private:
    double basicSalary;

public:
    FullTimeEmployee(string n, int id, double salary)
        : Employee(n, id), basicSalary(salary) {}

    void printDetails() override {
        cout << "Full-Time Employee\n";
        cout << "Name: " << name << "\nEmployee ID: " << empID << "\nBasic Salary: $" << basicSalary << endl;
    }

    double calculateSalary() override {
        return basicSalary;
    }
};

// Part-time employee class
class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;

public:
    PartTimeEmployee(string n, int id, double wage, int hours)
        : Employee(n, id), hourlyWage(wage), hoursWorked(hours) {}

    void printDetails() override {
        cout << "Part-Time Employee\n";
        cout << "Name: " << name << "\nEmployee ID: " << empID << "\nHourly Wage: $" << hourlyWage
             << "\nHours Worked: " << hoursWorked << endl;
    }

    double calculateSalary() override {
        return hourlyWage * hoursWorked;
    }
};

int main() {
    int numEmployees;
    cout << "Enter number of employees: ";
    cin >> numEmployees;

    Employee** employees = new Employee*[numEmployees]; // Array of pointers

    for (int i = 0; i < numEmployees; ++i) {
        string name;
        int empID, type;

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Employee ID: ";
        cin >> empID;
        cout << "Enter Employee Type (1 for Full-Time, 2 for Part-Time): ";
        cin >> type;

        if (type == 1) {
            double basicSalary;
            cout << "Enter Basic Salary: ";
            cin >> basicSalary;
            employees[i] = new FullTimeEmployee(name, empID, basicSalary);
        } else if (type == 2) {
            double hourlyWage;
            int hoursWorked;
            cout << "Enter Hourly Wage: ";
            cin >> hourlyWage;
            cout << "Enter Hours Worked: ";
            cin >> hoursWorked;
            employees[i] = new PartTimeEmployee(name, empID, hourlyWage, hoursWorked);
        } else {
            cout << "Invalid type! Try again.\n";
            i--; // Decrement index to retry
        }
    }

    // Display employee details
    for (int i = 0; i < numEmployees; ++i) {
        employees[i]->printDetails();
        cout << "Calculated Salary: $" << employees[i]->calculateSalary() << "\n\n";
    }
    
    delete[] employees; // Free the array

    return 0;
}