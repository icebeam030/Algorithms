#pragma once

#define NDEBUG

#include <algorithm>
#include <assert.h>
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
  assert(std::is_sorted(c.begin() + lo, c.begin() + hi + 1));

  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
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
// aux shall be a copy of c.
template <class Container>
void merge(Container& c, Container& aux, int lo, int mid, int hi) {
  assert(std::is_sorted(c.begin() + lo, c.begin() + mid + 1));
  assert(std::is_sorted(c.begin() + mid + 1, c.begin() + hi + 1));

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

  assert(std::is_sorted(c.begin() + lo, c.begin() + hi + 1));
}

template <class Container>
void merge_sort(Container& c, Container& aux, int lo, int hi) {
  if (hi <= lo) return;
  if (hi - lo < 7) {
    insertion_sort(c, lo, hi);
    return;
  }

  int mid = lo + (hi - lo) / 2;
  merge_sort(c, aux, lo, mid);
  merge_sort(c, aux, mid + 1, hi);

  if (c[mid] <= c[mid + 1]) return;
  merge(c, aux, lo, mid, hi);
}

}
