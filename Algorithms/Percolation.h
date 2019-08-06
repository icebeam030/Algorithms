#pragma once

#include "UnionFind.h"

using namespace std;

// Define a UnionFind grid to model a percolation system,
// which can be the foundation of Monte-Carlo simulations.
// Key function is open(row, col)
class Percolation {
  private:
    const int N;
    UnionFind grid;
    bool* openStatus;
    int openSitesCount = 0;

  public:
    // Creates an n-by-n grid
    Percolation(int n);
    ~Percolation();

    void open(int row, int col);
    bool isOpen(int row, int col) const;

    // A site is full if it's connected to the virtual top site
    bool isFull(int row, int col);

    int numberOfOpenSites() const;
    bool percolates();  // Does the system percolate?
};
