#include <stdexcept>
#include "Percolation.h"

using namespace std;

void Percolation::open(int row, int col) {
  if (row < 1 || row > N || col < 1 || col > N) {
    throw invalid_argument("Percolation: row and col should be within [1, N]");
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
    throw invalid_argument("Percolation: row and col should be within [1, N]");
  }

  int i = (row - 1) * N + col - 1;
  return openStatus[i];
}

bool Percolation::isFull(int row, int col) {
  if (row < 1 || row > N || col < 1 || col > N) {
    throw invalid_argument("Percolation: row and col should be within [1, N]");
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
