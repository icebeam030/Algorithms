#include <stdexcept>
#include "UnionFind.h"

using namespace std;

UnionFind::UnionFind(int n) : N(n) {
  if (n <= 0) {
    throw invalid_argument("UnionFind: n should be positive!");
  }

  root = new int[N];
  size = new int[N];

  for (int i = 0; i < N; ++i) {
    root[i] = i;
    size[i] = 1;
  }
}

UnionFind::~UnionFind() {
  delete[] root;
  delete[] size;
}

int UnionFind::get_root(int i) {
  if (i < 0 || i > N - 1) {
    throw invalid_argument("UnionFind: argument should be within [0, N - 1]!");
  }

  // We find the root if i's parent is itself
  while (i != root[i]) {
    root[i] = root[root[i]];  // Set i's parent to its grandparent
    i = root[i];              // Move up the tree by one level
  }
  return i;
}

bool UnionFind::is_connected(int a, int b) {
  if (a < 0 || a > N - 1 || b < 0 || b > N - 1) {
    throw invalid_argument("UnionFind: argument should be within [0, N - 1]!");
  }

  return get_root(a) == get_root(b);
}

void UnionFind::connect(int a, int b) {
  if (a < 0 || a > N - 1 || b < 0 || b > N - 1) {
    throw invalid_argument("UnionFind: argument should be within [0, N - 1]!");
  }

  int i = get_root(a);
  int j = get_root(b);
  if (i == j) {
    return;
  }

  // If the tree containing a is larger
  if (size[i] > size[j]) {
    root[j] = i;         // Set b's root to a's root
    size[i] += size[j];  // Merge b's tree into a's tree
  } else {
    root[i] = j;
    size[j] += size[i];
  }
}
