// Include BOTH this file and LinkedLists.h in the file
// where you want to instantiate a template instance.

#include <stdexcept>
#include "LinkedLists.h"

// Linked list stack
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


// Linked list queue
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
