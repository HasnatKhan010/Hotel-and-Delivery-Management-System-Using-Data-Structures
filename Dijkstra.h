#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "Heap.h"
#include "Display.h"

// Helper struct for Priority Queue
struct DistPair {
    int vertex;
    int distance;

    DistPair(int v, int d) : vertex(v), distance(d) {}
    DistPair() : vertex(-1), distance(0) {}

    // Overload operators for Heap (Min-Heap uses <, so we want smaller distance to be "smaller")
    bool operator<(const DistPair& other) const {
        return distance < other.distance;
    }
    
    bool operator>(const DistPair& other) const {
        return distance > other.distance;
    }
    
    bool operator==(const DistPair& other) const {
        return distance == other.distance;
    }
};

class Dijkstra {
public:
    static void findShortestPath(Graph& g, int src, int dest) {
        int V = g.getNumVertices();
        int* dist = new int[V];
        int* parent = new int[V];
        bool* visited = new bool[V];

        for (int i = 0; i < V; i++) {
            dist[i] = 2147483647; // INT_MAX
            parent[i] = -1;
            visited[i] = false;
        }

        dist[src] = 0;
        Heap<DistPair> pq;
        pq.insert(DistPair(src, 0));

        while (!pq.isEmpty()) {
            DistPair current = pq.extractMin();
            int u = current.vertex;

            if (visited[u]) continue;
            visited[u] = true;

            if (u == dest) break; // Found destination

            LinkedList<Edge>& adj = g.getAdjList(u);
            Node<Edge>* temp = adj.getHead();
            while (temp) {
                int v = temp->data.dest;
                int weight = temp->data.weight;

                if (!visited[v] && dist[u] != 2147483647 && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.insert(DistPair(v, dist[v]));
                }
                temp = temp->next;
            }
        }

        // Display path
        if (dist[dest] == 2147483647) {
            Display::printError("No path exists.");
        } else {
            std::cout << "Shortest Distance: " << dist[dest] << "\nPath: ";
            printPath(parent, dest);
            std::cout << "\n";
        }

        delete[] dist;
        delete[] parent;
        delete[] visited;
    }

private:
    static void printPath(int parent[], int j) {
        if (parent[j] == -1) {
            std::cout << j;
            return;
        }
        printPath(parent, parent[j]);
        std::cout << " -> " << j;
    }
};

#endif
