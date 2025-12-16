#ifndef MST_H
#define MST_H

#include "Graph.h"
#include "Heap.h"
#include "Display.h"
#include <string>

using namespace std;

// Forward declaration from Dijkstra.h
extern string getSectorName(int id);
extern string getSectorShort(int id);

// Helper for Kruskal's Union-Find
struct Subset {
    int parent;
    int rank;
};

// Helper for Kruskal's Edge sorting
struct EdgeTriple {
    int src;
    int dest;
    int weight;

    EdgeTriple(int s, int d, int w) : src(s), dest(d), weight(w) {}
    EdgeTriple() : src(0), dest(0), weight(0) {}

    bool operator<(const EdgeTriple& other) const {
        return weight < other.weight;
    }
    
    bool operator>(const EdgeTriple& other) const {
        return weight > other.weight;
    }
};

class MST {
private:
    // Union-Find: Find with path compression
    static int find(Subset subsets[], int i) {
        if (subsets[i].parent != i)
            subsets[i].parent = find(subsets, subsets[i].parent);
        return subsets[i].parent;
    }

    // Union-Find: Union by rank
    static void Union(Subset subsets[], int x, int y, bool verbose = false) {
        int xroot = find(subsets, x);
        int yroot = find(subsets, y);

        if (verbose) {
            Display::printSystemLog("UNION-FIND: Merging " + getSectorShort(x) + " (root: " + 
                getSectorShort(xroot) + ") with " + getSectorShort(y) + " (root: " + getSectorShort(yroot) + ")");
        }

        if (subsets[xroot].rank < subsets[yroot].rank) {
            subsets[xroot].parent = yroot;
        } else if (subsets[xroot].rank > subsets[yroot].rank) {
            subsets[yroot].parent = xroot;
        } else {
            subsets[yroot].parent = xroot;
            subsets[xroot].rank++;
        }
    }

public:
    static void prims(Graph& g) {
        int V = g.getNumVertices();
        int* parent = new int[V];
        int* key = new int[V];
        bool* mstSet = new bool[V];

        // ========== ALGORITHM EXPLANATION ==========
        Display::printHeader("PRIM'S MST ALGORITHM - Optimal Delivery Network");
        cout << "\n";
        Display::setColor(Display::LIGHT_YELLOW);
        cout << "=== DATA STRUCTURES USED ===\n";
        Display::resetColor();
        cout << "  1. GRAPH (Adjacency List) - Stores sector connections\n";
        cout << "  2. ARRAYS (key[], parent[], mstSet[]) - Track minimum edges\n";
        cout << "  3. MIN-HEAP (Priority Queue) - Always pick minimum weight edge\n";
        cout << "\n";
        Display::setColor(Display::LIGHT_YELLOW);
        cout << "=== WHY PRIM'S MST? ===\n";
        Display::resetColor();
        cout << "  - Build optimal delivery network connecting ALL sectors\n";
        cout << "  - Minimize total road distance for delivery coverage\n";
        cout << "  - Ensures every sector is reachable with minimum cost\n";
        cout << "\n";

        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== STEP 1: INITIALIZATION ===\n";
        Display::resetColor();
        cout << "  Starting from " << getSectorName(0) << "\n";
        cout << "  Setting all key values to INFINITY\n\n";

        for (int i = 0; i < V; i++) {
            key[i] = 2147483647;
            mstSet[i] = false;
            parent[i] = -1;
        }

        key[0] = 0;
        parent[0] = -1;

        struct KeyPair {
            int v;
            int key;
            bool operator<(const KeyPair& o) const { return key < o.key; }
            bool operator>(const KeyPair& o) const { return key > o.key; }
        };

        Heap<KeyPair> pq;
        pq.insert({0, 0});
        
        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== STEP 2: BUILD MST (Greedy Selection) ===\n";
        Display::resetColor();
        Display::printSystemLog("HEAP OPERATION: Insert starting vertex");
        cout << "\n";
        
        int step = 1;
        int totalWeight = 0;

        while (!pq.isEmpty()) {
            Display::printSystemLog("HEAP OPERATION: ExtractMin() - Get minimum key vertex");
            int u = pq.extractMin().v;
            
            if (mstSet[u]) {
                cout << "  [Skip] " << getSectorShort(u) << " already in MST\n";
                continue;
            }
            mstSet[u] = true;

            Display::setColor(Display::LIGHT_GREEN);
            cout << "\n  Step " << step++ << ": Adding " << getSectorName(u) << " to MST\n";
            Display::resetColor();
            
            if (parent[u] != -1) {
                cout << "    Edge: " << getSectorShort(parent[u]) << " -- " 
                     << getSectorShort(u) << " (distance: " << key[u] << " km)\n";
                totalWeight += key[u];
            }

            // Show current MST
            cout << "    MST vertices: { ";
            bool first = true;
            for (int i = 0; i < V; i++) {
                if (mstSet[i]) {
                    if (!first) cout << ", ";
                    cout << getSectorShort(i);
                    first = false;
                }
            }
            cout << " }\n";

            Display::printSystemLog("GRAPH OPERATION: Traverse adjacency list of " + getSectorShort(u));
            LinkedList<Edge>& adj = g.getAdjList(u);
            Node<Edge>* temp = adj.getHead();
            
            cout << "    Checking roads from " << getSectorShort(u) << ":\n";
            
            while (temp) {
                int v = temp->data.dest;
                int weight = temp->data.weight;

                cout << "      -> " << getSectorShort(v) << " (" << weight << " km): ";

                if (mstSet[v]) {
                    cout << "Already in MST\n";
                } else if (weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.insert({v, key[v]});
                    Display::printSystemLog("HEAP OPERATION: Insert " + getSectorShort(v) + " with key " + to_string(weight));
                    cout << "      Key updated to " << weight << " km\n";
                } else {
                    cout << "No improvement\n";
                }
                temp = temp->next;
            }
        }

        // Display final MST
        cout << "\n";
        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== FINAL: OPTIMAL DELIVERY NETWORK ===\n";
        Display::resetColor();
        Display::printLine();
        cout << "  Roads in network:\n";
        for (int i = 1; i < V; i++) {
            if (parent[i] != -1) {
                cout << "    " << getSectorShort(parent[i]) << " <--> " << getSectorShort(i) 
                     << " (" << key[i] << " km)\n";
            }
        }
        Display::printLine();
        Display::setColor(Display::LIGHT_GREEN);
        cout << "  Total Network Distance: " << totalWeight << " km\n";
        Display::resetColor();
        cout << "  All " << V << " sectors are now connected with minimum total distance!\n";

        delete[] parent;
        delete[] key;
        delete[] mstSet;
    }

