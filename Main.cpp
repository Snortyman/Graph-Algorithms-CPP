#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <stack>
#include <algorithm>
#include"Windows.h"
using namespace std;

class Graph {
private:
    int size;
    int numVertices;
    vector<list<int>> adjLists;

public:
    Graph(int vertices) {
        numVertices = vertices;
        size = vertices;
        adjLists.resize(vertices);
    }

    void addEdge(int src, int dest) {
        if (src >= numVertices || dest >= numVertices) return;
        adjLists[src].push_back(dest);
        adjLists[dest].push_back(src);
    }

    void removeEdge(int src, int dest) {
        adjLists[src].remove(dest);
        adjLists[dest].remove(src);
    }

    void addVertex() {
        numVertices++;
        size++;
        adjLists.push_back(list<int>());
        cout << "Вершина " << numVertices - 1 << " добавлена." << endl;
    }

    void removeVertex(int v) {
        size--;
        if (v >= numVertices) return;
        for (int i = 0; i < numVertices; i++) {
            adjLists[i].remove(v);
        }
        adjLists[v].clear();
        cout << "Вершина " << v << " изолирована/удалена из связей." << endl;
    }

    void printGraph() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << ": ";
            for (int neighbor : adjLists[i]) cout << neighbor << " ";
            cout << endl;
        }
    }

    void BFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        cout << "BFS: ";
        while (!q.empty()) {
            int curr = q.front();
            cout << curr << " ";
            q.pop();

            for (int neighbor : adjLists[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void DFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        stack<int> s;

        s.push(startVertex);

        cout << "DFS: ";
        while (!s.empty()) {
            int curr = s.top();
            s.pop();

            if (!visited[curr]) {
                cout << curr << " ";
                visited[curr] = true;
            }

            for (int neighbor : adjLists[curr]) {
                if (!visited[neighbor]) s.push(neighbor);
            }
        }
        cout << endl;
    }

    bool isConnected() {
        if (numVertices == 0) return true;

        vector<bool> visited(numVertices, false);
        queue<int> q;

        q.push(0);
        visited[0] = true;
        int count = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adjLists[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    count++;
                    q.push(v);
                }
            }
        }
        return count == size;
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
  
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    int n, m;
    inputFile >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        inputFile >> u >> v;
        g.addEdge(u, v);
    }
    inputFile.close();

    cout << "--- Исходный граф ---" << endl;
    g.printGraph();

    cout << "\n--- Проверка алгоритмов ---" << endl;
    g.BFS(0);
    g.DFS(0);
    g.removeVertex(2);
    cout << "\n--- Проверка связности ---" << endl;
    if (g.isConnected())
        cout << "Граф является связным." << endl;
    else
        cout << "Граф НЕ является связным." << endl;

    return 0;
}


//Первая строка — количество вершин и ребер, далее — пары вершин, образующих ребро.