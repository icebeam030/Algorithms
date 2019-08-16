#pragma once

#include <algorithm>
#include <random>
#include <chrono>

namespace Sorting
{
// The containers should have a size() member function,
// and have random access iterators.

// Return index of val within [lo, hi] of the container, return -1 if not found.
// The range [lo, hi] should be sorted.
template <class Container, class T>
int binary_search(const Container& c, int lo, int hi, const T& val) {
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (c[mid] == val) {
      return mid;
    } else if (c[mid] > val) {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  return -1;
}

// Sort the container in place within [lo, hi]
template <class Container>
void insertion_sort(Container& c, int lo, int hi) {
  for (int i = lo + 1; i <= hi; ++i) {
    for (int j = i; j > lo; --j) {
      if (c[j - 1] > c[j]) {
        std::swap(c[j], c[j - 1]);
      } else {
        break;
      }
    }
  }
}

// Shell sort the container in place within [lo, hi]
template <class Container>
void shell_sort(Container& c, int lo, int hi) {
  int h = 1;
  while (h < (hi - lo + 1) / 3) {
    h = 3 * h + 1;
  }

  while (h >= 1) {
    for (int i = lo + h; i <= hi; ++i) {
      for (int j = i; j >= lo + h; j -= h) {
        if (c[j - h] > c[j]) {
          std::swap(c[j], c[j - h]);
        }
      }
    }

    h /= 3;
  }
}

// Shuffle the container within [lo, hi]
template <class Container>
void shuffle(Container& container, int lo, int hi) {
  using namespace std;

  int seed = static_cast<int>(chrono::system_clock::now().time_since_epoch().count());
  mt19937 generator(seed);

  for (int i = lo; i <= hi; ++i) {
    uniform_int_distribution<int> distribution(lo, i);
    int random = distribution(generator);
    swap(container[i], container[random]);
  }
}

// Merge 2 sorted parts of [lo, mid] and [mid + 1, hi] of the container
// into sorted range of [lo, hi] in place.
// aux should be a copy of c.
template <class Container>
void merge(Container& c, Container& aux, int lo, int mid, int hi) {
  for (int i = lo; i <= hi; ++i) {
    aux[i] = c[i];
  }
  int left = lo;
  int right = mid + 1;

  for (int i = lo; i <= hi; ++i) {
    if (left > mid) {
      c[i] = aux[right++];
    } else if (right > hi) {
      c[i] = aux[left++];
    } else if (aux[left] < aux[right]) {
      c[i] = aux[left++];
    } else {
      c[i] = aux[right++];
    }
  }
}

// Sort the container within [lo, hi]. aux should be a copy of c.
template <class Container>
void merge_sort(Container& c, Container& aux, int lo, int hi) {
  if (hi <= lo) { return; }
  if (hi - lo < 7) {
    insertion_sort(c, lo, hi);
    return;
  }

  int mid = (lo + hi) / 2;
  merge_sort(c, aux, lo, mid);
  merge_sort(c, aux, mid + 1, hi);

  if (c[mid] <= c[mid + 1]) { return; }
  merge(c, aux, lo, mid, hi);
}

// Randomly pick an element p between [lo, hi] of the container, and
// partition c in place, so that items to the left of p are all smaller
// than p, and items to the right of p are all greater than or equal to p.
// Return index of p after partition.
template <class Container>
int partition(Container& c, int lo, int hi) {
  // We pick c[lo] as p because [lo, hi] is already shuffled
  int i = lo + 1;
  int j = hi;

  while (i <= j) {
    while (c[i] < c[lo] && i <= hi) { ++i; }
    while (c[j] > c[lo] && j >= lo) { --j; }
    if (i < j) {
      std::swap(c[i], c[j]);
    }
  }

  std::swap(c[lo], c[j]);
  return j;
}

// Quick sort the container in place within [lo, hi].
// The container must be shuffled before sorting.
template <class Container>
void quick_sort(Container& c, int lo, int hi) {
  if (hi <= lo) { return; }
  if (hi - lo < 10) {
    insertion_sort(c, lo, hi);
    return;
  }

  // Find the median value among lo, mid and hi, and swap it
  // with c[lo] so that c[lo], as the p value for partitioning,
  // can be close to the median value within [lo, hi].
  int mid = (lo + hi) / 2;
  if (c[lo] <= c[mid] && c[mid] <= c[hi]) {
    std::swap(c[lo], c[mid]);
  } else if (c[hi] <= c[mid] && c[mid] <= c[lo]) {
    std::swap(c[lo], c[mid]);
  } else if (c[lo] <= c[hi] && c[hi] <= c[mid]) {
    std::swap(c[lo], c[hi]);
  } else if (c[mid] <= c[hi] && c[hi] <= c[lo]) {
    std::swap(c[lo], c[hi]);
  }

  int p = partition(c, lo, hi);
  if (p > lo) {
    quick_sort(c, lo, p - 1);
  }
  if (p < hi) {
    quick_sort(c, p + 1, hi);
  }
}

}
