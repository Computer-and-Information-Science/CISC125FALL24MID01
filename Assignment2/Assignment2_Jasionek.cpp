// CSproject2.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>

// Abstract Base Class
class Employee {
protected:
    std::string name;
    int empID;
public:
    Employee(std::string m_name, int m_empID)
        : name(m_name), empID(m_empID) {} // Constructor, we want to create objects of this class
    virtual ~Employee() = default; // Destructor, we eventually want to delete them
    virtual void printDetails() = 0; // Pure Virtual Function
    virtual double calculateSalary() = 0; // Pure Virtual Function
};

// Derived Class for Full-Time Employees
class FullTimeEmployee : public Employee {
private:
    double basicSalary;

public:
    FullTimeEmployee(std::string m_name, int m_empID, double m_basicSalary)
        : Employee(m_name, m_empID), basicSalary(m_basicSalary) {} // Constructor, we want to create objects of this class

    void printDetails() override { // Polymorphism
        std::cout << "Full-Time Employee: " << name 
                  << "\nID: "               << empID
                  << "\nBasic Salary: $"    << basicSalary << '\n';
    }

    double calculateSalary() override { // Polymorphism 
        return basicSalary;
    }
};

// Derived Class for Part-Time Employees
class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;

public:
    PartTimeEmployee(std::string m_name, int m_empID, double m_hourlyWage, int m_hoursWorked)
        : Employee(m_name, m_empID), hourlyWage(m_hourlyWage), hoursWorked(m_hoursWorked) {} // Constructor, we want to create objects of this class

    void printDetails() override { // Polymorphism
        std::cout << "Part-Time Employee: " << name 
                  << "\nID: "               << empID
                  << "\nHourly Wage: $"     << hourlyWage
                  << "\nHours Worked: "     << hoursWorked << '\n';
    }
     
    double calculateSalary() override { // Polymorphism
        return hourlyWage * hoursWorked;
    }
};

// Function to get user input about employee details
void inputEmployeeDetails(Employee** employees, int numEmployees) {
    for (int i = 0; i < numEmployees; ++i) {
        std::string name;
        int empID;
        int empType;

        std::cout << "\nEnter details for employee " << i + 1 << '\n';
        std::cout << "Name: ";
        std::cin >> name;

        if (std::cin.fail()) { // Clear input buffer if cin fails for whatever reason.
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input.\n";
            continue;
        }

        std::cout << "Employee ID: ";
        std::cin >> empID;

        std::cout << "Employee Type (1 - Full-Time, 2 - Part-Time): ";
        std::cin >> empType;

        if (empType == 1) {
            double basicSalary;
            std::cout << "Enter basic salary: ";
            std::cin >> basicSalary;
            employees[i] = new FullTimeEmployee(name, empID, basicSalary); // Allocate memory for Object
        }
        else if (empType == 2) {
            double hourlyWage;
            int hoursWorked;
            std::cout << "Enter hourly wage: ";
            std::cin >> hourlyWage;
            std::cout << "Enter hours worked: ";
            std::cin >> hoursWorked;
            employees[i] = new PartTimeEmployee(name, empID, hourlyWage, hoursWorked); // Allocate memory for Object
        }
        else {
            std::cout << "Invalid employee type. Skipping this employee." << '\n';
            employees[i] = nullptr; // Null pointer if invalid
        }
    }
}

// Function to display employee details and calculate salaries
void displayEmployeeDetails(Employee** employees, int numEmployees) {
    std::cout << "\n ******* Employee Details: ******* \n" << "-----------------------------------------\n";
    for (int i = 0; i < numEmployees; ++i) {
        if (employees[i]) {
            employees[i]->printDetails(); // Using polymorphism
            std::cout << "Calculated Salary: $" << employees[i]->calculateSalary() << '\n'; // Using polymorphism
            std::cout << "-----------------------------------------\n";
        }
    }
}

int main()
{
    // Get number of employees
    int numEmployees;
    std::cout << "Enter the number of employees: ";
    std::cin >> numEmployees;

    // Cool dynamic array of pointers to objects of type Employee
    Employee** employees = new Employee * [numEmployees];

    // Input employee details
    inputEmployeeDetails(employees, numEmployees);

    // Display employee details
    displayEmployeeDetails(employees, numEmployees);

    // Free memory
    for (int i = 0; i < numEmployees; ++i) {
        delete employees[i];
    }
    delete[] employees;

    return 0;
}
