#pragma once

using namespace std;

// Implements the Weighted Quick Union algorithm with path compression
// for union-find problems.
// Useful for dynamic connectivity, or percolation problems.
class UnionFind {
  private:
    const int N;
    int* root;  // An array that stores the root of each node
    int* size;  // An array that stores the size of the trees
    int getRoot(int i);

  public:
    UnionFind(int n);  // Creates a system of n nodes
    ~UnionFind();

    bool isConnected(int a, int b);
    void connect(int a, int b);
};

