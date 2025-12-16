#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "Heap.h"
#include "Display.h"
#include <string>

using namespace std;

// ============================================================================
// ISLAMABAD SECTOR MAPPING - Connects the map to the algorithms
// ============================================================================
// Sectors are nodes in our graph, representing actual Islamabad locations

static string getSectorName(int id) {
    switch(id) {
        case 0: return "F-6 (Blue Area)";
        case 1: return "F-7 (Jinnah Super)";
        case 2: return "F-8 (Ayub Market)";
        case 3: return "F-10 (Markaz)";
        case 4: return "G-6 (Melody)";
        case 5: return "G-8 (Markaz)";
        case 6: return "G-9 (Markaz)";
        case 7: return "G-10 (Markaz)";
        case 8: return "G-11 (Markaz)";
        case 9: return "I-8 (Markaz)";
        case 10: return "I-10 (Markaz)";
        case 11: return "E-7 (Sector)";
        case 12: return "E-11 (MPCHS)";
        case 13: return "H-8 (Centaurus)";
        case 14: return "H-9 (Sector)";
        default: return "Unknown Sector";
    }
}

// Shorter names for map display
static string getSectorShort(int id) {
    switch(id) {
        case 0: return "F-6";
        case 1: return "F-7";
        case 2: return "F-8";
        case 3: return "F-10";
        case 4: return "G-6";
        case 5: return "G-8";
        case 6: return "G-9";
        case 7: return "G-10";
        case 8: return "G-11";
        case 9: return "I-8";
        case 10: return "I-10";
        case 11: return "E-7";
        case 12: return "E-11";
        case 13: return "H-8";
        case 14: return "H-9";
        default: return "???";
    }
}

// Display sector list for user reference
static void displaySectorList() {
    Display::printHeader("Islamabad Sectors (Graph Nodes)");
    Display::printSystemLog("DATA STRUCTURE: Graph using Adjacency List");
    Display::printSystemLog("PURPOSE: Represent city sectors as vertices, roads as weighted edges");
    cout << "\n";
    cout << "  [0]  F-6  (Blue Area)      [8]  G-11 (Markaz)\n";
    cout << "  [1]  F-7  (Jinnah Super)   [9]  I-8  (Markaz)\n";
    cout << "  [2]  F-8  (Ayub Market)    [10] I-10 (Markaz)\n";
    cout << "  [3]  F-10 (Markaz)         [11] E-7  (Sector)\n";
    cout << "  [4]  G-6  (Melody)         [12] E-11 (MPCHS)\n";
    cout << "  [5]  G-8  (Markaz)         [13] H-8  (Centaurus)\n";
    cout << "  [6]  G-9  (Markaz)         [14] H-9  (Sector)\n";
    cout << "  [7]  G-10 (Markaz)\n";
    Display::printLine();
}

// Helper struct for Priority Queue
struct DistPair {
    int vertex;
    int distance;

    DistPair(int v, int d) : vertex(v), distance(d) {}
    DistPair() : vertex(-1), distance(0) {}

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

        // ========== ALGORITHM EXPLANATION ==========
        Display::printHeader("DIJKSTRA'S SHORTEST PATH ALGORITHM");
        cout << "\n";
        Display::setColor(Display::LIGHT_YELLOW);
        cout << "=== DATA STRUCTURES USED ===\n";
        Display::resetColor();
        cout << "  1. GRAPH (Adjacency List) - Stores sectors and roads\n";
        cout << "  2. ARRAYS (dist[], parent[], visited[]) - Track distances and path\n";
        cout << "  3. MIN-HEAP (Priority Queue) - Always get minimum distance vertex\n";
        cout << "\n";
        Display::setColor(Display::LIGHT_YELLOW);
        cout << "=== WHY DIJKSTRA? ===\n";
        Display::resetColor();
        cout << "  - Finding shortest delivery route from restaurant to customer\n";
        cout << "  - Optimizes delivery time by avoiding longer paths\n";
        cout << "  - Works with weighted edges (road distances in km)\n";
        cout << "\n";

        // Initialize
        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== STEP 1: INITIALIZATION ===\n";
        Display::resetColor();
        cout << "  Setting all distances to INFINITY (unreachable)\n";
        cout << "  Setting source " << getSectorName(src) << " distance to 0\n\n";
        
