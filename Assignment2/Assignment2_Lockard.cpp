#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    int empID;

public:
    Employee(string n, int id) : name(n), empID(id) {}

    virtual void printDetails() const = 0;
    virtual double calculateSalary() const = 0;

    virtual ~Employee() {}
};

class FullTimeEmployee : public Employee {
private:
    double basicSalary;

public:
    FullTimeEmployee(string n, int id, double salary)
        : Employee(n, id), basicSalary(salary) {}

    void printDetails() const override {
        cout << "Full-Time Employee:\n";
        cout << "Name: " << name << ", ID: " << empID << ", Basic Salary: $" << basicSalary << "\n";
    }

    double calculateSalary() const override {
        return basicSalary;
    }
};

class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;

public:
    PartTimeEmployee(string n, int id, double wage, int hours)
        : Employee(n, id), hourlyWage(wage), hoursWorked(hours) {}

    void printDetails() const override {
        cout << "Part-Time Employee:\n";
        cout << "Name: " << name << ", ID: " << empID << ", Hourly Wage: $" << hourlyWage
            << ", Hours Worked: " << hoursWorked << "\n";
    }

    double calculateSalary() const override {
        return hourlyWage * hoursWorked;
    }
};

int main() {
    int numEmployees;
    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    Employee** employees = new Employee * [numEmployees];

    for (int i = 0; i < numEmployees; ++i) {
        string name;
        int empID, empType;

        cin.ignore();

        cout << "\nEnter details for Employee " << (i + 1) << ":\n";
        cout << "Enter name: ";
        getline(cin, name);

        cout << "Enter employee ID: ";
        cin >> empID;

        cout << "Enter employee type (1 for Full-Time, 2 for Part-Time): ";
        cin >> empType;

        if (empType == 1) {
            double basicSalary;
            cout << "Enter basic salary: $";
            cin >> basicSalary;
            employees[i] = new FullTimeEmployee(name, empID, basicSalary);
        }
        else if (empType == 2) {
            double hourlyWage;
            int hoursWorked;
            cout << "Enter hourly wage: $";
            cin >> hourlyWage;
            cout << "Enter hours worked: ";
            cin >> hoursWorked;
            employees[i] = new PartTimeEmployee(name, empID, hourlyWage, hoursWorked);
        }
        else {
            cout << "Invalid employee type! Try again.\n";
            --i;
        }
    }

    cout << "\nEmployee Details and Salaries:\n";
    for (int i = 0; i < numEmployees; ++i) {
        employees[i]->printDetails();
        cout << "Calculated Salary: $" << employees[i]->calculateSalary() << "\n\n";
    }

    for (int i = 0; i < numEmployees; ++i) {
        delete employees[i];
    }
    delete[] employees;

    return 0;
}