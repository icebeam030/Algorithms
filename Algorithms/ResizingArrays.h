// This file includes resizing array stack, queue and randomised queue.
// This file is declaration only. Include BOTH this file and
// ResizingArrays.cpp which includes the implementation, in the file
// where you want to instantiate a template class instance.

#pragma once

// Resizing array stack
template <class T>
class ResizingArrayStack {
private:
  int number_of_items = 0;
  // Capacity of array initialised to 1
  int capacity = 1;
  T* array = new T[1];

  void resize(int new_capacity);

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
  ~ResizingArrayStack();

  void push(const T& data);
  T pop();
  bool is_empty() const;
  int size() const;      // Current number of elements in the array
  int max_size() const;  // Maximum number of elements the array can contain

  Iterator begin() const;
  Iterator end() const;
};


// Resizing array queue
template <class T>
class ResizingArrayQueue {
private:
  int head = 0;
  int tail = 0;
  int number_of_items = 0;
  // Capacity of array initialised to 1
  int capacity = 1;
  T* array = new T[1];

  void resize(int new_capacity);

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
  ~ResizingArrayQueue();

  void enqueue(const T& data);
  T dequeue();
  bool is_empty() const;
  int size() const;      // Current number of elements in the array
  int max_size() const;  // Maximum number of elements the array can contain

  Iterator begin() const;
  Iterator end() const;
};
