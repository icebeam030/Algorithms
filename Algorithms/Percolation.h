#pragma once

#include "UnionFind.h"

// Define a UnionFind grid to model a percolation system,
// which can be the foundation of Monte-Carlo simulations.
// Key function is open(row, col)
class Percolation {
private:
  const int N;
  UnionFind grid;
  bool* open_status;  // An array that stores the open status of each site
  int open_sites_count = 0;

public:
  Percolation(int n);  // Creates an n-by-n grid
  ~Percolation();

  void open(int row, int col);
  bool is_open(int row, int col) const;

  // A site is full if it's connected to the virtual top site
  bool is_full(int row, int col);

  int number_of_open_sites() const;
  bool percolates();  // Does the system percolate?
};
