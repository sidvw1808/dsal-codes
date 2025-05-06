#include <iostream>
#include <list>
#include <string>
using namespace std;

const int SIZE = 10;

template <typename K, typename V>
struct KeyValuePair {
    K key;
    V value;
    KeyValuePair(K k, V v) : key(k), value(v) {}
};

template <typename K, typename V>
class Dictionary {
private:
    list<KeyValuePair<K, V> > table[SIZE];

    int hashFunc(K key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++)
            sum += key[i];
        return sum % SIZE;
    }

public:
    void insert(K key, V value) {
        int index = hashFunc(key);

        typename list<KeyValuePair<K, V> >::iterator it;
        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                it->value = value;
                return;
            }
        }

        table[index].push_back(KeyValuePair<K, V>(key, value));
    }

    bool find(K key) {
        int index = hashFunc(key);

        typename list<KeyValuePair<K, V> >::iterator it;
        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                cout << "Value: " << it->value << endl;
                return true;
            }
        }

        cout << "Key not found!" << endl;
        return false;
    }

    void deleteKey(K key) {
        int index = hashFunc(key);
        typename list<KeyValuePair<K, V> >::iterator it;

        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                cout << "Key deleted!" << endl;
                return;
            }
        }
        cout << "Key not found!" << endl;
    }
};

int main() {
    Dictionary<string, string> dict;
    int choice;
    string key, value;

    while (true) {
        cout << "\nDictionary Operations\n";
        cout << "1. Insert\n2. Find\n3. Delete\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dict.insert(key, value);
                break;
            case 2:
                cout << "Enter key to find: ";
                cin >> key;
                dict.find(key);
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.deleteKey(key);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}

