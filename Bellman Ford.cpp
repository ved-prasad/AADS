
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const long long INF = LLONG_MAX / 4;

struct Edge {
    int src, dest;
    long long weight;
};

void bellmanFord(int V, int E, vector<Edge>& edges, int src) {
    vector<long long> dist(V, INF);

    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        bool updated = false;

        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            long long weight = edges[j].weight;

            if (dist[u] != INF) {
                __int128 candidate =
                    (__int128)dist[u] + weight;

                if (candidate < dist[v]) {
                    if (candidate < -INF) {
                        cout << "Distance is out of range.\n";
                        return;
                    }

                    dist[v] = (long long)candidate;
                    updated = true;
                }
            }
        }

        if (!updated) {
            break;
        }
    }

    // Check for negative-weight cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        long long weight = edges[j].weight;

        if (dist[u] != INF) {
            __int128 candidate =
                (__int128)dist[u] + weight;

            if (candidate < dist[v]) {
                cout << "Graph contains a negative weight cycle!"
                     << endl;
                return;
            }
        }
    }

    // Display shortest distances
    cout << "Vertex\tDistance from Source ("
         << src << ")" << endl;

    for (int i = 0; i < V; i++) {
        cout << i << "\t";

        if (dist[i] == INF) {
            cout << "INF" << endl;
        }
        else {
            cout << dist[i] << endl;
        }
    }
}

int main() {
    int V = 5;
    int E = 8;

    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    int source = 0;

    if (V <= 0 || source < 0 || source >= V) {
        cout << "Invalid input." << endl;
        return 1;
    }

    for (const Edge& e : edges) {
        if (e.src < 0 || e.src >= V ||
            e.dest < 0 || e.dest >= V) {
            cout << "Invalid edge vertices." << endl;
            return 1;
        }
    }

    bellmanFord(V, E, edges, source);

    return 0;
}