        for (int i = 0; i < V; i++) {
            dist[i] = 2147483647;
            parent[i] = -1;
            visited[i] = false;
        }
        dist[src] = 0;

        // Show initial distance table
        cout << "  Initial Distance Table:\n";
        cout << "  +----------------------+----------+\n";
        cout << "  | Sector               | Distance |\n";
        cout << "  +----------------------+----------+\n";
        for (int i = 0; i < V; i++) {
            cout << "  | " << getSectorShort(i);
            for (size_t s = getSectorShort(i).length(); s < 20; s++) cout << " ";
            cout << "| ";
            if (dist[i] == 2147483647) cout << "INF     ";
            else cout << dist[i] << " km    ";
            cout << "|\n";
        }
        cout << "  +----------------------+----------+\n\n";

        Heap<DistPair> pq;
        pq.insert(DistPair(src, 0));
        
        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== STEP 2: PROCESS VERTICES (Using Min-Heap) ===\n";
        Display::resetColor();
        Display::printSystemLog("HEAP OPERATION: Insert source into priority queue");
        cout << "\n";
        
        int step = 1;

        while (!pq.isEmpty()) {
            Display::printSystemLog("HEAP OPERATION: ExtractMin() - Get vertex with smallest distance");
            DistPair current = pq.extractMin();
            int u = current.vertex;

            if (visited[u]) {
                cout << "  [Skip] " << getSectorShort(u) << " already visited\n";
                continue;
            }
            visited[u] = true;

            Display::setColor(Display::LIGHT_GREEN);
            cout << "\n  Step " << step++ << ": Processing " << getSectorName(u);
            cout << " (distance: " << dist[u] << " km)\n";
            Display::resetColor();

            if (u == dest) {
                Display::printSuccess("Destination " + getSectorName(dest) + " reached!");
                break;
            }

            Display::printSystemLog("GRAPH OPERATION: Get adjacency list of " + getSectorShort(u));
            LinkedList<Edge>& adj = g.getAdjList(u);
            Node<Edge>* temp = adj.getHead();
            
            cout << "  Checking neighbors (LINKED LIST traversal):\n";
            
            while (temp) {
                int v = temp->data.dest;
                int weight = temp->data.weight;

                cout << "    " << getSectorShort(u) << " -> " << getSectorShort(v);
                cout << " (road distance: " << weight << " km): ";

                if (visited[v]) {
                    cout << "Already visited\n";
                } else if (dist[u] != 2147483647 && dist[u] + weight < dist[v]) {
                    int oldDist = dist[v];
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.insert(DistPair(v, dist[v]));
                    Display::printSystemLog("HEAP OPERATION: Insert updated distance for " + getSectorShort(v));
                    
                    Display::setColor(Display::LIGHT_GREEN);
                    if (oldDist == 2147483647) {
                        cout << "      Distance: INF -> " << dist[v] << " km (UPDATED)\n";
                    } else {
                        cout << "      Distance: " << oldDist << " -> " << dist[v] << " km (UPDATED)\n";
                    }
                    Display::resetColor();
                } else {
                    cout << "No improvement\n";
                }
                temp = temp->next;
            }
        }

        // Display result
        cout << "\n";
        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== STEP 3: RESULT ===\n";
        Display::resetColor();
        
        if (dist[dest] == 2147483647) {
            Display::printError("No path exists from " + getSectorName(src) + " to " + getSectorName(dest));
        } else {
            Display::setColor(Display::LIGHT_GREEN);
            cout << "  Shortest Distance: " << dist[dest] << " km\n\n";
            Display::resetColor();
            
            cout << "  Delivery Route: ";
            printPath(parent, dest);
            cout << "\n\n";
            
            cout << "  Route Details:\n";
            printPathDetailed(parent, dist, dest);
        }

        delete[] dist;
        delete[] parent;
        delete[] visited;
    }

private:
    static void printPath(int parent[], int j) {
        if (parent[j] == -1) {
            cout << getSectorShort(j);
            return;
        }
        printPath(parent, parent[j]);
        cout << " -> " << getSectorShort(j);
    }
    
    static void printPathDetailed(int parent[], int dist[], int j) {
        if (parent[j] == -1) {
            cout << "    [START] " << getSectorName(j) << " (0 km)\n";
            return;
        }
        printPathDetailed(parent, dist, parent[j]);
        cout << "       |-> " << getSectorName(j) << " (" << dist[j] << " km total)\n";
    }
};

#endif