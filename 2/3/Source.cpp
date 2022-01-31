#include <iostream>
#include <list>
#include<vector>
using namespace std;

class Edge { // Class edge to public so it can be accessed 
public:
    int start; // Start of path
    int end; // End of path
    int path; //Value
    Edge() {}
    Edge(int start, int end, int path) { //Edge is used to get values 
        this->start = start;
        this->end = end;
        this->path = path;
    }
};

class Graph { //This will store the shortest distance of the path and also construct it 
private:
    list<Edge> edge_list;
    int nodes;
    vector<vector<int>> arr;
    vector<vector<int>> next;

public:
    Graph() {}
    Graph(int n) {
        nodes = n;
        arr.resize(n);
        next.resize(n);

        for (int i = 0; i < n; i++) {
            arr[i].resize(n, 1000); //Max set to 1000 as this is the highest point it can go
            next[i].resize(n, -1);
        }
    }
    void AddEdge(int start, int end, int path, bool isbidirectional) { // Can be accesed from any way
        Edge e(start, end, path);
        edge_list.push_back(e);
        if (isbidirectional) {
            Edge e(end, start, path);
            edge_list.push_back(e);
        }
    }
    void Floyd_Warshall() {

        for (int i = 0; i < nodes; i++) {
            arr[i][i] = 0;
            next[i][i] = i;
        };

        for (auto edge : edge_list) {
            int u = edge.start;
            int v = edge.end;
            arr[u][v] = edge.path;
            next[u][v] = v;
        };

        for (int k = 0; k < nodes; k++) {
            for (int i = 0; i < nodes; i++) {
                for (int j = 0; j < nodes; j++) {
                    if (arr[i][j] > arr[i][k] + arr[k][j]) {
                        arr[i][j] = arr[i][k] + arr[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
        cout << "This is the shortest distance between nodes if the path exists " << endl;
        for (int u = 0; u < nodes; u++) {
            for (int v = u + 1; v < nodes; v++) {
                cout << u << " - " << v << " ) : " << arr[u][v] << endl;
                PathConstruction(u, v);
            }
        }
    }
    void PathConstruction(int start, int end, int path) {

        cout << "Path exists between: " << start << " and " << end << " : "; //If the path exists it will output this message with the path

        if (next[start][end] == -1) {
            cout << "No path" << endl; //If no path exists this will be output 
        }
        else {
            vector<int> path;
            path.push_back(start);

            while (start != end) {
                start = next[start][end];
                path.push_back(start);
            }

            for (auto& it : path)
                cout << it << " ";
            cout << endl;
        }
    }
};

int main() { //This is the nodes with values Nodes = { A, B, C, D, E, F, G, H }

    Graph g(7);

    // Edges from node 0 (H)
    g.AddEdge(0, 2, 14, true);
    g.AddEdge(0, 3, 10, true);
    g.AddEdge(0, 4, 5, true);
    g.AddEdge(0, 5, 20, true);
    g.AddEdge(0, 1, 4, true);
    g.AddEdge(0, 7, 21, true);
    g.AddEdge(0, 6, 30, true);

    // Edges from node 1 (A)
    g.AddEdge(1, 2, 12, true);
    g.AddEdge(1, 0, 4, true);
    g.AddEdge(1, 5, 10, true);
    g.AddEdge(1, 6, 11, true);

    // Edges from node 2 (D)
    g.AddEdge(2, 0, 14, true);
    g.AddEdge(2, 1, 12, true);
    g.AddEdge(2, 5, 8, true);
    g.AddEdge(2, 6, 24, true);
    g.AddEdge(2, 7, 16, true);
    g.AddEdge(2, 3, 17, true);

    // Edges from node 3 (C)
    g.AddEdge(3, 0, 10, true);
    g.AddEdge(3, 2, 17, true);
    g.AddEdge(3, 6, 13, true);
    g.AddEdge(3, 4, 8, true);

    // Edges from node 4 (E)
    g.AddEdge(4, 0, 5, true);
    g.AddEdge(4, 3, 8, true);
    g.AddEdge(4, 6, 11, true);
    g.AddEdge(4, 7, 8, true);

    // Edges from node 5 (B)
    g.AddEdge(5, 0, 20, true);
    g.AddEdge(5, 1, 10, true);
    g.AddEdge(5, 2, 8, true);

    // Edges from node 6 (G)
    g.AddEdge(6, 1, 11, true);
    g.AddEdge(6, 2, 24, true);
    g.AddEdge(6, 3, 13, true);
    g.AddEdge(6, 4, 11, true);
    g.AddEdge(6, 0, 30, true);
    g.AddEdge(6, 7, 18, true);

    // Edges from node 7
    g.AddEdge(7, 0, 21, true);
    g.AddEdge(7, 2, 16, true);
    g.AddEdge(7, 6, 18, true);
    g.AddEdge(7, 4, 8, true);

    g.Floyd_Warshall();

    return 0;
}

