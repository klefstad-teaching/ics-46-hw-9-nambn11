#include "dijkstras.h"

int main() {
    Graph G;

    string filename = "small.txt";  
    try {
        file_to_graph(filename, G);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    int source = 0;  
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    for (int i = 0; i < G.numVertices; ++i) {
        if (distances[i] == INF) {
            cout << "No path from " << source << " to " << i << endl;
        } else {
            vector<int> path = extract_shortest_path(distances, previous, i);
            print_path(path, distances[i]);
        }
    }

    return 0;
}