    static void kruskals(Graph& g) {
        int V = g.getNumVertices();
        Heap<EdgeTriple> pq;

        // ========== ALGORITHM EXPLANATION ==========
        Display::printHeader("KRUSKAL'S MST ALGORITHM - Using Union-Find");
        cout << "\n";
        Display::setColor(Display::LIGHT_YELLOW);
        cout << "=== DATA STRUCTURES USED ===\n";
        Display::resetColor();
        cout << "  1. GRAPH (Adjacency List) - Stores sector connections\n";
        cout << "  2. MIN-HEAP - Sort edges by weight (greedy selection)\n";
        cout << "  3. UNION-FIND (Disjoint Sets) - Detect cycles efficiently\n";
        cout << "\n";
        Display::setColor(Display::LIGHT_YELLOW);
        cout << "=== WHY KRUSKAL'S MST? ===\n";
        Display::resetColor();
        cout << "  - Alternative way to build optimal delivery network\n";
        cout << "  - Uses Union-Find to detect if edge creates a cycle\n";
        cout << "  - Good for sparse graphs (few edges)\n";
        cout << "\n";

        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== STEP 1: COLLECT ALL EDGES ===\n";
        Display::resetColor();
        Display::printSystemLog("GRAPH OPERATION: Traverse all adjacency lists");
        
        int edgeCount = 0;
        for (int i = 0; i < V; i++) {
            LinkedList<Edge>& adj = g.getAdjList(i);
            Node<Edge>* temp = adj.getHead();
            while (temp) {
                if (i < temp->data.dest) {
                    pq.insert(EdgeTriple(i, temp->data.dest, temp->data.weight));
                    cout << "    Edge: " << getSectorShort(i) << " -- " 
                         << getSectorShort(temp->data.dest) << " (" << temp->data.weight << " km)\n";
                    edgeCount++;
                }
                temp = temp->next;
            }
        }
        cout << "  Total edges: " << edgeCount << "\n";
        Display::printSystemLog("HEAP OPERATION: All edges inserted (sorted by weight)");
        cout << "\n";

        // Initialize Union-Find
        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== STEP 2: INITIALIZE UNION-FIND ===\n";
        Display::resetColor();
        Display::printSystemLog("Creating disjoint sets - each sector is its own set");
        Subset* subsets = new Subset[V];
        for (int v = 0; v < V; ++v) {
            subsets[v].parent = v;
            subsets[v].rank = 0;
        }
        cout << "  Each sector starts as its own tree (self-parent)\n\n";

        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== STEP 3: GREEDY EDGE SELECTION ===\n";
        Display::resetColor();
        cout << "  For each edge (smallest first), add if no cycle\n\n";
        
        int e = 0;
        int step = 1;
        int totalWeight = 0;
        
        while (e < V - 1 && !pq.isEmpty()) {
            Display::printSystemLog("HEAP OPERATION: ExtractMin() - Get smallest edge");
            EdgeTriple next_edge = pq.extractMin();
            
            cout << "  Step " << step++ << ": Edge " << getSectorShort(next_edge.src) 
                 << " -- " << getSectorShort(next_edge.dest) << " (" << next_edge.weight << " km)\n";
            
            Display::printSystemLog("UNION-FIND: Find() - Get root of each vertex");
            int x = find(subsets, next_edge.src);
            int y = find(subsets, next_edge.dest);
            
            cout << "    Find(" << getSectorShort(next_edge.src) << ") = " << getSectorShort(x) << "\n";
            cout << "    Find(" << getSectorShort(next_edge.dest) << ") = " << getSectorShort(y) << "\n";

            if (x != y) {
                Display::setColor(Display::LIGHT_GREEN);
                cout << "    ACCEPTED - Different sets (no cycle)\n";
                Display::resetColor();
                
                Union(subsets, x, y, true);
                totalWeight += next_edge.weight;
                e++;
                cout << "    MST edges: " << e << "/" << (V-1) << "\n\n";
            } else {
                Display::setColor(Display::LIGHT_RED);
                cout << "    REJECTED - Same set (would create cycle)\n\n";
                Display::resetColor();
            }
        }

        // Display final MST
        Display::setColor(Display::LIGHT_CYAN);
        cout << "=== FINAL: OPTIMAL DELIVERY NETWORK ===\n";
        Display::resetColor();
        Display::printLine();
        Display::setColor(Display::LIGHT_GREEN);
        cout << "  Total Network Distance: " << totalWeight << " km\n";
        cout << "  Edges in MST: " << e << "\n";
        Display::resetColor();

        delete[] subsets;
    }
};

#endif
