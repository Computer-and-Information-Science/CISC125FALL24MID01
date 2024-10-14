#include <iostream>

using namespace std;


  
  
  //abstract class
  class Employee
  {
    protected:
      string name;
      int empID;
      
    public:
    //constructor to access protected members
      Employee(string _name, int _empID) : name(_name), empID(_empID) {} 
      
    //pure virtual functions
      virtual void printDetails() const = 0;
      virtual double calculateSalary() const = 0;
      
    //destructor
      virtual ~Employee() {}
  };
  
  //derived class
  class FullTimeEmployee : public Employee
  {
    private:
      double basicSalary;
      
    public:
    //constructor
      FullTimeEmployee(string _name, int _empID, double _basicSalary) : Employee(_name, _empID), basicSalary(_basicSalary) {}
      
    //override functions to display details and salary
      void printDetails() const
      {
        cout << "--FullTime Employee--" << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << empID << endl;
        cout << "Salary: " << basicSalary << endl;
      };
      
      double calculateSalary() const
      {
        return basicSalary;
      };
  };
      
  //derived class
  class PartTimeEmployee : public Employee
  {
    private:
      double hourlyWage;
      int hoursWorked;
      
    public:
    //constructor
    PartTimeEmployee(string _name, int _empID, double _hourlyWage, int _hoursWorked) : Employee(_name, _empID), hourlyWage(_hourlyWage), hoursWorked(_hoursWorked) {}
    
    //override functions to display details and salary
      void printDetails() const
      {
        cout << "--PartTime Employee--" << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << empID << endl;
        cout << "Salary: " << calculateSalary() << endl;
      };
      
      double calculateSalary() const
      {
          return (hourlyWage * hoursWorked);
      };
      
    };
      
 
int main() { 
  
  //asks user for amount of employees
  int employeeAmt;
  cout << "Enter how many employees: " << endl;
  cin >> employeeAmt;
  
  //dynamic array of the amount of employees
  Employee* employees[employeeAmt];
  
  //input information based on type of employee
  for (int i = 0; i < employeeAmt; i++)
  {
    string name;
    int empID;
    int schedule;
    
    cout << "--Employee " << i + 1 << "--" << endl;
    cout << "Enter Name: " << endl;
    cin >> name;
    cout << "Enter ID: " << endl;
    cin >> empID;
    cout << "Enter Schedule (1 for Full-Time, 2 for Part-Time): " << endl;
    cin >> schedule;
    
    if (schedule == 1)
    {
      double basicSalary;
      
      cout << "Enter Salary: " << endl;
      cin >> basicSalary;
      
      employees[i] = new FullTimeEmployee(name, empID, basicSalary);
    }
    
    else if (schedule == 2)
    {
      double hourlyWage;
      int hoursWorked;
      
      cout << "Enter hourly wage: " << endl;
      cin >> hourlyWage;
      cout << "Enter hours worked: " << endl;
      cin >> hoursWorked;
      
      employees[i] = new PartTimeEmployee(name, empID, hourlyWage, hoursWorked);
    }
    
    else
    {
      cout << "Please enter 1 or 2" << endl;
    }
    
    
    for (int i = 0; i < employeeAmt; i++)
    {
      employees[i]->printDetails();
    }
    
    
    
    //deallocating
    for (int i = 0; i < employeeAmt; i++)
    {
      delete employees[i];
    }
    
    
    
    
    return 0;
    
  }
  
}