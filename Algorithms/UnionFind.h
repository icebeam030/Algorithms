#pragma once

using namespace std;

// Implements the Weighted Quick Union algorithm with path compression
// for union-find problems.
// Useful for dynamic connectivity, or percolation problems.
class UnionFind {
  private:
    int* root;  // Stores the root of each node
    int* size;  // Stores the size of the trees
    int getRoot(int i);

  public:
    const int N;
    // Creates a system of n nodes
    UnionFind(int n) : N(n), root(new int[n]), size(new int[n]) {
      if (n <= 0) {
        throw invalid_argument("UnionFind: n should be positive");
      }

      for (int i = 0; i < n; ++i) {
        root[i] = i;
        size[i] = 1;
      }
    }
    ~UnionFind() {
      delete[] root;
      delete[] size;
    }

    bool isConnected(int a, int b);
    void connect(int a, int b);
};

