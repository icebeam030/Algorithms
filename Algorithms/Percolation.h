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
    // Creates an n-by-n grid, and 2 extra virtual sites at top and bottom
    Percolation(int n)
        : N(n),
          grid(UnionFind(n * n + 2)),
          openStatus(new bool[n * n + 2]) {
      if (n <= 0) {
        throw invalid_argument("Percolation: n should be positive");
      }

      // All sites are initially blocked
      for (int i = 0; i < n * n; ++i) {
        openStatus[i] = false;
      }

      openStatus[n * n] = true;      // Open virtual top site
      openStatus[n * n + 1] = true;  // Open virtual bottom site

      for (int i = 0; i < n; ++i) {
        // Connect virtual top site with each site in the first row
        grid.connect(i, n * n);
        // Connect virtual bottom site with each site in the last row
        grid.connect(n * n - 1 - i, n * n + 1);
      }
    }
    ~Percolation() {
      delete[] openStatus;
    }

    void open(int row, int col);
    bool isOpen(int row, int col) const;

    // A site is full if it's connected to the virtual top site
    bool isFull(int row, int col);

    int numberOfOpenSites() const;
    bool percolates();  // Does the system percolate?
};
