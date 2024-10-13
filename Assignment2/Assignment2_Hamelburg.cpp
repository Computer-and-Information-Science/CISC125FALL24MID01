// Pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Employee {
protected:
    string name;
    int empID;

public:
    Employee(string& n, int id) : name(n), empID(id) {}//constructor
    virtual ~Employee() {} // virtual destructor

    //virtual functions
    virtual void printDetails() = 0;
    virtual double calculateSalary() = 0;
};

class FullTimeEmployee : public Employee {
private:
    double basicSalary;

public:
    FullTimeEmployee(string& n, int id, double salary) 
        : Employee(n, id), basicSalary(salary) {}//constructor sets the values: n = name, id = empID, salary = basicSalary


    void printDetails() {
        cout << "Full-Time Employee:" << endl;
        cout << "Name: " << name << ", ID: " << empID << ", Basic Salary: " << basicSalary << endl;
    }

    double calculateSalary() {
        return basicSalary;
    }
};

class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(string& n, int id, double wage, int hours): Employee(n, id), hourlyWage(wage), hoursWorked(hours) {}//constructor

    void printDetails() {
        cout << "Part-Time Employee:" << endl;
        cout << "Name: " << name << ", ID: " << empID << ", Hourly Wage: " << hourlyWage << ", Hours Worked: " << hoursWorked << endl;
    }

    double calculateSalary() {
        return hourlyWage * hoursWorked;
    }
};

int main()
{
    int numberOfEmployees;
    cout << "Enter the number of employees: ";
    cin >> numberOfEmployees;

    //Allocate an array of Employee pointers
    Employee** p_Employ = new Employee*[numberOfEmployees];

    //for-loop repeats for number of employees
    for (int i = 0; i < numberOfEmployees; i++) {
        string name;
        int ID, empType;
        cout << "Enter details for Employee " << i + 1 << ": " << endl;

        cout << "Enter name: ";
        cin >> name;

        cout << "Enter employee ID: ";
        cin >> ID;

        cout << "Enter employee type (1 for Full-Time, 2 for Part-Time): ";
        cin >> empType;

        if (empType == 1) {
            double basicSa;
            cout << "Enter basic salary: ";
            cin >> basicSa;
            p_Employ[i] = new FullTimeEmployee(name, ID, basicSa);
        }
        else if (empType == 2) {
            double hourlyWa;
            int hoursWork;

            cout << "Enter hourly wage: ";
            cin >> hourlyWa;
            cout << "Enter hours worked: ";
            cin >> hoursWork;

            p_Employ[i] = new PartTimeEmployee(name, ID, hourlyWa, hoursWork);
        }
        else {
            cout << "Invaild Number";
        
        }
        
    }

    for (int i = 0; i < numberOfEmployees; ++i) {
        
            p_Employ[i]->printDetails();
            cout << "Calculated Salary: $" << p_Employ[i]->calculateSalary() << endl;
        
    }

    for (int i = 0; i < numberOfEmployees; ++i) {
        delete p_Employ[i];//deletes each employee
    }

    delete[] p_Employ;//deletes array

}

