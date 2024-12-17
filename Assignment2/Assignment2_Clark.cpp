#include <iostream>
#include <string>
using namespace std;

//Base Class Employee
class Employee {
protected:
    string name;
    int empID;

public:
    //Constructor
    Employee(string n, int id) : name(n), empID(id) {}

    //Pure virtual functions
    virtual void printDetails() const = 0;
    virtual double calculateSalary() const = 0;

    //Virtual Destructor
    virtual ~Employee() {}
};

// Derived Class: FullTimeEmployee
class FullTimeEmployee : public Employee {
private:
    double basicSalary;

public:
    //Constructor
    FullTimeEmployee(string n, int id, double salary)
        : Employee(n, id), basicSalary(salary) {}

    //Override printDetails
    void printDetails() const override {
        cout << "Full-Time Employee Details:\n";
        cout << "Name: " << name << "\nEmployee ID: " << empID
             << "\nBasic Salary: $" << basicSalary << endl;
    }

    //Override calculateSalary
    double calculateSalary() const override {
        return basicSalary;
    }
};

//Derived Class PartTimeEmployee
class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;

public:
    //Constructor
    PartTimeEmployee(string n, int id, double wage, int hours)
        : Employee(n, id), hourlyWage(wage), hoursWorked(hours) {}

    //Override printDetails
    void printDetails() const override {
        cout << "Part-Time Employee Details:\n";
        cout << "Name: " << name << "\nEmployee ID: " << empID
             << "\nHourly Wage: $" << hourlyWage
             << "\nHours Worked: " << hoursWorked << endl;
    }

    //Override calculateSalary
    double calculateSalary() const override {
        return hourlyWage * hoursWorked;
    }
};

//Main Block
int main() {
    int numEmployees;

    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    //Pointer array stores Employee objects
    Employee* employees[numEmployees];

    for (int i = 0; i < numEmployees; ++i) {
        cout << "\nEnter details for Employee " << (i + 1) << ":\n";
        string name;
        int empID, empType;

        cout << "Name: ";
        cin.ignore(); //Clears input buffer
        getline(cin, name);

        cout << "Employee ID: ";
        cin >> empID;

        cout << "Enter Employee Type (1 for Full-Time, 2 for Part-Time): ";
        cin >> empType;

        if (empType == 1) { //Full-Time Employee
            double basicSalary;
            cout << "Enter Basic Salary: $";
            cin >> basicSalary;

            employees[i] = new FullTimeEmployee(name, empID, basicSalary);
        } else if (empType == 2) { //Part-Time Employee
            double hourlyWage;
            int hoursWorked;

            cout << "Enter Hourly Wage: $";
            cin >> hourlyWage;

            cout << "Enter Hours Worked: ";
            cin >> hoursWorked;

            employees[i] = new PartTimeEmployee(name, empID, hourlyWage, hoursWorked);
        } else {
            cout << "Invalid employee type! Skipping entry.\n";
            --i; //Retry for current employee
        }
    }

    //Displays Employee Details and Salaries
    cout << "\nEmployee Details and Salaries:\n";
    for (int i = 0; i < numEmployees; ++i) {
        cout << "----------------------------------\n";
        employees[i]->printDetails();
        cout << "Salary: $" << employees[i]->calculateSalary() << "\n";
    }

    //Frees dynamically allocated memory
    for (int i = 0; i < numEmployees; ++i) {
        delete employees[i];
    }

    cout << "\nMemory cleared. Program terminated successfully.\n";
    return 0;
}
