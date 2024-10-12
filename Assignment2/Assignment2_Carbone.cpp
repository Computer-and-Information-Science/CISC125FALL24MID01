#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************/
//Abstract employee class/
/************************/
class Employee {
    protected:
        string name;
        int eID;
    public:
        Employee(string eName, int eId) : name(eName), eID(eId){}

        virtual void printDetails() const = 0;  //virtual function for employee information
        virtual double calcSal() const = 0;     //virtual function for salary calculation
        virtual ~Employee(){}                   //virtual destructor
};

/*************************/
//Full time employee class/
/*************************/
class Fulltime : public Employee{
    private:
        double baseSal;
    public:
        Fulltime(string eName, int eId, double sal) : Employee(eName, eId), baseSal(sal){}
        void printDetails() const override{ //By setting print details to an override, we can continuously use the previously defined virtual void function.
            cout << "Full-time Employee\n";
            cout << "Name:        " << name << endl;
            cout << "ID#:         " << eID << endl;
            cout << "Base Salary: " << baseSal << endl;
        }
        double calcSal() const override {
            return baseSal;
        }
};

/*************************/
//Part time employee class/
/*************************/
class Parttime : public Employee{
    private:
        double hrWage;
        int hrsWrk;
    public:
    Parttime(string eName, int eId, double wage, int hrs) : Employee(eName, eId), hrWage(wage), hrsWrk(hrs){}
    void printDetails() const override{
        cout << "Part-Time Employee\n";
        cout << "Name:         " << name << endl;
        cout << "ID#:          " << eID << endl;
        cout << "Wage:        $" << hrWage << endl;
        cout << "Hours Worked: " << hrsWrk << endl;
    }
    double calcSal() const override{
        return hrWage * hrsWrk;
    }
};

int main() {
    int empNum;
    cout << "Enter amount of employees: ";
    cin >> empNum;
    vector<Employee*> employees; //Vector for employee pointer storage

    for(int i = 0; i < empNum; ++i){
        string name;
        int eID;
        int type;

        cout << "Enter employee details " << i + 1 << endl;
        cout << "Name: ";
        cin >> name;
        cout << "\nEmployee ID: ";
        cin >> eID;
        cout << "\nFull time (1) or Part-time (2): ";
        cin >> type;

        if( type == 1) {
            double salary;
            cout << "\nEnter salary: ";
            cin >> salary;
            employees.push_back(new Fulltime(name, eID, salary));
        }
        else if (type == 2) {
            double wage;
            int hrs;
            cout << "Enter wage: ";
            cin >> wage;
            cout << "\nEnter hours worked: ";
            cin >> hrs;
            employees.push_back(new Parttime(name, eID, wage, hrs));
        }
        else {
            cout << "Please enter valid type.\n";
        }
    }
    //Displays information and calculates salaries
    for (int i = 0; i < empNum; ++i){
        employees[i]->printDetails();
        cout << "Salary: $" << employees[i]->calcSal() << endl;
    }
    //Freeing dynamically allocated memory
    for (int i = 0; i < empNum; ++i){
        delete employees[i];
    }
    
    return 0;
};