#include <stdexcept>
#include "UnionFind.h"

using namespace std;

int UnionFind::getRoot(int i) {
  if (i < 0 || i > N - 1) {
    throw invalid_argument("UnionFind: argument should be within [0, N - 1]");
  }

  // We find the root if i's parent is itself
  while (i != root[i]) {
    root[i] = root[root[i]];  // Set i's parent to its grandparent
    i = root[i];              // Move up the tree by one level
  }
  return i;
}

bool UnionFind::isConnected(int a, int b) {
  if (a < 0 || a > N - 1 || b < 0 || b > N - 1) {
    throw invalid_argument("UnionFind: argument should be within [0, N - 1]");
  }

  return getRoot(a) == getRoot(b);
}

void UnionFind::connect(int a, int b) {
  if (a < 0 || a > N - 1 || b < 0 || b > N - 1) {
    throw invalid_argument("UnionFind: argument should be within [0, N - 1]");
  }

  int i = getRoot(a);
  int j = getRoot(b);
  if (i == j) return;

  // If the tree containing a is larger
  if (size[i] > size[j]) {
    root[j] = i;         // Set b's root to a's root
    size[i] += size[j];  // Merge b's tree into a's tree
  } else {
    root[i] = j;
    size[j] += size[i];
  }
}
