// Algorithms.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.

#include <iostream>
#include <string>
#include <sstream>
#include "UnionFind.h"
#include "Percolation.h"
#include "PercolationStats.h"

using namespace std;

int main() {
  try {
    PercolationStats p(1000, 40);
  } catch (const invalid_argument& e) {
    cerr << "Exception: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
}
