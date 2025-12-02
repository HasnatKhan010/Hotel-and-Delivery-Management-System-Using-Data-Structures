#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "LinkedList.h"
#include "Display.h"

using namespace std;

// Simple structure for adjacency list node
struct Edge {
    int dest;
    int weight;

    Edge(int d, int w) : dest(d), weight(w) {}
    Edge() : dest(0), weight(0) {}

    bool operator==(const Edge& other) const {
        return dest == other.dest; // Basic comparison for removal
    }

    friend ostream& operator<<(ostream& os, const Edge& e) {
        os << "(" << e.dest << ", w:" << e.weight << ")";
        return os;
    }
};

class Graph {
private:
    int numVertices;
    LinkedList<Edge>* adjLists;
    bool isDirected;

public:
    Graph(int vertices, bool directed = false) : numVertices(vertices), isDirected(directed) {
        adjLists = new LinkedList<Edge>[vertices];
    }

    ~Graph() {
        delete[] adjLists;
    }

    void addEdge(int src, int dest, int weight = 1) {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            adjLists[src].insertTail(Edge(dest, weight));
            if (!isDirected) {
                adjLists[dest].insertTail(Edge(src, weight));
            }
        } else {
            Display::printError("Invalid vertex index");
        }
    }

    void display() const {
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << ": ";
            adjLists[i].display();
        }
    }

    LinkedList<Edge>& getAdjList(int vertex) {
        return adjLists[vertex];
    }

    int getNumVertices() const {
        return numVertices;
    }
};

#endif
