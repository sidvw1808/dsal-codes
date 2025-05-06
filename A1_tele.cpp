#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

class LinearProbing {
    string names[SIZE];
    string phones[SIZE];

public:
    int insert(string name, string phone) {
        int index = hashFunc(name);
        int comparisons = 1;

        while (!names[index].empty()) {
            index = (index + 1) % SIZE;
            comparisons++;
        }
        names[index] = name;
        phones[index] = phone;
        return comparisons;
    }

    int search(string name) {
        int index = hashFunc(name);
        int comparisons = 1;

        while (!names[index].empty()) {
            if (names[index] == name) {
                cout << "Phone (Linear): " << phones[index] << endl;
                return comparisons;
            }
            index = (index + 1) % SIZE;
            comparisons++;
            if (comparisons > SIZE) break;
        }
        cout << "Not found in Linear Probing.\n";
        return comparisons;
    }

private:
    int hashFunc(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum += key[i];
        }
        return sum % SIZE;
    }
};

class QuadraticProbing {
    string names[SIZE];
    string phones[SIZE];

public:
    int insert(string name, string phone) {
        int index = hashFunc(name);
        int comparisons = 1;
        int i = 1;

        while (!names[index].empty()) {
            index = (index + i * i) % SIZE;
            i++;
            comparisons++;
        }
        names[index] = name;
        phones[index] = phone;
        return comparisons;
    }

    int search(string name) {
        int index = hashFunc(name);
        int comparisons = 1;
        int i = 1;

        while (!names[index].empty()) {
            if (names[index] == name) {
                cout << "Phone (Quadratic): " << phones[index] << endl;
                return comparisons;
            }
            index = (index + i * i) % SIZE;
            i++;
            comparisons++;
            if (comparisons > SIZE) break;
        }
        cout << "Not found in Quadratic Probing.\n";
        return comparisons;
    }

private:
    int hashFunc(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum += key[i];
        }
        return sum % SIZE;
    }
};

int main() {
    LinearProbing lp;
    QuadraticProbing qp;

    int n;
    cout << "Enter number of clients: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string name, phone;
        cout << "Enter name and phone: ";
        cin >> name >> phone;
        lp.insert(name, phone);
        qp.insert(name, phone);
    }

    for (int i = 0; i < 3; i++) {
        string name;
        cout << "Enter name to search: ";
        cin >> name;

        int lp_comp = lp.search(name);
        int qp_comp = qp.search(name);

        cout << "Comparisons: Linear = " << lp_comp << ", Quadratic = " << qp_comp << "\n\n";
    }

    return 0;
}

