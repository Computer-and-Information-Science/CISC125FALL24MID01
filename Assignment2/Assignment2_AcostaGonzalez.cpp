// Coding Assignment #2
// By: Jarel Acosta Gonzalez

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Employee {    // represents abstracts variables for Employees
protected:
    string name;
    int empID;
public:
    virtual void printDetails() = 0;    // represents printing employee details
    virtual double calculateSalary() = 0;    // represents calculating salary
    virtual ~Employee() {}    // virtual destructor for proper cleanup
};

class FullTimeEmployee:public Employee {    // derived class represents full-time
private:
    double basicSalary;

public:
    FullTimeEmployee(string n, int id, double salary) {    // this constructor initialize's full-time
        name = n;
        empID = id;
        basicSalary = salary;
    }
    void printDetails()override {    
        cout << "\nFull-time Employee:\n";    // output of full-time details
        cout << "Name: " << name << ", ID: " << empID << ", Basic Salary: $" << basicSalary << endl; 
    }
    double calculateSalary()override {    // calculates/returns salary info
        return basicSalary;
    }
};

class PartTimeEmployee:public Employee {    // same as full-time, derived class but this time represents part-time
private:
    double hourlyWage;
    int hoursWorked;    // taking into account both hourly wage & hrs worked as compared to full-time

public:
    PartTimeEmployee(string n, int id, double wage, int hours) {    // this constructor initialize's part-time employees
        name = n;
        empID = id;
        hourlyWage = wage;
        hoursWorked = hours;
    }
    void printDetails() override {
        cout << "\nPart-time Employee:\n";    // output of part-time details
        cout << "Name: " << name << ", ID: " << empID << ", Hourly Wage: $" 
            << hourlyWage << ", Hours Worked: " << hoursWorked << endl;    // cut line down as to not stretch
    }
    double calculateSalary() override {
        return hourlyWage * hoursWorked;    // calculates/returns salary info
    }
};

int main() {
    int numberOfEmployees;
        cout << "Enter the number of employees: "; // user inputs for #'s of employees
        cin >> numberOfEmployees;
    vector<Employee*> employees;    // dynamic arry of employee pointers

    for (int i = 0; i < numberOfEmployees; i++) { // input details for said # of employees
        string name;
        int empID, empType;

        cout << "\nEnter the details for Employee " << (i + 1) << ":\n";
        cout << "Enter name: ";
        cin >> ws; // allows for a clean space for next input
        getline(cin, name);
        cout << "Enter employee ID: ";
        cin >> empID;
        cout << "Enter employee type (1 for Full-time, 2 for Part-time): ";
        cin >> empType;

        if (empType == 1) {    // represents full-time employees
            double basicSalary;
            cout << "Enter basic salary: ";
            cin >> basicSalary;
            employees.push_back(new FullTimeEmployee(name, empID, basicSalary));
        } else if (empType == 2) {    // represents part-time employees
            double hourlyWage;
            int hoursWorked;
            cout << "Enter hourly wage: ";
            cin >> hourlyWage;
            cout << "Enter hours worked: ";
            cin >> hoursWorked;
            employees.push_back(new PartTimeEmployee(name, empID, hourlyWage, hoursWorked));
        } else {
            cout << "Invalid employee type! Skipping this entry." << endl;
            i--;    // assist the user in repeating the input for employee
        }
    }
    cout << "\nEmployee Details and Salaries:\n";    // output of employee detail and calculated salary
    for (Employee* emp:employees) {
        emp->printDetails();
        cout << "Calculated Salary: $" << emp->calculateSalary() << endl;
    }
    for (Employee* emp:employees) {    // deletes employee objects
        delete emp;
    }
return 0;
}
