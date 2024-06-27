#ifndef CBSOLVER_H
#define CBSOLVER_H

#include <vector>

using namespace std;

enum Color {WHITE, GRAY, BLACK};

struct Edge {
    int v;
    short w;
};

struct Edge2 {
    int u, v;
    short w;
};

class DisjointSet {
    public:
        DisjointSet(int V);
        int Find(int x);
        void Union(int x, int y);

    private:
        vector<int> parent;
        vector<int> rank;
};

class CBSolver {
    public:
        int V, E;
        int minRemoveWeight = 0;
        int removeWeight;
        int removeWeightLib;
        bool directed;
        int positiveCount;
        int negativeCount;
        vector<Edge2> edgeList;
        vector<vector<Edge>> adjList;
        vector<vector<Edge>> adjListLib;    // directed only
        vector<Edge2> minRemoveEdges;
        vector<Edge2> removeEdges;          // directed only
        vector<Edge2> removeEdgesLib;       // directed only

        CBSolver(int numV, int numE, bool graphtype) : V(numV), E(numE), directed(graphtype), adjList(vector<vector<Edge>>(numV)), color(vector<Color>(numV)) {}
        void MaximumSpanningTree();
        void AddbackEdge(int start);        // directed only

    private:
        vector<Color> color;
        bool DFSdetectCycle();          // directed only
        bool CycleFound(int i);         // directed only
};

#endif