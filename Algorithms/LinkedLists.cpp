// Include BOTH this file and LinkedLists.h in the file
// where you want to instantiate a template instance.

#include <stdexcept>
#include "LinkedLists.h"

using namespace std;

// Linked list stack implementation
template <class T>
LinkedListStack<T>::~LinkedListStack() {
  while (head != nullptr) {
    Node* current = head;
    head = head->next;
    delete current;
  }
}

template <class T>
void LinkedListStack<T>::push(const T&& data) {
  Node* newNode = new Node;
  newNode->data = data;
  newNode->next = head;
  head = newNode;

  ++numberOfItems;
}

template <class T>
T LinkedListStack<T>::pop() {
  if (isEmpty()) {
    throw logic_error("Error: Poping from empty stack!");
  }

  T data = head->data;
  Node* oldHead = head;
  head = head->next;
  delete oldHead;

  --numberOfItems;
  return data;
}

template <class T>
bool LinkedListStack<T>::isEmpty() const {
  return head == nullptr;
}

template <class T>
int LinkedListStack<T>::size() const {
  return numberOfItems;
}

template <class T>
typename LinkedListStack<T>::Iterator LinkedListStack<T>::begin() const {
  return Iterator(head);
}

template <class T>
typename LinkedListStack<T>::Iterator LinkedListStack<T>::end() const {
  return Iterator(nullptr);
}


// Linked list queue implementation
template <class T>
LinkedListQueue<T>::~LinkedListQueue() {
  while (head != nullptr) {
    Node* current = head;
    head = head->next;
    delete current;
  }
}

template <class T>
void LinkedListQueue<T>::enqueue(const T&& data) {
  Node* oldTail = tail;

  tail = new Node;
  tail->data = data;
  tail->next = nullptr;

  if (isEmpty()) {
    head = tail;
  } else {
    oldTail->next = tail;
  }

  ++numberOfItems;
}

template <class T>
T LinkedListQueue<T>::dequeue() {
  if (isEmpty()) {
    throw logic_error("Error: Poping from empty queue!");
  }

  T data = head->data;
  Node* oldHead = head;
  head = head->next;
  delete oldHead;

  if (isEmpty()) {
    tail = nullptr;
  }

  --numberOfItems;
  return data;
}

template <class T>
bool LinkedListQueue<T>::isEmpty() const {
  return head == nullptr;
}

template <class T>
int LinkedListQueue<T>::size() const {
  return numberOfItems;
}

template <class T>
typename LinkedListQueue<T>::Iterator LinkedListQueue<T>::begin() const {
  return Iterator(head);
}

template <class T>
typename LinkedListQueue<T>::Iterator LinkedListQueue<T>::end() const {
  return Iterator(nullptr);
}
