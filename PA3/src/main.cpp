#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "CBSolver.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    auto totoalStart = steady_clock::now();
    ifstream inFile( argv[1] );

        char graphtype;
    inFile >> graphtype;

    int numV, numE;
    inFile >> numV >> numE;
    CBSolver graph = CBSolver(numV, numE, (graphtype == 'd') ? true : false);

    // Read in edges, add to adjacency list
    for (int i = 0; i < graph.E; ++i) {
        int u, v;
        short w;
        inFile >> u >> v >> w;
        graph.edgeList.push_back({u, v, w});
        if (graph.directed) {
            graph.adjList[u].push_back({v, w});
        }
    }

    inFile.close();
    
    graph.MaximumSpanningTree();
    if(graph.directed) {
        graph.adjListLib = graph.adjList;
        graph.removeWeightLib = graph.minRemoveWeight;
        graph.removeWeight = graph.minRemoveWeight;
        graph.removeEdges = graph.minRemoveEdges;
        graph.removeEdgesLib = graph.minRemoveEdges;
        int loopCount = 0;
        auto timelimit = milliseconds(55000).count();
        auto enterStart = steady_clock::now();
        // Keep finding better solution
        while (loopCount < graph.positiveCount*2) {
            auto now = steady_clock::now();
            auto enterElapsed = duration_cast<milliseconds>(now - enterStart).count();
            auto totalElapsed = duration_cast<milliseconds>(now - totoalStart).count();
            // Stop if time is almost up
            if(loopCount != 0 && (enterElapsed / loopCount) * 8 > timelimit - totalElapsed) {
                break;
            }
            // Scheme of selecting the vertex to start from
            graph.AddbackEdge(loopCount < graph.positiveCount ? loopCount : loopCount - graph.positiveCount);
            if(loopCount == graph.positiveCount - 1) {
                sort(graph.removeEdgesLib.begin(), graph.removeEdgesLib.end(), [](Edge2 a, Edge2 b) {
                    return a.w > b.w;
                });
            }
            // If the current graph has less remove weight, update min
            if (graph.removeWeight < graph.minRemoveWeight) {
                graph.minRemoveEdges = graph.removeEdges;
                graph.minRemoveWeight = graph.removeWeight;
            }
            // Reset graph to original state
            graph.adjList = graph.adjListLib;
            graph.removeWeight = graph.removeWeightLib;
            graph.removeEdges = graph.removeEdgesLib;
            loopCount++;
        }
    }

    // Output edges to remove
    ofstream outFile( argv[2] );
    outFile << graph.minRemoveWeight << endl;
    for (int i = 0; i < (int)graph.minRemoveEdges.size(); ++i) {
        outFile << graph.minRemoveEdges[i].u << " " << graph.minRemoveEdges[i].v << " " << graph.minRemoveEdges[i].w << endl;
    }

    outFile.close();
    return 0;
}