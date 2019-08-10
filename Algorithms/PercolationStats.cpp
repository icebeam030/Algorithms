#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <math.h>

#include "PercolationStats.h"
#include "Percolation.h"

using namespace std;

PercolationStats::PercolationStats(int n, int t)
  : N(n), T(t)
{
  if (n <= 0 || t <= 0) {
    throw invalid_argument("PercolationStats: n and t should be positive!");
  }

  run();
}

void PercolationStats::run()
{
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

double PercolationStats::mean() const
{
  double sum = 0.0;
  for (double threshold : thresholds) {
    sum += threshold;
  }
  return sum / T;
}

double PercolationStats::std_dev() const
{
  double s_squared = 0.0;
  double m = mean();
  for (double threshold : thresholds) {
    s_squared += (threshold - m) * (threshold - m);
  }
  s_squared /= static_cast<double>(T) - 1;
  return sqrt(s_squared);
}

double PercolationStats::confidence_lo() const
{
  double m = mean();
  double s = std_dev();
  return m - (1.96 * s) / sqrt(T);
}

double PercolationStats::confidence_hi() const
{
  double m = mean();
  double s = std_dev();
  return m + (1.96 * s) / sqrt(T);
}
