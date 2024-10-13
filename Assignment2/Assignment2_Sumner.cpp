#include <iostream>
using namespace std;

//Employee abstract base class
class Employee {
protected:
    string name = "N/A";  
    int empID = 0;
public:  
    Employee(string iname, int iempID) : name(iname), empID(iempID){}
    virtual void printDetails() const = 0;
    virtual void calculateSalary() const = 0;
};

//FullTimeEmployee class derived from Employee class
class FullTimeEmployee : public Employee {
protected:
    double basicSalary = 0.0;
public:   
    FullTimeEmployee(string iname, int iempID, double ibasicSalary) : Employee(iname,iempID), basicSalary(ibasicSalary){}
    void printDetails() const override {
        cout << "Full Time Employee:" << endl;
        cout << "Name: " << this->name << ", ID: " << this->empID << ", Basic Salary: $" << this->basicSalary << endl;
    };
    void calculateSalary() const override{
        cout << "Calculated Salary: $" << this->basicSalary << "\n" << endl;
    }
};

//PartTimeEmployee class derived from Employee class
class PartTimeEmployee : public Employee {
protected:
    double hourlyWage = 0.0;
    int hoursWorked = 0;
public:  
    PartTimeEmployee(string iname, int iempID, double ihourlyWage, int ihoursWorked) : Employee(iname,iempID), hourlyWage(ihourlyWage), hoursWorked(ihoursWorked){}
    void printDetails() const override{
        cout << "Part Time Employee:" << endl;
        cout << "Name: " << this->name << ", ID: " << this->empID << ", Hourly Wage: $" << this->hourlyWage << ", Hours Worked: " << this->hoursWorked << endl;
    };
    void calculateSalary() const override{
        cout << "Calculated Salary: $" << this->hourlyWage*this->hoursWorked << "\n" << endl;
    }
};

//type declarations
int emps;
string name;
int empID;
int type;
double basicSalary;
double hourlyWage;
int hoursWorked;

int main() {
//prompting for number of employees
cout << "Enter the number of employees: ";
cin >> emps;

//creating pointer array to manage objects in Employee class
Employee* employees[emps];

//prompting for inputs for class members
for (int i=0; i < emps; i++) {
    cout << "\nEnter details for Employee " << i+1 << ":" << endl;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter employee ID: ";
    cin >> empID;
    cout << "Enter employee type (1 for Full-Time, 2 for Part-Time): ";
    cin >> type;

//FullTimeEmploye specific inputs and entry into array   
    if (type == 1) {
        cout << "Enter basic salary: ";
        cin >> basicSalary;
        employees[i] = new FullTimeEmployee(name, empID, basicSalary);
    }
  
//PartTimeEmploye specific inputs and entry into array   
    else if (type == 2) {
        cout << "Enter hourly wage: ";
        cin >> hourlyWage;
        cout << "Enter hours worked: ";
        cin >> hoursWorked;
        employees[i] = new PartTimeEmployee(name, empID, hourlyWage, hoursWorked);
    }
 
//output if type is invalid
    else {
        cout << "Invalid employee type! Skipping this entry." << endl;
        i--;
    }
}

//outputting employee details
cout << "\nEmployee Details and Salaries:" << endl;
for (int i=0; i < emps; i++) {
    employees[i]->printDetails();
    employees[i]->calculateSalary();
}

//freeing dynamically allocated memory
for (int i=0; i < emps; i++) {
    delete employees[i];
}

return 0;
}
