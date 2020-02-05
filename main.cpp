#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Employee
{
    int empID;
    string firstname;
    string lastname;
    int storeID;
    int salary;
    string daysWorked;
    int totalDaysWorked;
    string salesTotal;

    bool operator >(const Employee & another)
    {
        return this->empID > another.empID;
    }


    bool operator <(const Employee &another)
    {
        return this->empID < another.empID;
    }

    void printEmployee()
    {
        cout << this->empID << endl;
        cout << this->firstname << endl;
        cout << this->lastname << endl;
        cout << this->storeID << endl;
        cout << this->salary << endl;
        cout << this->totalDaysWorked << endl;
        cout << this->salesTotal << endl << endl;
    }
};

vector<int> stringToVector(string str)
{
    vector<int> v;
    stringstream ss(str);
    int temp;
    while (ss >> temp)
        v.push_back(temp);
    return v;
}

static inline std::string &rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

int genID(int limit, Employee * employees)
{
    int empID;
    while(true)
    {
        empID = (rand()%999999)+100000;

        bool unique = true;
        for(int i = 0; i < limit; i++)
        {
            if(employees[i].empID == empID)
            {
                unique = false;
            }
        }
        if(unique)
        {
            break;
        }
    }
    return empID;
}

string genName(int min_length, int max_length)
{
    size_t len = rand()%max_length+min_length;
    string random_str;
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for (size_t n = 0; n < len; n++)
    {
        int key = rand() % (int) (sizeof charset - 1);
        random_str += charset[key];
    }
    return random_str;
}

string genDaysWorked()
{
    string daysWorked;
    for(int i = 0; i < 12; i++)
    {
        std::stringstream ss;
        ss << rand()%22;
        daysWorked += ss.str() + " ";
    }
    rtrim(daysWorked);
    return daysWorked;
}

string genSalesTotal(int salary, string daysWorked)
{
    vector<int> days = stringToVector(daysWorked);
    string salesTotal;
    for(int i = 0; i < 12; i++)
    {
        std::stringstream ss;
        if(salary < 60000)
        {
            ss << ((rand()%(15000-1000+1))+1000) * days[i];
        }
        else
        {
            ss << ((rand()%(20000-3000+1))+3000) * days[i];
        }

        salesTotal += ss.str() + " ";
    }
    rtrim(salesTotal);
    return salesTotal;
}

int getTotalDaysWorked(string daysWorked)
{
    vector<int> days = stringToVector(daysWorked);
    int total = 0;
    for(int i = 0; i < 12; i++)
    {
        total += days[i];
    }
    return total;
}

int genStoreID()
{
    return (rand()%(9999-1000+1))+1000;
}

int genSalary()
{
    return (rand()%(100000-20000+1)) + 20000;
}

void sortEmployees(Employee e[], int n)
{
    sort(e, e+n);
}

void printToFile(Employee e[], int n, const string filename)
{
    cout << "Printing output file" << endl;
    ofstream myfile;
    myfile.open (filename.c_str());

    for(int i = 0; i < n; i++)
    {
        myfile << e[i].empID << ", ";
        myfile << e[i].firstname << ", ";
        myfile << e[i].lastname << ", ";
        myfile << e[i].storeID << ", ";
        myfile << e[i].salary << ", ";
        myfile << e[i].totalDaysWorked << ", ";
        myfile << e[i].salesTotal << endl;
    }
    myfile.close();
}

int main(int argc, char const *argv[])
{
    srand((unsigned)time(0));


    Employee employees[5000];
    cout << "Generating data" << endl;
    for(int i = 0; i < 5000; i++)
    {
        employees[i].empID = genID(i, employees);
        employees[i].firstname = genName(8, 16);
        employees[i].lastname = genName(8, 16);
        employees[i].storeID = genStoreID();
        employees[i].salary = genSalary();
        employees[i].daysWorked = genDaysWorked();
        employees[i].totalDaysWorked = getTotalDaysWorked(employees[i].daysWorked);
        employees[i].salesTotal = genSalesTotal(employees[i].salary, employees[i].daysWorked);
    }

    sortEmployees(employees, 5000);
    string out_filename = "data.txt";
    printToFile(employees, 5000, out_filename);
    return 0;
}
