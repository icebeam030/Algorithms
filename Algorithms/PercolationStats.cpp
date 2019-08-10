#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <math.h>

#include "PercolationStats.h"
#include "Percolation.h"

using namespace std;

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
    vector<int> blockedSites;
    blockedSites.reserve(N * N);
    for (int i = 0; i < N * N; ++i) {
      blockedSites.push_back(i);
    }

    // Initialise random number generator and shuffle the vector
    // Note mt19937_64 might be needed if you test on really large N's
    int seed = static_cast<int>(chrono::system_clock::now().time_since_epoch().count());
    mt19937 generator(seed);
    shuffle(blockedSites.begin(), blockedSites.end(), generator);

    do {
      // Randomly choose a blocked site at index i
      uniform_int_distribution<int> distribution(0, blockedSites.size() - 1);
      int i = distribution(generator);

      // Open that site
      int row = blockedSites[i] / N + 1;
      int col = blockedSites[i] % N + 1;
      grid.open(row, col);

      // Once the site is opened, remove it from the vector
      swap(blockedSites[i], blockedSites.back());
      blockedSites.pop_back();
    } while (!grid.percolates());  // Loop until the system percolates

    // The percentage of open sites in the system is an estimate
    // of the percolation threshold.
    double threshold = static_cast<double>(grid.numberOfOpenSites()) / N / N;
    thresholds.push_back(threshold);

    cout << "Trial " << t + 1 << " finished\n";
  }

  // Print out some useful stats
  cout << "\nTrial finished, stats about simulated percolation threshold:\n\n";
  cout << "Mean: " << mean() << '\n';
  cout << "Standard deviation: " << stdDev() << '\n';
  cout << "Low end of 95%% confidence interval:  " << confidenceLo() << '\n';
  cout << "High end of 95%% confidence interval: " << confidenceHi() << '\n';
}

double PercolationStats::mean() const {
  double sum = 0.0;
  for (double threshold : thresholds) {
    sum += threshold;
  }
  return sum / T;
}

double PercolationStats::stdDev() const {
  double s_squared = 0.0;
  double m = mean();
  for (double threshold : thresholds) {
    s_squared += (threshold - m) * (threshold - m);
  }
  s_squared /= static_cast<double>(T) - 1;
  return sqrt(s_squared);
}

double PercolationStats::confidenceLo() const {
  double m = mean();
  double s = stdDev();
  return m - (1.96 * s) / sqrt(T);
}

double PercolationStats::confidenceHi() const {
  double m = mean();
  double s = stdDev();
  return m + (1.96 * s) / sqrt(T);
}
