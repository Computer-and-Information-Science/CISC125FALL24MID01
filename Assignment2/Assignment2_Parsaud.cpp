#include <iostream>
#include <string>
using namespace std;

// We can first create the base class for the employees.
class Employee {
protected:
    string name;
    int empID;
public:
    Employee(string empName, int id) : name(empName), empID(id) {}
    virtual void printDetails() = 0; // Pure virtual function
    virtual double calculateSalary() = 0; // Pure virtual function
    virtual ~Employee() {} // Virtual destructor
};

// Then the derived class for the Full-Timers.
class FullTimeEmployee : public Employee {
private:
    double basicSalary;
public:
    FullTimeEmployee(string empName, int id, double salary) 
        : Employee(empName, id), basicSalary(salary) {}
    
    void printDetails() override {
        cout << "Full-Time Employee: " << name << ", ID: " << empID 
             << ", Salary: $" << calculateSalary() << endl;
    }
    
    double calculateSalary() override {
        return basicSalary;
    }
};

// Then we create the derived class for the Part-Timers.
class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(string empName, int id, double wage, int hours) 
        : Employee(empName, id), hourlyWage(wage), hoursWorked(hours) {}
    
    void printDetails() override {
        cout << "Part-Time Employee: " << name << ", ID: " << empID 
             << ", Salary: $" << calculateSalary() << endl;
    }
    
    double calculateSalary() override {
        return hourlyWage * hoursWorked;
    }
};

int main() {
    int numEmployees;
    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    Employee* employees[numEmployees]; // Array of Employee pointers

    for (int i = 0; i < numEmployees; i++) {
        string name;
        int empID, empType;
        cout << "\nEnter name of employee #" << i + 1 << ": ";
        cin >> name;
        cout << "Enter employee ID: ";
        cin >> empID;
        cout << "Enter employee type (1 for Full-Time, 2 for Part-Time): ";
        cin >> empType;

        if (empType == 1) {
            double basicSalary;
            cout << "Enter basic salary: ";
            cin >> basicSalary;
            employees[i] = new FullTimeEmployee(name, empID, basicSalary); // Dynamic allocation
        } else if (empType == 2) {
            double hourlyWage;
            int hoursWorked;
            cout << "Enter hourly wage: ";
            cin >> hourlyWage;
            cout << "Enter hours worked: ";
            cin >> hoursWorked;
            employees[i] = new PartTimeEmployee(name, empID, hourlyWage, hoursWorked); // Dynamic allocation
        } else {
            cout << "Invalid employee type!" << endl;
            i--; // Decrement counter to retry
        }
    }

    cout << "\nEmployee Details:\n";
    for (int i = 0; i < numEmployees; i++) {
        employees[i]->printDetails();
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < numEmployees; i++) {
        delete employees[i];
    }

    return 0;
}