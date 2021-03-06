#pragma once

#include <vector>

namespace UnionFind
{

#pragma region Implementaion

    // Implements the Weighted Quick Union algorithm with path compression
    // for union-find problems.
    // Useful for dynamic connectivity, or percolation problems.
    class WeightedQuickUnion {
    public:
        WeightedQuickUnion(int n);  // Creates a system of n nodes
        ~WeightedQuickUnion();

        bool is_connected(int a, int b);
        void connect(int a, int b);

    private:
        const int N;
        int* root;  // An array that stores the root of each node
        int* size;  // An array that stores the size of the trees
        int get_root(int i);
    };

#pragma endregion Implementation


#pragma region Percolation

    // Define a UnionFind grid to model a percolation system,
    // which can be the foundation of Monte-Carlo simulations.
    // Key function is open(row, col)
    class Percolation {
    public:
        Percolation(int n);  // Creates an n-by-n grid
        ~Percolation();

        void open(int row, int col);
        bool is_open(int row, int col) const;

        // A site is full if it's connected to the virtual top site
        bool is_full(int row, int col);

        int number_of_open_sites() const;
        bool percolates();  // Does the system percolate?

    private:
        const int N;
        WeightedQuickUnion grid;
        bool* open_status;  // An array that stores the open status of each site
        int open_sites_count = 0;
    };

    // Monte-Carlo simulation implementation based on Percolation model.
    // Construct different objects to see the resulting stats.
    class PercolationStats {
    public:
        // Perform t trials on an n-by-n grid
        PercolationStats(int n, int t);

        // Some stats of simulated percolation thresholds
        double mean() const;           // Sample mean
        double std_dev() const;        // Sample standard deviation
        double confidence_lo() const;  // Low endpoint of 95% confidence interval
        double confidence_hi() const;  // High endpoint of 95% confidence interval

    private:
        const int N;
        const int T;
        std::vector<double> thresholds;  // Store simulated percolation thresholds
        void run();
    };

#pragma endregion Percolation

}
