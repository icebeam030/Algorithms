// Include BOTH this file and Stacks.h in the file
// where you want to instantiate a template instance.

#include <stdexcept>
#include "Stacks.h"

// Linked list implementation
template <class T>
LinkedListStack<T>::~LinkedListStack() {
  while (!isEmpty()) {
    Node* current = head;
    head = head->next;
    delete current;
  }
}

template <class T>
void LinkedListStack<T>::push(T data) {
  Node* newNode = new Node;
  newNode->data = data;
  newNode->next = head;
  head = newNode;
}

template <class T>
T LinkedListStack<T>::pop() {
  if (isEmpty()) {
    throw logic_error("Error: Poping from empty stack");
  }

  T data = head->data;
  Node* oldHead = head;
  head = head->next;
  delete oldHead;
  return data;
}

template <class T>
bool LinkedListStack<T>::isEmpty() const {
  return head == nullptr;
}


// Resizing array implementation
template <class T>
ResizingArrayStack<T>::~ResizingArrayStack() {
  delete[] array;
}

template <class T>
void ResizingArrayStack<T>::resizeArray(int newCapacity) {
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
void ResizingArrayStack<T>::push(T data) {
  if (numberOfItems == capacity) {
    resizeArray(2 * capacity);
  }

  array[numberOfItems++] = data;
}

template <class T>
T ResizingArrayStack<T>::pop() {
  if (isEmpty()) {
    throw logic_error("Error: Poping from empty stack");
  }

  if (numberOfItems == capacity / 4) {
    resizeArray(capacity / 2);
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
