#pragma once

#include <vector>
#include "Percolation.h"

using namespace std;

// Monte-Carlo simulation implementation based on Percolation model.
// Construct different objects to see the resulting stats.
class PercolationStats {
  private:
    const int N;
    const int T;
    vector<double> thresholds;  // Store simulated percolation thresholds
    void run();

  public:
    // Perform t trials on an n-by-n grid
    PercolationStats(int n, int t) : N(n), T(t) {
      if (n <= 0 || t <= 0) {
        throw invalid_argument("PercolationStats: n and t should be positive");
      }

      run();
    }

    // Some stats of simulated percolation thresholds
    double mean() const;          // Sample mean
    double stdDev() const;        // Sample standard deviation
    double confidenceLo() const;  // Low endpoint of 95% confidence interval
    double confidenceHi() const;  // High endpoint of 95% confidence interval
};
