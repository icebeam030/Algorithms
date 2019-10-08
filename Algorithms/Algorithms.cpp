// Algorithms.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.

#include <iostream>
#include <string>
#include <vector>

#include "PercolationStats.h"
#include "Sorting.h"
#include "AStar.h"

using namespace std;
using namespace Sorting;
using namespace PuzzleBoard;

int main() {
  cout << "Testing percolation...\n\n";
  try {
    PercolationStats p(100, 40);

  } catch (const invalid_argument& e) {
    cerr << "Invalid argument: " << e.what() << '\n';
    return EXIT_FAILURE;

  } catch (const bad_alloc& e) {
    cerr << "Memory Exception: " << e.what() << ". Try using smaller arguments.\n";
    return EXIT_FAILURE;

  } catch (...) {
    cerr << "Unknown Exception!";
    return EXIT_FAILURE;
  }

  cout << "\n\nTesting minimum priority queue...\n\n";
  MinPriorityQueue<int> pq;
  int seed = static_cast<int>(chrono::system_clock::now().time_since_epoch().count());
  mt19937 generator(seed);
  uniform_int_distribution<int> distribution(0, 1000);
  cout << "All items in priority queue:\n";
  for (int i = 0; i < 30; ++i) {
    int random = distribution(generator);
    cout << random << ' ';
    pq.push(random);
  }
  cout << "\n\nPoping minimum elements:\n";
  while (!pq.is_empty()) {
    cout << pq.pop_min() << ' ';
  }

  cout << "\n\n\nTesting puzzle board problem with an A* solver...\n\n";
  int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 11, 12, 13, 14, 15, 10 };
  vector<int> tiles(arr, arr + sizeof(arr) / sizeof(int));
  Board initial(tiles);
  Solver solver(initial);
  cout << "Solvable: " << boolalpha << solver.is_solvable() << '\n';
  cout << "Min moves: " << solver.min_moves() << '\n';
  cout << "\nSolution sequence:\n\n";
  auto solution = solver.solution();
  for (Board elem : solution) {
    cout << elem.string_representation() << '\n';
  }
}
