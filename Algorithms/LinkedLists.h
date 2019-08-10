// This file includes linked list stack, queue and dequeue.

#pragma once

#include <stdexcept>

namespace LinkedLists
{
// Linked list stack
template <class T>
class Stack {
private:
  struct Node {
    T data;
    Node* next;
  };

  Node* head = nullptr;
  int number_of_items = 0;

  class Iterator {
  private:
    Node* node;
  public:
    Iterator(Node* node) : node(node) {}
    Iterator& operator++() {
      node = node->next;
      return *this;
    }
    bool operator!=(const Iterator& other) const { return node != other.node; }
    const T& operator*() const { return node->data; }
  };

public:
  // Destructor
  ~Stack() {
    while (head != nullptr) {
      Node* current = head;
      head = head->next;
      delete current;
    }
  }

  // Push data to the top of the stack
  void push(const T& data) {
    Node* new_node = new Node;
    new_node->data = data;
    new_node->next = head;
    head = new_node;

    ++number_of_items;
  }

  // Pop data from the top of the stack
  T pop() {
    if (is_empty()) {
      throw std::logic_error("Error: Poping from empty stack!");
    }

    T data = head->data;
    Node* old_head = head;
    head = head->next;
    delete old_head;

    --number_of_items;
    return data;
  }

  // Is the stack empty?
  bool is_empty() const {
    return head == nullptr;
  }

  // Current number of items on the stack
  int size() const {
    return number_of_items;
  }

  // Beginning iterator
  Iterator begin() const {
    return Iterator(head);
  }

  // Ending iterator
  Iterator end() const {
    return Iterator(nullptr);
  }
};


// Linked list queue
template <class T>
class Queue {
private:
  struct Node {
    T data;
    Node* next;
  };

  Node* head = nullptr;
  Node* tail = head;
  int number_of_items = 0;

  class Iterator {
  private:
    Node* node;
  public:
    Iterator(Node* node) : node(node) {}
    Iterator& operator++() {
      node = node->next;
      return *this;
    }
    bool operator!=(const Iterator& other) const { return node != other.node; }
    const T& operator*() const { return node->data; }
  };

public:
  // Destructor
  ~Queue() {
    while (head != nullptr) {
      Node* current = head;
      head = head->next;
      delete current;
    }
  }

  // Enqueue data to the back of the queue
  void enqueue(const T& data) {
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

  // Dequeue data from the front of the queue
  T dequeue() {
    if (is_empty()) {
      throw std::logic_error("Error: Poping from empty queue!");
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

  // Is the queue empty?
  bool is_empty() const {
    return head == nullptr;
  }

  // Current number of items on the queue
  int size() const {
    return number_of_items;
  }

  // Beginning iterator
  Iterator begin() const {
    return Iterator(head);
  }

  // Ending iterator
  Iterator end() const {
    return Iterator(nullptr);
  }
};

}
