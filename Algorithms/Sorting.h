#pragma once

#include <random>
#include <chrono>
#include <vector>

// All containers should have random access iterators.
namespace Sorting
{
    // Return index of val within [lo, hi] of the container, return -1 if not found.
    // The range [lo, hi] should be sorted.
    template <class Container, class T>
    int binary_search(const Container& c, int lo, int hi, const T& val)
    {
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (c[mid] == val) {
                return mid;
            }
            else if (c[mid] > val) {
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }
        return -1;
    }

    // Sort the container in place within [lo, hi].
    // Good for small containers.
    template <class Container>
    void insertion_sort(Container& c, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; ++i) {
            for (int j = i; j > lo; --j) {
                if (c[j] < c[j - 1]) {
                    std::swap(c[j], c[j - 1]);
                }
                else {
                    break;
                }
            }
        }
    }

    // Shell sort the container in place within [lo, hi].
    // Good for medium to large containers.
    template <class Container>
    void shell_sort(Container& c, int lo, int hi)
    {
        int h = 1;
        while (h < (hi - lo + 1) / 3) {
            h = 3 * h + 1;
        }

        while (h >= 1) {
            for (int i = lo + h; i <= hi; ++i) {
                for (int j = i; j >= lo + h; j -= h) {
                    if (c[j] < c[j - h]) {
                        std::swap(c[j], c[j - h]);
                    }
                }
            }
            h /= 3;
        }
    }

    // Shuffle the container within [lo, hi]
    template <class Container>
    void shuffle(Container& container, int lo, int hi)
    {
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
    // into sorted range of [lo, hi] in place. aux should be a copy of c.
    template <class Container>
    void merge(Container& c, Container& aux, int lo, int mid, int hi)
    {
        for (int i = lo; i <= hi; ++i) {
            aux[i] = c[i];
        }
        int left = lo;
        int right = mid + 1;

        for (int i = lo; i <= hi; ++i) {
            if (left > mid) {
                c[i] = aux[right++];
            }
            else if (right > hi) {
                c[i] = aux[left++];
            }
            else if (aux[left] < aux[right]) {
                c[i] = aux[left++];
            }
            else {
                c[i] = aux[right++];
            }
        }
    }

    // Sort the container within [lo, hi]. aux should be a copy of c.
    template <class Container>
    void merge_sort(Container& c, Container& aux, int lo, int hi)
    {
        if (hi <= lo) {
            return;
        }
        if (hi - lo < 7) {
            insertion_sort(c, lo, hi);
            return;
        }

        int mid = (lo + hi) / 2;
        merge_sort(c, aux, lo, mid);
        merge_sort(c, aux, mid + 1, hi);

        if (c[mid] <= c[mid + 1]) {
            return;
        }
        merge(c, aux, lo, mid, hi);
    }

    // Randomly pick an element p between [lo, hi] of the container, and
    // partition c in place, so that items to the left of p are all smaller than
    // or equal to p, and items to the right of p are all greater than or equal to p.
    // Return index of p after partition.
    template <class Container>
    int partition(Container& c, int lo, int hi)
    {
        // We pick c[lo] as p because [lo, hi] is already shuffled.
        int i = lo + 1;
        int j = hi;

        while (true) {
            while (c[i] < c[lo] && i <= hi) {
                ++i;
            }
            while (c[j] > c[lo]) {
                --j;
            }
            if (i >= j) {
                break;
            }
            std::swap(c[i++], c[j--]);
        }
        std::swap(c[lo], c[j]);

        return j;
    }

    // Return the k'th smallest element in c, without sorting c.
    // Container will be shuffled and should have a size() member function.
    // k should be within [1, c.size()].
    template <class Container, class T>
    T quick_select(Container& c, int k)
    {
        int lo = 0;
        int hi = c.size() - 1;
        shuffle(c, lo, hi);

        while (lo < hi) {
            int p = partition(c, lo, hi);
            if (p == k - 1) {
                return c[p];
            }
            else if (p > k - 1) {
                hi = p - 1;
            }
            else {
                lo = p + 1;
            }
        }

        return c[k - 1];
    }

    // Quick sort the container in place within [lo, hi].
    // The container must be shuffled before sorting.
    template <class Container>
    void quick_sort(Container& c, int lo, int hi)
    {
        if (hi <= lo) {
            return;
        }
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
        }
        else if (c[hi] <= c[mid] && c[mid] <= c[lo]) {
            std::swap(c[lo], c[mid]);
        }
        else if (c[lo] <= c[hi] && c[hi] <= c[mid]) {
            std::swap(c[lo], c[hi]);
        }
        else if (c[mid] <= c[hi] && c[hi] <= c[lo]) {
            std::swap(c[lo], c[hi]);
        }

        // Recursively sort the 2 partitions
        int p = partition(c, lo, hi);
        if (p > lo) {
            quick_sort(c, lo, p - 1);
        }
        if (p < hi) {
            quick_sort(c, p + 1, hi);
        }
    }

    // Quick sort the container in place within [lo, hi].
    // The container must be shuffled before sorting.
    // Quicker than normal 2-way quick sort for typical inputs
    // where there are many duplicate keys.
    template <class Container>
    void three_way_quick_sort(Container& c, int lo, int hi)
    {
        if (hi <= lo) {
            return;
        }
        if (hi - lo < 10) {
            insertion_sort(c, lo, hi);
            return;
        }

        int mid = (lo + hi) / 2;
        if (c[lo] <= c[mid] && c[mid] <= c[hi]) {
            std::swap(c[lo], c[mid]);
        }
        else if (c[hi] <= c[mid] && c[mid] <= c[lo]) {
            std::swap(c[lo], c[mid]);
        }
        else if (c[lo] <= c[hi] && c[hi] <= c[mid]) {
            std::swap(c[lo], c[hi]);
        }
        else if (c[mid] <= c[hi] && c[hi] <= c[lo]) {
            std::swap(c[lo], c[hi]);
        }

        int less = lo;
        int greater = hi;
        int i = lo + 1;

        while (i <= greater) {
            if (c[i] == c[less]) {
                ++i;
            }
            else if (c[i] < c[less]) {
                std::swap(c[i++], c[less++]);
            }
            else {
                std::swap(c[i], c[greater--]);
            }
        }

        if (less > lo) {
            quick_sort(c, lo, less - 1);
        }
        if (greater < hi) {
            quick_sort(c, greater + 1, hi);
        }
    }

    // A priority queue that uses a binary heap to store elements of type T,
    // and can pop out the minimum element.
    template <class T>
    class MinPriorityQueue {
    public:
        void push(const T& data)
        {
            heap.push_back(data);
            swim(heap.size() - 1);
        }

        T min()
        {
            return heap[0];
        }

        T pop_min()
        {
            T data = heap[0];
            std::swap(heap[0], heap[heap.size() - 1]);
            heap.pop_back();
            sink(0);
            return data;
        }

        bool is_empty() const
        {
            return heap.empty();
        }

    private:
        std::vector<T> heap;

        void swim(int i)
        {
            while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
                std::swap(heap[i], heap[(i - 1) / 2]);
                i = (i - 1) / 2;
            }
        }

        void sink(int i)
        {
            while (2 * i + 1 < static_cast<int>(heap.size())) {
                int smaller_child = 2 * i + 1;
                if (2 * i + 2 < static_cast<int>(heap.size()) && heap[2 * i + 2] < heap[2 * i + 1]) {
                    ++smaller_child;
                }
                if (heap[i] <= heap[smaller_child]) {
                    break;
                }
                std::swap(heap[i], heap[smaller_child]);
                i = smaller_child;
            }
        }
    };
}
