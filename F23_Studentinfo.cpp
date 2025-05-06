#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
using namespace std;

struct Student {
    int roll;
    string name;
    string division;
    string address;
};


void addStudent() {
    Student s;
    ofstream outFile("students.txt", ios::app);  

    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Division: ";
    getline(cin, s.division);

    cout << "Enter Address: ";
    getline(cin, s.address);

    outFile << s.roll << "," << s.name << "," << s.division << "," << s.address << endl;
    outFile.close();

    cout << "Student record added successfully.\n";
}


void displayStudent() {
    int searchRoll;
    cout << "Enter roll number to search: ";
    cin >> searchRoll;

    ifstream inFile("students.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        int roll;
        string name, division, address;

        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);

        string rollStr = line.substr(0, pos1);
        stringstream ss(rollStr);
        ss >> roll;

        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        division = line.substr(pos2 + 1, pos3 - pos2 - 1);
        address = line.substr(pos3 + 1);

        if (roll == searchRoll) {
            cout << "\nStudent Found:\n";
            cout << "Roll Number: " << roll << endl;
            cout << "Name: " << name << endl;
            cout << "Division: " << division << endl;
            cout << "Address: " << address << endl;
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cout << "Student with roll number " << searchRoll << " not found.\n";
    }
}


void deleteStudent() {
    int deleteRoll;
    cout << "Enter roll number to delete: ";
    cin >> deleteRoll;

    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        size_t pos = line.find(",");
        string rollStr = line.substr(0, pos);
        int roll;
        stringstream ss(rollStr);
        ss >> roll;

        if (roll != deleteRoll) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "Student record deleted successfully.\n";
    } else {
        cout << "Student with roll number " << deleteRoll << " not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

