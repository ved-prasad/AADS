#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_V = 100;
const int MAX_E = 1000;

int parent[MAX_V];
int rankArr[MAX_V];
int u[MAX_E];
int v[MAX_E];
int weight[MAX_E];
int edgeIndex[MAX_E];

bool compareEdges(int a, int b) {
    return weight[a] < weight[b];
}

int findSet(int i) {
    if (parent[i] == i)
        return i;

    return parent[i] = findSet(parent[i]);
}

void unionSets(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);

    if (rootX != rootY) {
        if (rankArr[rootX] < rankArr[rootY]) {
            parent[rootX] = rootY;
        }
        else if (rankArr[rootX] > rankArr[rootY]) {
            parent[rootY] = rootX;
        }
        else {
            parent[rootY] = rootX;
            rankArr[rootX]++;
        }
    }
}

void kruskalMST(int V, int E) {
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }

    for (int i = 0; i < E; i++) {
        edgeIndex[i] = i;
    }

    sort(edgeIndex, edgeIndex + E, compareEdges);

    int mstWeight = 0;
    int edgesIncluded = 0;

    cout << "\nEdges in the Minimum Spanning Tree:\n";
    cout << "Edge \tWeight\n";

    for (int i = 0; i < E; i++) {
        int idx = edgeIndex[i];
        int src = u[idx];
        int dest = v[idx];
        int w = weight[idx];

        if (findSet(src) != findSet(dest)) {
            cout << src << " - " << dest << "\t" << w << "\n";

            mstWeight += w;
            unionSets(src, dest);
            edgesIncluded++;

            if (edgesIncluded == V - 1) {
                break;
            }
        }
    }

    if (edgesIncluded != V - 1) {
        cout << "\nThe graph is disconnected; a complete MST does not exist.\n";
    }
    else {
        cout << "\nTotal Weight of MST: " << mstWeight << "\n";
    }
}

int main() {
    int V, E;

    cout << "Enter the number of vertices (max " << MAX_V << "): ";
    cin >> V;

    cout << "Enter the number of edges (max " << MAX_E << "): ";
    cin >> E;

    if (V > MAX_V || E > MAX_E || V <= 0 || E < 0) {
        cout << "Invalid number of vertices or edges.\n";
        return 1;
    }

    cout << "Enter each edge as: source destination weight (0-indexed vertices)\n";

    for (int i = 0; i < E; i++) {
        cin >> u[i] >> v[i] >> weight[i];
    }

    kruskalMST(V, E);

    return 0;
}