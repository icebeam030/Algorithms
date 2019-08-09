// Include BOTH this file and ResizingArrays.h in the file
// where you want to instantiate a template instance.

#include <stdexcept>
#include "ResizingArrays.h"

using namespace std;

// Resizing array stack implementation
template <class T>
ResizingArrayStack<T>::~ResizingArrayStack() {
  delete[] array;
}

template <class T>
void ResizingArrayStack<T>::resize(int newCapacity) {
  T* newArray = new T[newCapacity];
  for (int i = 0; i < numberOfItems; ++i) {
    newArray[i] = array[i];
  }

  T* oldArray = array;
  array = newArray;
  delete[] oldArray;

  capacity = newCapacity;
}

template <class T>
void ResizingArrayStack<T>::push(const T&& data) {
  if (numberOfItems == capacity) {
    resize(2 * capacity);
  }

  array[numberOfItems++] = data;
}

template <class T>
T ResizingArrayStack<T>::pop() {
  if (isEmpty()) {
    throw logic_error("Error: Poping from empty stack!");
  }

  if (numberOfItems == capacity / 4) {
    resize(capacity / 2);
  }

  return array[--numberOfItems];
}

template <class T>
bool ResizingArrayStack<T>::isEmpty() const {
  return numberOfItems == 0;
}

template <class T>
int ResizingArrayStack<T>::size() const {
  return numberOfItems;
}

template <class T>
int ResizingArrayStack<T>::maxSize() const {
  return capacity;
}


// Resizing array queue implementation
template <class T>
ResizingArrayQueue<T>::~ResizingArrayQueue() {
  delete[] array;
}

template <class T>
void ResizingArrayQueue<T>::resize(int newCapacity) {
  T* newArray = new T[newCapacity];
  for (int i = 0; i < numberOfItems; ++i) {
    newArray[i] = array[(head + i) % capacity];
  }

  T* oldArray = array;
  array = newArray;
  delete[] oldArray;

  capacity = newCapacity;
  head = 0;
  tail = numberOfItems;
}

template <class T>
void ResizingArrayQueue<T>::enqueue(const T&& data) {
  if (numberOfItems == capacity) {
    resize(2 * capacity);
  }

  array[tail] = data;
  tail = (tail + 1) % capacity;
  ++numberOfItems;
}

template <class T>
T ResizingArrayQueue<T>::dequeue() {
  if (isEmpty()) {
    throw logic_error("Error: Poping from empty stack!");
  }

  if (numberOfItems == capacity / 4) {
    resize(capacity / 2);
  }

  T data = array[head];
  head = (head + 1) % capacity;
  --numberOfItems;
  return data;
}

template <class T>
bool ResizingArrayQueue<T>::isEmpty() const {
  return numberOfItems == 0;
}

template <class T>
int ResizingArrayQueue<T>::size() const {
  return numberOfItems;
}

template <class T>
int ResizingArrayQueue<T>::maxSize() const {
  return capacity;
}
