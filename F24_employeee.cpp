#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct Employee {
    int id;
    string name;
    string designation;
    float salary;

    string toString() const {
        stringstream ss;
        ss << id << "," << name << "," << designation << "," << salary;
        return ss.str();
    }

    static Employee fromString(const string &line) {
        stringstream ss(line);
        string temp;
        Employee e;

        getline(ss, temp, ',');
        stringstream(temp) >> e.id;

        getline(ss, e.name, ',');

        getline(ss, e.designation, ',');

        getline(ss, temp, ',');
        stringstream(temp) >> e.salary;

        return e;
    }
};

// Function to load all employees into memory
vector<Employee> loadEmployees() {
    vector<Employee> list;
    ifstream inFile("employees.txt");
    string line;
    while (getline(inFile, line)) {
        if (!line.empty())
            list.push_back(Employee::fromString(line));
    }
    inFile.close();
    return list;
}

// Function to save all employees back to file in sorted order
void saveEmployees(const vector<Employee> &list) {
    ofstream outFile("employees.txt");
    for (size_t i = 0; i < list.size(); ++i) {
        outFile << list[i].toString() << endl;
    }
    outFile.close();
}

// Add a new employee
void addEmployee() {
    vector<Employee> list = loadEmployees();
    Employee e;

    cout << "Enter Employee ID: ";
    cin >> e.id;
    cin.ignore();

    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i].id == e.id) {
            cout << "Employee ID already exists!\n";
            return;
        }
    }

    cout << "Enter Name: ";
    getline(cin, e.name);

    cout << "Enter Designation: ";
    getline(cin, e.designation);

    cout << "Enter Salary: ";
    cin >> e.salary;

    list.push_back(e);

    // Sort using normal compare function
    for (size_t i = 0; i < list.size(); ++i) {
        for (size_t j = i + 1; j < list.size(); ++j) {
            if (list[i].id > list[j].id) {
                Employee temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    saveEmployees(list);
    cout << "Employee added successfully.\n";
}

// Delete an employee by ID
void deleteEmployee() {
    vector<Employee> list = loadEmployees();
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    bool found = false;
    vector<Employee> newList;

    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i].id != id) {
            newList.push_back(list[i]);
        } else {
            found = true;
        }
    }

    if (found) {
        saveEmployees(newList);
        cout << "Employee deleted successfully.\n";
    } else {
        cout << "Employee not found.\n";
    }
}

// Display a particular employee by ID
void displayEmployee() {
    vector<Employee> list = loadEmployees();
    int id;
    cout << "Enter Employee ID to search: ";
    cin >> id;

    bool found = false;

    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i].id == id) {
            cout << "\nEmployee Found:\n";
            cout << "ID: " << list[i].id << "\nName: " << list[i].name
                 << "\nDesignation: " << list[i].designation
                 << "\nSalary: " << list[i].salary << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << id << " not found.\n";
    }
}

// Main Menu
int main() {
    int choice;
    do {
        cout << "\n--- Employee Information System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: deleteEmployee(); break;
            case 3: displayEmployee(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

