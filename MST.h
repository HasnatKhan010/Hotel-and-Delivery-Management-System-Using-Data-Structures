#ifndef MST_H
#define MST_H

#include "Graph.h"
#include "Heap.h"
#include "Display.h"

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
    // Union-Find methods for Kruskal's
    static int find(Subset subsets[], int i) {
        if (subsets[i].parent != i)
            subsets[i].parent = find(subsets, subsets[i].parent);
        return subsets[i].parent;
    }

    static void Union(Subset subsets[], int x, int y) {
        int xroot = find(subsets, x);
        int yroot = find(subsets, y);

        if (subsets[xroot].rank < subsets[yroot].rank)
            subsets[xroot].parent = yroot;
        else if (subsets[xroot].rank > subsets[yroot].rank)
            subsets[yroot].parent = xroot;
        else {
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

        for (int i = 0; i < V; i++) {
            key[i] = 2147483647;
            mstSet[i] = false;
            parent[i] = -1;
        }

        key[0] = 0;
        parent[0] = -1;

        // Using Heap for Priority Queue
        // Reusing DistPair from Dijkstra.h logic (vertex, key)
        // We need to define a local struct or include Dijkstra.h, but let's just redefine a simple one here or use a template pair if we had one.
        // Let's define a simple struct here to be self-contained.
        struct KeyPair {
            int v;
            int key;
            bool operator<(const KeyPair& o) const { return key < o.key; }
            bool operator>(const KeyPair& o) const { return key > o.key; }
        };

        Heap<KeyPair> pq;
        pq.insert({0, 0});

        while (!pq.isEmpty()) {
            int u = pq.extractMin().v;
            mstSet[u] = true;

            LinkedList<Edge>& adj = g.getAdjList(u);
            Node<Edge>* temp = adj.getHead();
            while (temp) {
                int v = temp->data.dest;
                int weight = temp->data.weight;

                if (!mstSet[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.insert({v, key[v]});
                }
                temp = temp->next;
            }
        }

        Display::printHeader("Prim's MST");
        for (int i = 1; i < V; i++) {
            if (parent[i] != -1)
                std::cout << parent[i] << " - " << i << " \tWeight: " << key[i] << "\n";
        }

        delete[] parent;
        delete[] key;
        delete[] mstSet;
    }

    static void kruskals(Graph& g) {
        int V = g.getNumVertices();
        Heap<EdgeTriple> pq; // Min-Heap to sort edges

        // Collect all edges
        for (int i = 0; i < V; i++) {
            LinkedList<Edge>& adj = g.getAdjList(i);
            Node<Edge>* temp = adj.getHead();
            while (temp) {
                // Add edge only once (since it's undirected, we might see it twice)
                // Or just add all and Union-Find will handle cycles.
                // To avoid double counting in display, we can add if i < dest
                if (i < temp->data.dest) {
                    pq.insert(EdgeTriple(i, temp->data.dest, temp->data.weight));
                }
                temp = temp->next;
            }
        }

        Subset* subsets = new Subset[V];
        for (int v = 0; v < V; ++v) {
            subsets[v].parent = v;
            subsets[v].rank = 0;
        }

        Display::printHeader("Kruskal's MST");
        int e = 0;
        while (e < V - 1 && !pq.isEmpty()) {
            EdgeTriple next_edge = pq.extractMin();
            int x = find(subsets, next_edge.src);
            int y = find(subsets, next_edge.dest);

            if (x != y) {
                std::cout << next_edge.src << " - " << next_edge.dest << " \tWeight: " << next_edge.weight << "\n";
                Union(subsets, x, y);
                e++;
            }
        }

        delete[] subsets;
    }
};

#endif
