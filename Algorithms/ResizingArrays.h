// This file includes resizing array stack, queue and randomised queue.

#pragma once

#include <stdexcept>

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

  // Resize array capacity to new_capacity
  void resize(int new_capacity) {
    T* new_array = new T[new_capacity];
    for (int i = 0; i < number_of_items; ++i) {
      new_array[i] = array[i];
    }

    T* old_array = array;
    array = new_array;
    delete[] old_array;

    capacity = new_capacity;
  }

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

  // Push data to the top of the stack
  void push(const T& data) {
    if (number_of_items == capacity) {
      resize(2 * capacity);
    }
    array[number_of_items++] = data;
  }

  // Pop data from the top of the stack
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

  // Resize array capacity to new_capacity
  void resize(int new_capacity) {
    T* new_array = new T[new_capacity];
    for (int i = 0; i < number_of_items; ++i) {
      new_array[i] = array[(head + i) % capacity];
    }

    T* old_array = array;
    array = new_array;
    delete[] old_array;

    capacity = new_capacity;
    head = 0;
    tail = number_of_items;
  }

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

  // Enqueue data to the back of the queue
  void enqueue(const T& data) {
    if (number_of_items == capacity) {
      resize(2 * capacity);
    }
    array[tail] = data;
    tail = (tail + 1) % capacity;
    ++number_of_items;
  }

  // Dequeue data from the front of the queue
  T dequeue() {
    if (is_empty()) {
      throw std::logic_error("Error: Poping from empty stack!");
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

  // Beginning iterator
  Iterator begin() const {
    return Iterator(array, head, capacity);
  }

  // Ending iterator
  Iterator end() const {
    return Iterator(array, tail, capacity);
  }
};

}
