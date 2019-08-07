// Algorithms.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.

#include <iostream>
#include <string>
#include <sstream>

#include "PercolationStats.h"
#include "Queues.h"
#include "Queues.cpp"

using namespace std;

int main() {
  try {
    PercolationStats p(100, 40);
  } catch (const invalid_argument& e) {
    cerr << "Invalid argument: " << e.what() << '\n';
    return EXIT_FAILURE;
  } catch (const bad_alloc& e) {
    cerr << "Memory Exception: " << e.what() << ". Try using smaller arguments\n";
    return EXIT_FAILURE;
  } catch (...) {
    cerr << "Unknown Exception";
    return EXIT_FAILURE;
  }

  ResizingArrayQueue<string> queue;
  for (int i = 0; i < 4; ++i) {
    queue.enqueue(to_string(i));
  }
  for (int i = 0; i < 3; ++i) {
    cout << queue.dequeue() << '\n';
  }
  for (int i = 0; i < 2; ++i) {
    queue.enqueue("2nd " + to_string(i));
  }
  while (!queue.isEmpty()) {
    cout << queue.dequeue() << '\n';
  }
}
