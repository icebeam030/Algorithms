// This file includes resizing array stack, queue and randomised queue.

#pragma once

#include <stdexcept>
#include <chrono>
#include <random>
#include <vector>

namespace ResizingArrays
{
// Resizing array stack
template <class T>
class Stack {
private:
  int number_of_items = 0;
  // Array capacity initialised to 1
  int capacity = 1;
  T* array = new T[1];

  class Iterator {
  private:
    T* const array;
    int index;
  public:
    Iterator(T* array, int index) : array(array), index(index) {}
    Iterator& operator++() {
      --index;
      return *this;
    }
    bool operator!=(const Iterator& other) const { return index != other.index; }
    const T& operator*() const { return array[index]; }
  };

public:
  // Destructor
  ~Stack() {
    delete[] array;
  }

  // Resize array capacity to new_capacity (will shrink to fit)
  void resize(int new_capacity) {
    T* new_array = new T[new_capacity];

    if (new_capacity < number_of_items) {
      number_of_items = new_capacity;
    }
    for (int i = 0; i < number_of_items; ++i) {
      new_array[i] = array[i];
    }

    T* old_array = array;
    array = new_array;
    delete[] old_array;

    capacity = new_capacity;
  }

  // Push an item to the top of the stack
  void push(const T& data) {
    if (number_of_items == capacity) {
      resize(2 * capacity);
    }
    array[number_of_items++] = data;
  }

  // Pop an item from the top of the stack
  T pop() {
    if (is_empty()) {
      throw std::logic_error("Error: Poping from empty stack!");
    }

    if (number_of_items == capacity / 4) {
      resize(capacity / 2);
    }
    return array[--number_of_items];
  }

  // Is the stack empty?
  bool is_empty() const {
    return number_of_items == 0;
  }

  // Current number of items on the stack
  int size() const {
    return number_of_items;
  }

  // Maximum number of items the stack can hold
  int max_size() const {
    return capacity;
  }

  // Beginning iterator
  Iterator begin() const {
    return Iterator(array, number_of_items - 1);
  }

  // Ending iterator
  Iterator end() const {
    return Iterator(array, -1);
  }
};


// Resizing array queue
template <class T>
class Queue {
private:
  int head = 0;
  int tail = 0;
  int number_of_items = 0;
  // Array capacity initialised to 1
  int capacity = 1;
  T* array = new T[1];

  class Iterator {
  private:
    T* const array;
    int index;
    int capacity;
  public:
    Iterator(T* array, int index, int capacity)
      : array(array), index(index), capacity(capacity) {}
    Iterator& operator++() {
      index = (index + 1) % capacity;
      return *this;
    }
    bool operator!=(const Iterator& other) const { return index != other.index; }
    const T& operator*() const { return array[index]; }
  };

public:
  // Destructor
  ~Queue() {
    delete[] array;
  }

  // Resize array capacity to new_capacity (will shrink to fit)
  void resize(int new_capacity) {
    T* new_array = new T[new_capacity];

    if (new_capacity < number_of_items) {
      number_of_items = new_capacity;
    }
    for (int i = 0; i < number_of_items; ++i) {
      new_array[i] = array[(head + i) % capacity];
    }

    T* old_array = array;
    array = new_array;
    delete[] old_array;

    capacity = new_capacity;
    head = 0;
    tail = number_of_items - 1;
  }

  // Push an item to the end of the queue
  void push(const T& data) {
    if (number_of_items == capacity) {
      resize(2 * capacity);
    }

    tail = (tail + 1) % capacity;
    array[tail] = data;
    ++number_of_items;
  }

  // Pop an item from the start of the queue
  T pop() {
    if (is_empty()) {
      throw std::logic_error("Error: Poping from empty queue!");
    }

    if (number_of_items == capacity / 4) {
      resize(capacity / 2);
    }

    T data = array[head];
    head = (head + 1) % capacity;
    --number_of_items;
    return data;
  }

  // Is the queue empty?
  bool is_empty() const {
    return number_of_items == 0;
  }

  // Current number of items on the queue
  int size() const {
    return number_of_items;
  }

  // Maximum number of items the queue can hold
  int max_size() const {
    return capacity;
  }

  // Beginning iterator from start to end
  Iterator begin() const {
    return Iterator(array, head, capacity);
  }

  // Ending iterator from start to end
  Iterator end() const {
    return Iterator(array, tail + 1, capacity);
  }
};


// Randomised queue using resizing array
template <class T>
class RandomisedQueue {
private:
  // Generate a random integer between [0, max]
  static int random_number(int max) {
    using namespace std;

    int seed = static_cast<int>(chrono::system_clock::now().time_since_epoch().count());
    mt19937 generator(seed);
    uniform_int_distribution<int> distribution(0, max);
    return distribution(generator);
  }

  int number_of_items = 0;
  // Array capacity initialised to 1
  int capacity = 1;
  T* array = new T[1];

  class Iterator {
  private:
    T* const array;
    int index;
    std::vector<int> indices;
  public:
    Iterator(T* array, int index, int n) : array(array), index(index) {
      if (this->index == -1) {
        return;
      }

      this->index = random_number(n - 1);
      indices.reserve(n - 1);
      for (int i = 0; i < n; ++i) {
        if (i != this->index) {
          indices.push_back(i);
        }
      }
    }
    Iterator& operator++() {
      if (indices.empty()) {
        index = -1;
      } else {
        int i = random_number(indices.size() - 1);
        index = indices[i];
        std::swap(indices[i], indices.back());
        indices.pop_back();
      }
      return *this;
    }
    bool operator!=(const Iterator& other) const { return index != other.index; }
    const T& operator*() const { return array[index]; }
  };

public:
  // Destructor
  ~RandomisedQueue() {
    delete[] array;
  }

  // Resize array capacity to new_capacity (will shrink to fit)
  void resize(int new_capacity) {
    T* new_array = new T[new_capacity];

    if (new_capacity < number_of_items) {
      number_of_items = new_capacity;
    }
    for (int i = 0; i < number_of_items; ++i) {
      new_array[i] = array[i];
    }

    T* old_array = array;
    array = new_array;
    delete[] old_array;

    capacity = new_capacity;
  }

  // Push an item to the end of the queue
  void push(const T& data) {
    if (number_of_items == capacity) {
      resize(2 * capacity);
    }
    array[number_of_items++] = data;
  }

  // Return a random item, but don't remove it
  T sample() {
    if (is_empty()) {
      throw std::logic_error("Error: Queue is empty!");
    }

    int i = random_number(number_of_items - 1);
    return array[i];
  }

  // Return and remove a random item from the queue
  T pop() {
    if (is_empty()) {
      throw std::logic_error("Error: Poping from empty queue!");
    }

    if (number_of_items == capacity / 4) {
      resize(capacity / 2);
    }

    int i = random_number(number_of_items - 1);
    std::swap(array[i], array[number_of_items - 1]);
    return array[--number_of_items];
  }

  // Is the queue empty?
  bool is_empty() const {
    return number_of_items == 0;
  }

  // Current number of items on the queue
  int size() const {
    return number_of_items;
  }

  // Maximum number of items the queue can hold
  int max_size() const {
    return capacity;
  }

  // Beginning iterator, iterates randomly
  Iterator begin() const {
    return Iterator(array, 0, number_of_items);
  }

  // Ending iterator, iterates randomly
  Iterator end() const {
    return Iterator(array, -1, number_of_items);
  }
};

}
