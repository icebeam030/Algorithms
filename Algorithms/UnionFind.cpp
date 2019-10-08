#include <stdexcept>
#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <math.h>

#include "UnionFind.h"

using namespace UnionFinds;
using namespace std;

// UnionFind class
UnionFind::UnionFind(int n) : N(n) {
  if (n <= 0) {
    throw invalid_argument("UnionFind: n should be positive!");
  }

  root = new int[N];
  size = new int[N];

  for (int i = 0; i < N; ++i) {
    root[i] = i;
    size[i] = 1;
  }
}

UnionFind::~UnionFind() {
  delete[] root;
  delete[] size;
}

int UnionFind::get_root(int i) {
  if (i < 0 || i > N - 1) {
    throw invalid_argument("UnionFind: argument should be within [0, N - 1]!");
  }

  // We find the root if i's parent is itself
  while (i != root[i]) {
    root[i] = root[root[i]];  // Set i's parent to its grandparent
    i = root[i];              // Move up the tree by one level
  }
  return i;
}

bool UnionFind::is_connected(int a, int b) {
  if (a < 0 || a > N - 1 || b < 0 || b > N - 1) {
    throw invalid_argument("UnionFind: argument should be within [0, N - 1]!");
  }

  return get_root(a) == get_root(b);
}

void UnionFind::connect(int a, int b) {
  if (a < 0 || a > N - 1 || b < 0 || b > N - 1) {
    throw invalid_argument("UnionFind: argument should be within [0, N - 1]!");
  }

  int i = get_root(a);
  int j = get_root(b);
  if (i == j) {
    return;
  }

  // If the tree containing a is larger
  if (size[i] > size[j]) {
    root[j] = i;         // Set b's root to a's root
    size[i] += size[j];  // Merge b's tree into a's tree
  } else {
    root[i] = j;
    size[j] += size[i];
  }
}


// Percolation class

// Create two extra virtual sites at top and bottom
Percolation::Percolation(int n)
  : N(n),
    grid(UnionFind(n * n + 2)),
    open_status(new bool[n * n + 2]) {
  if (n <= 0) {
    throw invalid_argument("Percolation: n should be positive!");
  }

  // All sites are initially blocked
  for (int i = 0; i < N * N; ++i) {
    open_status[i] = false;
  }

  open_status[N * N] = true;      // Open virtual top site
  open_status[N * N + 1] = true;  // Open virtual bottom site

  for (int i = 0; i < N; ++i) {
    // Connect virtual top site with each site in the first row
    grid.connect(i, N * N);
    // Connect virtual bottom site with each site in the last row
    grid.connect(N * N - 1 - i, N * N + 1);
  }
}

Percolation::~Percolation() {
  delete[] open_status;
}

void Percolation::open(int row, int col) {
  if (row < 1 || row > N || col < 1 || col > N) {
    throw invalid_argument("Percolation: row and col should be within [1, N]!");
  }

  if (is_open(row, col)) {
    return;
  }

  // Convert row and col to index in the grid
  int i = (row - 1) * N + col - 1;
  // Then open the site
  open_status[i] = true;
  open_sites_count += 1;

  // Connect current site to its left site if that site is open
  if (col > 1 && is_open(row, col - 1)) {
    grid.connect(i, i - 1);
  }
  // Right
  if (col < N && is_open(row, col + 1)) {
    grid.connect(i, i + 1);
  }
  // Top
  if (row > 1 && is_open(row - 1, col)) {
    grid.connect(i, i - N);
  }
  // Bottom
  if (row < N && is_open(row + 1, col)) {
    grid.connect(i, i + N);
  }
}

bool Percolation::is_open(int row, int col) const {
  if (row < 1 || row > N || col < 1 || col > N) {
    throw invalid_argument("Percolation: row and col should be within [1, N]!");
  }

  int i = (row - 1) * N + col - 1;
  return open_status[i];
}

bool Percolation::is_full(int row, int col) {
  if (row < 1 || row > N || col < 1 || col > N) {
    throw invalid_argument("Percolation: row and col should be within [1, N]!");
  }

  int i = (row - 1) * N + col - 1;
  return grid.is_connected(i, N * N);
}

int Percolation::number_of_open_sites() const {
  return open_sites_count;
}

bool Percolation::percolates() {
  return grid.is_connected(N * N, N * N + 1);
}


// PercolationStats class
PercolationStats::PercolationStats(int n, int t)
    : N(n), T(t) {
  if (n <= 0 || t <= 0) {
    throw invalid_argument("PercolationStats: n and t should be positive!");
  }

  run();
}

void PercolationStats::run() {
  cout << "Performing " << T << " trials on a " << N << "x" << N << " grid\n";
  cout << "This may take some time...\n\n";

  thresholds.reserve(T);

  // Run Monte-Carlo simulation T times
  for (int t = 0; t < T; ++t) {
    // Initialise a percolation grid
    Percolation grid(N);

    // All sites are initially blocked
    vector<int> blocked_sites;
    blocked_sites.reserve(N * N);
    for (int i = 0; i < N * N; ++i) {
      blocked_sites.push_back(i);
    }

    // Initialise random number generator and shuffle the vector
    // Note mt19937_64 might be needed if you test on really large N's
    int seed = static_cast<int>(chrono::system_clock::now().time_since_epoch().count());
    mt19937 generator(seed);
    shuffle(blocked_sites.begin(), blocked_sites.end(), generator);

    do {
      // Randomly choose a blocked site at index i
      uniform_int_distribution<int> distribution(0, blocked_sites.size() - 1);
      int i = distribution(generator);

      // Open that site
      int row = blocked_sites[i] / N + 1;
      int col = blocked_sites[i] % N + 1;
      grid.open(row, col);

      // Once the site is opened, remove it from the vector
      swap(blocked_sites[i], blocked_sites.back());
      blocked_sites.pop_back();
    } while (!grid.percolates());  // Loop until the system percolates

    // The percentage of open sites in the system is an estimate
    // of the percolation threshold.
    double threshold = static_cast<double>(grid.number_of_open_sites()) / N / N;
    thresholds.push_back(threshold);

    cout << "Trial " << t + 1 << " finished\n";
  }

  // Print out some useful stats
  cout << "\nTrial finished, stats about simulated percolation threshold:\n\n";
  cout << "Mean: " << mean() << '\n';
  cout << "Standard deviation: " << std_dev() << '\n';
  cout << "Low end of 95% confidence interval:  " << confidence_lo() << '\n';
  cout << "High end of 95% confidence interval: " << confidence_hi() << '\n';
}

double PercolationStats::mean() const {
  double sum = 0.0;
  for (double threshold : thresholds) {
    sum += threshold;
  }
  return sum / T;
}

double PercolationStats::std_dev() const {
  double s_squared = 0.0;
  double m = mean();
  for (double threshold : thresholds) {
    s_squared += (threshold - m) * (threshold - m);
  }
  s_squared /= static_cast<double>(T) - 1;
  return sqrt(s_squared);
}

double PercolationStats::confidence_lo() const {
  double m = mean();
  double s = std_dev();
  return m - (1.96 * s) / sqrt(T);
}

double PercolationStats::confidence_hi() const {
  double m = mean();
  double s = std_dev();
  return m + (1.96 * s) / sqrt(T);
}
