// Include BOTH this file and LinkedLists.h in the file
// where you want to instantiate a template instance.

#include <stdexcept>
#include "LinkedLists.h"

using namespace std;

// Linked list stack implementation
template <class T>
LinkedListStack<T>::~LinkedListStack()
{
  while (head != nullptr) {
    Node* current = head;
    head = head->next;
    delete current;
  }
}

template <class T>
void LinkedListStack<T>::push(const T& data)
{
  Node* new_node = new Node;
  new_node->data = data;
  new_node->next = head;
  head = new_node;

  ++number_of_items;
}

template <class T>
T LinkedListStack<T>::pop()
{
  if (is_empty()) {
    throw logic_error("Error: Poping from empty stack!");
  }

  T data = head->data;
  Node* old_head = head;
  head = head->next;
  delete old_head;

  --number_of_items;
  return data;
}

template <class T>
bool LinkedListStack<T>::is_empty() const
{
  return head == nullptr;
}

template <class T>
int LinkedListStack<T>::size() const
{
  return number_of_items;
}

template <class T>
typename LinkedListStack<T>::Iterator LinkedListStack<T>::begin() const
{
  return Iterator(head);
}

template <class T>
typename LinkedListStack<T>::Iterator LinkedListStack<T>::end() const
{
  return Iterator(nullptr);
}


// Linked list queue implementation
template <class T>
LinkedListQueue<T>::~LinkedListQueue()
{
  while (head != nullptr) {
    Node* current = head;
    head = head->next;
    delete current;
  }
}

template <class T>
void LinkedListQueue<T>::enqueue(const T& data)
{
  Node* old_tail = tail;

  tail = new Node;
  tail->data = data;
  tail->next = nullptr;

  if (is_empty()) {
    head = tail;
  } else {
    old_tail->next = tail;
  }

  ++number_of_items;
}

template <class T>
T LinkedListQueue<T>::dequeue()
{
  if (is_empty()) {
    throw logic_error("Error: Poping from empty queue!");
  }

  T data = head->data;
  Node* old_head = head;
  head = head->next;
  delete old_head;

  if (is_empty()) {
    tail = nullptr;
  }

  --number_of_items;
  return data;
}

template <class T>
bool LinkedListQueue<T>::is_empty() const
{
  return head == nullptr;
}

template <class T>
int LinkedListQueue<T>::size() const
{
  return number_of_items;
}

template <class T>
typename LinkedListQueue<T>::Iterator LinkedListQueue<T>::begin() const
{
  return Iterator(head);
}

template <class T>
typename LinkedListQueue<T>::Iterator LinkedListQueue<T>::end() const
{
  return Iterator(nullptr);
}
