#include "dijkstras.h"
#include <queue>
#include <limits>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF); // Initialize distances to infinity
    distances[source] = 0; // Distance to source is 0
    previous.assign(G.numVertices, -1); // Initialize previous nodes to -1

    // Min-heap priority queue: (distance, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source}); // Start with the source vertex

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();
        if (cost > distances[u]) continue;

        // Explore neighbors of u
        for (const Edge& e : G[u]) {
            int v = e.dst; // Neighbor vertex
            int weight = e.weight; // Edge weight

            // Relaxation step
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight; // Update distance
                previous[v] = u; // Update previous node
                pq.push({distances[v], v}); // Enqueue the neighbor
            }
        }
    }

    return distances; // Return the shortest distances
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path; // No path exists

    // Backtrack from destination to source
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }

    // Reverse to get path from source to destination
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size()) cout << " "; // Add space after each vertex
    }
    cout << "\nTotal cost is " << total << endl; // Add a newline after the total cost
}