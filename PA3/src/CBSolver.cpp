#include <vector>
#include <algorithm>
#include "CBSolver.h"

using namespace std;

DisjointSet::DisjointSet(int V) : parent(vector<int>(V)), rank(vector<int>(V)) {
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int DisjointSet::Find(int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = Find(parent[x]);
}

void DisjointSet::Union(int x, int y) {
    int xRoot = Find(x);
    int yRoot = Find(y);
    if (xRoot == yRoot) {
        return;
    }
    if (rank[xRoot] < rank[yRoot]) {
        parent[xRoot] = yRoot;
    }
    else if (rank[xRoot] > rank[yRoot]) {
        parent[yRoot] = xRoot;
    }
    else {
        parent[yRoot] = xRoot;
        ++rank[xRoot];
    }
}

void CBSolver::MaximumSpanningTree() {
    // Sort edges by weight in descending order
    sort(edgeList.begin(), edgeList.end(), [](Edge2 a, Edge2 b) {
        return a.w > b.w;
    });
    // Kruskal's Algorithm
    DisjointSet set(V);
    for (int i = 0; i < E; ++i) {
        Edge2 e = edgeList[i];
        if(set.Find(e.u) != set.Find(e.v)) {
            set.Union(e.u, e.v);
        }
        else {
            minRemoveEdges.push_back(e);
            minRemoveWeight += e.w;
        }
    }
    if(directed) {
        // Remove edges from adjacency list
        for (int i = 0; i < (int)minRemoveEdges.size(); ++i) {
                Edge2 e = minRemoveEdges[i];
                for(int j = 0; j < (int)adjList[e.u].size(); ++j) {
                    if(adjList[e.u][j].v == e.v) {
                        adjList[e.u].erase(adjList[e.u].begin() + j);
                        break;
                    }
                }
            }
        // Count positive and negative edges
        int i = 0;
        while (minRemoveEdges[i].w > 0 && i < (int)minRemoveEdges.size()) {
            i++;
        }
        positiveCount = i;
        negativeCount = (int)minRemoveEdges.size() - i;
    }
}

void CBSolver::AddbackEdge(int start) {
    // Add back positive edges
    for (int i = start; i < (int)removeEdges.size() - negativeCount; ++i) {
        Edge2 e = removeEdges[i];
        adjList[e.u].push_back({e.v, e.w});
        // Check for cycle
        if (DFSdetectCycle()) {
            adjList[e.u].pop_back();
        }
        else {
            removeEdges.erase(removeEdges.begin() + i);
            --i;
            removeWeight -= e.w;
        }
    }
    for(int i = 0; i < start; ++i) {
        Edge2 e = removeEdges[i];
        adjList[e.u].push_back({e.v, e.w});
        // Check for cycle
        if (DFSdetectCycle()) {
            adjList[e.u].pop_back();
        }
        else {
            removeEdges.erase(removeEdges.begin() + i);
            --i;
            --start;
            removeWeight -= e.w;
        }
    }
}

bool CBSolver::DFSdetectCycle() {
    // Reset for DFS
    for (int i = 0; i < V; ++i) {
        color[i] = WHITE;
    }
    // DFS: See if cycle exists
    for (int i = 0; i < V; ++i) {
        if (color[i] == WHITE && CycleFound(i)) {
            return true;
        }
    }
    return false;
}

bool CBSolver::CycleFound(int i) {
    color[i] = GRAY;
    for (int j = 0; j < (int)adjList[i].size(); ++j) {
        Edge e = adjList[i][j];
        if (color[e.v] == GRAY) {
            return true;
        }
        else if (color[e.v] == WHITE && CycleFound(e.v)) {
            return true;
        }
    }
    color[i] = BLACK;
    return false;
}