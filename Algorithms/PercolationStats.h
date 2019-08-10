#pragma once

#include <vector>

// Monte-Carlo simulation implementation based on Percolation model.
// Construct different objects to see the resulting stats.
class PercolationStats {
private:
  const int N;
  const int T;
  std::vector<double> thresholds;  // Store simulated percolation thresholds
  void run();

public:
  // Perform t trials on an n-by-n grid
  PercolationStats(int n, int t);

  // Some stats of simulated percolation thresholds
  double mean() const;          // Sample mean
  double std_dev() const;        // Sample standard deviation
  double confidence_lo() const;  // Low endpoint of 95% confidence interval
  double confidence_hi() const;  // High endpoint of 95% confidence interval
};
