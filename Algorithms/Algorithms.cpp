// Algorithms.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.

#include <iostream>
#include <string>

#include "PercolationStats.h"
#include "LinkedLists.h"
#include "LinkedLists.cpp"
#include "ResizingArrays.h"
#include "ResizingArrays.cpp"

using namespace std;

int main() {
  // try {
  //   PercolationStats p(100, 40);
  // } catch (const invalid_argument& e) {
  //   cerr << "Invalid argument: " << e.what() << '\n';
  //   return EXIT_FAILURE;
  // } catch (const bad_alloc& e) {
  //   cerr << "Memory Exception: " << e.what() << ". Try using smaller arguments.\n";
  //   return EXIT_FAILURE;
  // } catch (...) {
  //   cerr << "Unknown Exception!";
  //   return EXIT_FAILURE;
  // }

  LinkedListQueue<string> stack;
  for (int i = 0; i < 5; ++i) {
    stack.enqueue(to_string(i));
  }
  for (int i = 0; i < 2; ++i) {
    stack.dequeue();
  }
  for (int i = 0; i < 3; ++i) {
    stack.enqueue("2nd " + to_string(i));
  }
  cout << "Testing iterator...\n";
  for (string s : stack) {
    cout << s << '\n';
  }
  cout << "dequeueing all elements...\n";
  while (!stack.isEmpty()) {
    cout << stack.dequeue() << '\n';
  }
}
