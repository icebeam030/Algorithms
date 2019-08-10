// Include BOTH this file and ResizingArrays.h in the file
// where you want to instantiate a template instance.

#include <stdexcept>
#include "ResizingArrays.h"

using namespace std;

// Resizing array stack implementation
template <class T>
ResizingArrayStack<T>::~ResizingArrayStack()
{
  delete[] array;
}

template <class T>
void ResizingArrayStack<T>::resize(int new_capacity)
{
  T* new_array = new T[new_capacity];
  for (int i = 0; i < number_of_items; ++i) {
    new_array[i] = array[i];
  }

  T* old_array = array;
  array = new_array;
  delete[] old_array;

  capacity = new_capacity;
}

template <class T>
void ResizingArrayStack<T>::push(const T& data)
{
  if (number_of_items == capacity) {
    resize(2 * capacity);
  }

  array[number_of_items++] = data;
}

template <class T>
T ResizingArrayStack<T>::pop()
{
  if (is_empty()) {
    throw logic_error("Error: Poping from empty stack!");
  }

  if (number_of_items == capacity / 4) {
    resize(capacity / 2);
  }

  return array[--number_of_items];
}

template <class T>
bool ResizingArrayStack<T>::is_empty() const {
  return number_of_items == 0;
}

template <class T>
int ResizingArrayStack<T>::size() const
{
  return number_of_items;
}

template <class T>
int ResizingArrayStack<T>::max_size() const
{
  return capacity;
}

template <class T>
typename ResizingArrayStack<T>::Iterator ResizingArrayStack<T>::begin() const
{
  return Iterator(array, number_of_items - 1);
}

template <class T>
typename ResizingArrayStack<T>::Iterator ResizingArrayStack<T>::end() const
{
  return Iterator(array, -1);
}


// Resizing array queue implementation
template <class T>
ResizingArrayQueue<T>::~ResizingArrayQueue()
{
  delete[] array;
}

template <class T>
void ResizingArrayQueue<T>::resize(int new_capacity)
{
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

template <class T>
void ResizingArrayQueue<T>::enqueue(const T& data)
{
  if (number_of_items == capacity) {
    resize(2 * capacity);
  }

  array[tail] = data;
  tail = (tail + 1) % capacity;
  ++number_of_items;
}

template <class T>
T ResizingArrayQueue<T>::dequeue()
{
  if (is_empty()) {
    throw logic_error("Error: Poping from empty stack!");
  }

  if (number_of_items == capacity / 4) {
    resize(capacity / 2);
  }

  T data = array[head];
  head = (head + 1) % capacity;
  --number_of_items;
  return data;
}

template <class T>
bool ResizingArrayQueue<T>::is_empty() const
{
  return number_of_items == 0;
}

template <class T>
int ResizingArrayQueue<T>::size() const
{
  return number_of_items;
}

template <class T>
int ResizingArrayQueue<T>::max_size() const
{
  return capacity;
}

template <class T>
typename ResizingArrayQueue<T>::Iterator ResizingArrayQueue<T>::begin() const
{
  return Iterator(array, head, capacity);
}

template <class T>
typename ResizingArrayQueue<T>::Iterator ResizingArrayQueue<T>::end() const
{
  return Iterator(array, tail, capacity);
}
