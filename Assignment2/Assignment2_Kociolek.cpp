#include <iostream>
#include <string>

using namespace std;


//base/abstract class for employee
class Employee {
    protected:
        string name;
        int eID;
    public:
        Employee(string eName, int eId) : name(eName), eID(eId){}

        virtual void printDetails() const = 0;  //virtual function employee information
        virtual double calcSal() const = 0;     //virtual function salary calculation
        virtual ~Employee(){}                   //virtual destructor
};

//full time employee class

class Fulltime : public Employee{
    private:
        double baseSalary;
    public:
        Fulltime(string eName, int eId, double sal) : Employee(eName, eId), baseSalary(sal){}
        void printDetails() const override{ 
            cout << "\nFull-time Employee\n";
            cout << "Name:        " << name << endl;
            cout << "ID#:         " << eID << endl;
            cout << "Base Salary: " << baseSalary << endl;
        }
        double calcSal() const override {
            return baseSalary;
        }
};




//part time employee class
class Parttime : public Employee{
    private:
        double hrWage;
        int hrsWrk;
    public:
    Parttime(string eName, int eId, double wage, int hrs) : Employee(eName, eId), hrWage(wage), hrsWrk(hrs){}
    void printDetails() const override{
        cout << "\nPart-Time Employee:        \n";
        cout << "Name:         " << name << endl;
        cout << "ID#:          " << eID << endl;
        cout << "Wage:        $" << hrWage << endl;
        cout << "Hours Worked: " << hrsWrk << endl;
    }
    double calcSal() const override{
        return hrWage * hrsWrk;
    }
};

//main program
int main() {
  int numEmployees;
  cout << "Enter the number of employees: ";
  cin >> numEmployees;

  Employee* employees[numEmployees]; // Array of Employees

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
          employees[i] = new Fulltime(name, empID, basicSalary); 
        
      } else if (empType == 2) {
          double hourlyWage;
          int hoursWorked;
          cout << "Enter hourly wage: ";
          cin >> hourlyWage;
          cout << "Enter hours worked: ";
          cin >> hoursWorked;
          employees[i] = new Parttime(name, empID, hourlyWage, hoursWorked);
        
      } else {
          cout << "Invalid employee type!" << endl;
          i--; // Decrement counter to retry
      }
  }

  //Displays information and calculates salaries
      for (int i = 0; i < numEmployees; ++i){
          employees[i]->printDetails();
          cout << "Salary: $" << employees[i]->calcSal() << endl;
      }
      //Freeing dynamically allocated memory
      for (int i = 0; i < numEmployees; ++i){
          delete employees[i];
      }
      
    return 0;
  };