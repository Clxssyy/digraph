/*
    Digraph.cpp

    Implementation file for Digraph class
*/

#include "Digraph.hpp"

const int INF = 9999999;

// Accessor for numberOfVertices
unsigned int Digraph::noVertices() {
    return numberOfVertices;
}

// Accessor for numberOfEdges
unsigned int Digraph::noEdges() {
    return numberOfEdges;
}

// Resets edges (sets them to -1)
void Digraph::resetEdges() {
    // Set all elements of the distance matrix to -1
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            distMatrix[i][j] = -1;
        }
    }
}

// Adds an edge (path between two cities)
void Digraph::addEdge(int source, int dest, int wt) {
    // Check for invalid source or destination index
    if (source < 0 || source >= numberOfVertices || dest < 0 || dest >= numberOfVertices) {
        return;
    }

    distMatrix[source][dest] = wt;
    numberOfEdges++;
}

// Deletes an edge (set it to -1)
void Digraph::delEdge(int source, int dest) {
    // Check for invalid source or destination index
    if (source < 0 || source >= numberOfVertices || dest < 0 || dest >= numberOfVertices) {
        return;
    }

    // Checks to see if the edge exists
    if (distMatrix[source][dest] != -1) {
        distMatrix[source][dest] = -1;
        numberOfEdges--;
    }
}

// Returns an edge or -1 if not an edge
int Digraph::isEdge(int source, int dest) {
    // Checks for invalid source or destination index
    if (source < 0 || source >= numberOfVertices || dest < 0 || dest >= numberOfVertices) {
        return -1;
    }

    return distMatrix[source][dest];
}

// Dijkstra's algorithm to find the shortest path and output that path
int Digraph::dijkstra(int source, int dest) {
    std::vector<int> dist(numberOfVertices, INF);
    std::vector<int> prev(numberOfVertices, -1);
    std::vector<bool> visited(numberOfVertices, false);

    dist[source] = 0;

    for (int count = 0; count < numberOfVertices-1; count++) {
        int u = -1;

        for (int i = 0; i < numberOfVertices; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = true;

        for (int v = 0; v < numberOfVertices; v++) {
            if (distMatrix[u][v] != -1 && dist[u] != INF && dist[u] + distMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + distMatrix[u][v];
                prev[v] = u;
            }
        }
    }

    // No path found
    if (dist[dest] == INF) {
        std::cout << "No path exists between source and destination" << endl;
        return -1;
    }

    int current = dest;
    std::vector<int> path;

    // Output the shortest path found
    std::cout << vertex[source]->getName() << " to " << vertex[dest]->getName() << '\n';

    while (current != -1) {
        path.insert(path.begin(), current);
        current = prev[current];
    }

    std::cout << "\nPath:\n";

    for (int i = 0; i < path.size(); i++) {
        std::cout << vertex[path[i]]->getName() << '\n';
    }

    std::cout << "\nDistance: " << dist[dest] << '\n';

    return dist[dest];
}
