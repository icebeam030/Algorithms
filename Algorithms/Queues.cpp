// Include BOTH this file and Queues.h in the file
// where you want to instantiate a template instance.

#include <stdexcept>
#include "Queues.h"

// Linked list implementation
template <class T>
LinkedListQueue<T>::~LinkedListQueue() {
  while (!isEmpty()) {
    Node* current = head;
    head = head->next;
    delete current;
  }
}

template <class T>
void LinkedListQueue<T>::enqueue(T data) {
  Node* oldTail = tail;

  tail = new Node;
  tail->data = data;
  tail->next = nullptr;

  if (isEmpty()) {
    head = tail;
  } else {
    oldTail->next = tail;
  }
}

template <class T>
T LinkedListQueue<T>::dequeue() {
  if (isEmpty()) {
    throw logic_error("Error: Poping from empty queue");
  }

  T data = head->data;
  Node* oldHead = head;
  head = head->next;
  delete oldHead;

  if (isEmpty()) {
    tail = nullptr;
  }
  return data;
}

template <class T>
bool LinkedListQueue<T>::isEmpty() const {
  return head == nullptr;
}


// Resizing array implementation
template <class T>
ResizingArrayQueue<T>::~ResizingArrayQueue() {
  delete[] array;
}

template <class T>
void ResizingArrayQueue<T>::resizeArray(int newCapacity) {
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
void ResizingArrayQueue<T>::enqueue(T data) {
  if (numberOfItems == capacity) {
    resizeArray(2 * capacity);
  }

  array[tail] = data;
  tail = (tail + 1) % capacity;
  ++numberOfItems;
}

template <class T>
T ResizingArrayQueue<T>::dequeue() {
  if (isEmpty()) {
    throw logic_error("Error: Poping from empty stack");
  }

  if (numberOfItems == capacity / 4) {
    resizeArray(capacity / 2);
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
