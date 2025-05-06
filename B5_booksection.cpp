#include <iostream>
#include <string>
using namespace std;

struct node // Node Declaration
{
    string label;
    int ch_count;
    struct node *child[10];
} *root;

class GT // Class Declaration
{
public:
    void create_tree();
    void display(node *r1);
    GT()
    {
        root = NULL;
    }
};

void GT::create_tree()
{
    int tchapters, i, j, k;
    root = new node;
    
    cout << "Enter name of book : ";
    cin.ignore(); // Clear input buffer
    getline(cin, root->label);
    
    cout << "Enter number of chapters in book : ";
    cin >> tchapters;
    root->ch_count = tchapters;
    
    for (i = 0; i < tchapters; i++)
    {
        root->child[i] = new node;
        cout << "Enter the name of Chapter " << i + 1 << " : ";
        cin.ignore(); // Clear input buffer
        getline(cin, root->child[i]->label);
        
        cout << "Enter number of sections in Chapter : " << root->child[i]->label << " : ";
        cin >> root->child[i]->ch_count;
        
        for (j = 0; j < root->child[i]->ch_count; j++)
        {
            root->child[i]->child[j] = new node;
            cout << "Enter Name of Section " << j + 1 << " : ";
            cin.ignore(); // Clear input buffer
            getline(cin, root->child[i]->child[j]->label);
            
            cout << "Enter number of subsections in Section " << root->child[i]->child[j]->label << " : ";
            cin >> root->child[i]->child[j]->ch_count;
            
            for (k = 0; k < root->child[i]->child[j]->ch_count; k++)
            {
                root->child[i]->child[j]->child[k] = new node;
                cout << "Enter Name of Subsection " << k + 1 << " : ";
                cin.ignore(); // Clear input buffer
                getline(cin, root->child[i]->child[j]->child[k]->label);
                
                // Initialize subsection's child count to 0
                root->child[i]->child[j]->child[k]->ch_count = 0;
            }
        }
    }
}

void GT::display(node *r1)
{
    int i, j, k, tchapters;
    if (r1 != NULL)
    {
        cout << "\n-----Book Hierarchy---";
        cout << "\n Book title : " << r1->label;
        tchapters = r1->ch_count;
        
        for (i = 0; i < tchapters; i++)
        {
            cout << "\nChapter " << i + 1;
            cout << " : " << r1->child[i]->label;
            
            cout << "\nSections : ";
            for (j = 0; j < r1->child[i]->ch_count; j++)
            {
                cout << "\n  " << j + 1 << ". " << r1->child[i]->child[j]->label;
                
                cout << "\n     Subsections : ";
                for (k = 0; k < r1->child[i]->child[j]->ch_count; k++)
                {
                    cout << "\n     " << k + 1 << ". " << r1->child[i]->child[j]->child[k]->label;
                }
            }
        }
    }
    cout << endl;
}

int main()
{
    int choice;
    GT gt;
    while (1)
    {
        cout << "-----------------" << endl;
        cout << "Book Tree Creation" << endl;
        cout << "-----------------" << endl;
        cout << "1.Create" << endl;
        cout << "2.Display" << endl;
        cout << "3.Quit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        
        switch (choice)
        {
        case 1:
            gt.create_tree();
            break; // Added missing break statement
        case 2:
            gt.display(root);
            break;
        case 3:
            cout << "Thanks for using this program!!!" << endl;
            exit(1);
        default:
            cout << "Wrong choice!!!" << endl;
        }
    }
    return 0;
}
