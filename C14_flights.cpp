#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int adj_mat[50][50] = {0};
int visited[50] = {0};

void dfs(int s, int n, string arr[])
{
    visited[s] = 1;
    cout << arr[s] << " ";
    for (int i = 0; i < n; i++)
    {
        if (adj_mat[s][i] && !visited[i])
            dfs(i, n, arr);
    }
}

void bfs(int s, int n, string arr[])
{
    bool visited_local[50] = {0};
    int v;
    queue<int> bfsq;

    cout << arr[s] << " ";
    bfsq.push(s);
    visited_local[s] = true;

    while (!bfsq.empty())
    {
        v = bfsq.front();
        bfsq.pop();

        for (int i = 0; i < n; i++)
        {
            if (adj_mat[v][i] && !visited_local[i])
            {
                cout << arr[i] << " ";
                visited_local[i] = true;
                bfsq.push(i);
            }
        }
    }
}

void displayGraph(int n, string cities[])
{
    cout << "\nAdjacency Matrix (Flight Distance Map):\n\n\t";
    for (int i = 0; i < n; i++)
        cout << cities[i] << "\t";
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << cities[i] << "\t";
        for (int j = 0; j < n; j++)
            cout << adj_mat[i][j] << "\t";
        cout << endl;
    }
}

int getCityIndex(string cities[], int n, string name)
{
    for (int i = 0; i < n; i++)
    {
        if (cities[i] == name)
            return i;
    }
    return -1;
}

bool isConnected(int n)
{
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
            return false;
    }
    return true;
}

int main()
{
    int n;

    cout << "Enter number of cities: ";
    cin >> n;
    cin.ignore();

    string cities[50];

    cout << "\nEnter names of the cities:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "City #" << i << ": ";
        getline(cin, cities[i]);
    }

    cout << "\nYour cities are:\n";
    for (int i = 0; i < n; i++)
        cout << "City #" << i << ": " << cities[i] << endl;

    cout << "\nEnter the distance (flight time/fuel cost) between cities:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            cout << "Distance between " << cities[i] << " and " << cities[j] << " (enter 0 if no direct flight): ";
            cin >> adj_mat[i][j];
            adj_mat[j][i] = adj_mat[i][j];
        }
    }

    cin.ignore();
    string startCity;
    cout << "\nEnter starting city name: ";
    getline(cin, startCity);

    int u = getCityIndex(cities, n, startCity);
    if (u == -1)
    {
        cout << "Invalid city name. Exiting." << endl;
        return 0;
    }

    cout << "\nDepth First Search (DFS) starting from " << cities[u] << ": ";
    dfs(u, n, cities);
    cout << endl;

    cout << "Breadth First Search (BFS) starting from " << cities[u] << ": ";
    bfs(u, n, cities);
    cout << endl;

    displayGraph(n, cities);

    if (isConnected(n))
        cout << "\nThe graph is CONNECTED (All cities can reach each other)." << endl;
    else
        cout << "\nThe graph is NOT connected (Some cities cannot reach each other)." << endl;

    return 0;
}

