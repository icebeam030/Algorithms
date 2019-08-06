#include <stdexcept>
#include "Percolation.h"

using namespace std;

Percolation::Percolation(int n)
  : N(n),
    // Create two extra virtual sites at top and bottom
    grid(UnionFind(n * n + 2)),
    openStatus(new bool[n * n + 2]) {
  if (n <= 0) {
    throw invalid_argument("Percolation: n should be positive!");
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

Percolation::~Percolation() {
  delete[] openStatus;
}

void Percolation::open(int row, int col) {
  if (row < 1 || row > N || col < 1 || col > N) {
    throw invalid_argument("Percolation: row and col should be within [1, N]!");
  }

  if (isOpen(row, col)) return;

  // Convert row and col to index in the grid
  int i = (row - 1) * N + col - 1;
  // Then open the site
  openStatus[i] = true;
  openSitesCount += 1;

  // Connect current site to its left site if that site is open
  if (col > 1 && isOpen(row, col - 1)) {
    grid.connect(i, i - 1);
  }
  // Right
  if (col < N && isOpen(row, col + 1)) {
    grid.connect(i, i + 1);
  }
  // Top
  if (row > 1 && isOpen(row - 1, col)) {
    grid.connect(i, i - N);
  }
  // Bottom
  if (row < N && isOpen(row + 1, col)) {
    grid.connect(i, i + N);
  }
}

bool Percolation::isOpen(int row, int col) const {
  if (row < 1 || row > N || col < 1 || col > N) {
    throw invalid_argument("Percolation: row and col should be within [1, N]!");
  }

  int i = (row - 1) * N + col - 1;
  return openStatus[i];
}

bool Percolation::isFull(int row, int col) {
  if (row < 1 || row > N || col < 1 || col > N) {
    throw invalid_argument("Percolation: row and col should be within [1, N]!");
  }

  int i = (row - 1) * N + col - 1;
  return grid.isConnected(i, N * N);
}

int Percolation::numberOfOpenSites() const {
  return openSitesCount;
}

bool Percolation::percolates() {
  return grid.isConnected(N * N, N * N + 1);
}
