// Algorithms.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

#include "PercolationStats.h"
#include "Stacks.h"
#include "Queues.h"

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
  // LinkedListStack queue;
  // queue.push("Test");
  // queue.push("Test");
  // queue.push("Test");
  // queue.push("Test");
  // while (!queue.isEmpty()) {
  //   cout << queue.pop() << '\n';
  // }
}
