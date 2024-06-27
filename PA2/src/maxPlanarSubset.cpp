#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Make use of the space unused in MPS to store Arrows
#define Arrows(i,j) MPS[N-1-i][N-1-j]
#define KOUT 1
#define KIN 2
#define KBOUNDARY 3

unsigned short ComputeMPS(vector<int>& C, vector<vector<unsigned short>>& MPS) {
    // Bottom-up Iterative Implementation
    int N = C.size();
    for (int i = N-2; i >= 0; --i) {
        for (int j = i+1; j < N; ++j) {
            int k = C[j];
            // k not in [i,j]
            if (k < i || k > j) {
                MPS[i][j] = MPS[i][j-1];
                Arrows(i,j) = KOUT;
            }
            // k in (i,j)
            else if (i < k && k < j) {
                if (k+1 <= j-1) {
                    MPS[i][j] = MPS[i][k-1] + 1 + MPS[k+1][j-1];
                } else {
                    MPS[i][j] = MPS[i][k-1] + 1;
                }
                // max{MPS[i][j-1], MPS[i][k-1]+1+MPS[k+1][j-1]}
                if (MPS[i][j-1] >= MPS[i][j]) {
                    MPS[i][j] = MPS[i][j-1];
                    Arrows(i,j) = KOUT;
                } else {
                    Arrows(i,j) = KIN;
                }
            } 
            // k == i
            else {
                if (i+1 <= j-1) {
                    MPS[i][j] = MPS[i+1][j-1] + 1;
                } else {
                MPS[i][j] = 1;
                }
                Arrows(i,j) = KBOUNDARY;
            }
        }
    }
    return MPS[0][N-1];
}

void PrintMPS(ofstream& outFile, vector<int>& C, vector<vector<unsigned short>>& MPS, int i, int j) {
    if (i >= j) return;
    int N = C.size();
    if (Arrows(i,j) == KOUT) {
        PrintMPS(outFile, C, MPS, i, j-1);
    } else if (Arrows(i,j) == KIN) {
        PrintMPS(outFile, C, MPS, i, C[j]-1);
        outFile << C[j] << " " << j << '\n';
        PrintMPS(outFile, C, MPS, C[j]+1, j-1);
    } else {
        outFile << i << " " << j << '\n';
        PrintMPS(outFile, C, MPS, i+1, j-1);
    }
}

int main(int argc, char* argv[]) {
    ifstream inFile( argv[1] );
    ofstream outFile( argv[2] );
    int N, v1, v2;

    // Read in number of vertices
    inFile >> N;
    vector<int> C(N);
    // Read in N/2 pairs of vertices
    for (int i = 0; i < N/2; ++i) {
        inFile >> v1 >> v2;
        C[v1] = v2;
        C[v2] = v1;
    }
    inFile.close();

    // MPS Table: default all 0
    vector<vector<unsigned short>> MPS(N, vector<unsigned short>(N, 0));

    // Compute the maximum planar subset and prunsigned int
    outFile << ComputeMPS(C, MPS) << '\n';
    PrintMPS(outFile, C, MPS, 0, N-1);
    outFile.close();

    return 0;
}