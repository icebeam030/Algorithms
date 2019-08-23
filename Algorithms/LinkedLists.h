// This file includes linked list stack, queue and deque.

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
    Node* current = head;
    while (current != nullptr) {
      head = head->next;
      delete current;
      current = head;
    }
  }

  // Push an item to the top of the stack
  void push(const T& data) {
    Node* new_head = new Node;
    new_head->data = data;
    new_head->next = head;
    head = new_head;

    ++number_of_items;
  }

  // Pop an item from the top of the stack
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
    return number_of_items == 0;
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
    Node* current = head;
    while (current != nullptr) {
      head = head->next;
      delete current;
      current = head;
    }
  }

  // Push an item to the end of the queue
  void push(const T& data) {
    Node* new_tail = new Node;
    new_tail->data = data;
    new_tail->next = nullptr;

    if (is_empty()) {
      head = new_tail;
    } else {
      tail->next = new_tail;
    }

    ++number_of_items;
    tail = new_tail;
  }

  // Pop an item from the start of the queue
  T pop() {
    if (is_empty()) {
      throw std::logic_error("Error: Poping from empty queue!");
    }

    T data = head->data;

    Node* old_head = head;
    head = head->next;
    delete old_head;
    --number_of_items;

    if (is_empty()) {
      tail = nullptr;
    }
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

  // Beginning iterator from start to end
  Iterator begin() const {
    return Iterator(head);
  }

  // Ending iterator from start to end
  Iterator end() const {
    return Iterator(nullptr);
  }
};


// Linked list deque
template <class T>
class Deque {
private:
  struct Node {
    T data;
    Node* next;
    Node* prev;
  };

  Node* head = nullptr;
  Node* tail = nullptr;
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
  ~Deque() {
    Node* current = head;
    while (current != nullptr) {
      head = head->next;
      delete current;
      current = head;
    }
  }

  // Push an item to the end of the queue
  void push_back(const T& data) {
    Node* new_tail = new Node;
    new_tail->data = data;
    new_tail->next = nullptr;
    new_tail->prev = tail;

    if (is_empty()) {
      head = new_tail;
    } else {
      tail->next = new_tail;
    }

    ++number_of_items;
    tail = new_tail;
  }

  // Push an item to the start of the queue
  void push_front(const T& data) {
    Node* new_head = new Node;
    new_head->data = data;
    new_head->next = head;
    new_head->prev = nullptr;

    if (is_empty()) {
      tail = new_head;
    } else {
      head->prev = new_head;
    }

    ++number_of_items;
    head = new_head;
  }

  // Pop an item from the end of the queue
  T pop_back() {
    if (is_empty()) {
      throw std::logic_error("Error: Poping from empty deque!");
    }

    T data = tail->data;

    Node* old_tail = tail;
    tail = tail->prev;
    delete old_tail;
    --number_of_items;

    if (is_empty()) {
      head = nullptr;
    } else {
      tail->next = nullptr;
    }

    return data;
  }

  // Pop an item from the start of the queue
  T pop_front() {
    if (is_empty()) {
      throw std::logic_error("Error: Poping from empty deque!");
    }

    T data = head->data;

    Node* old_head = head;
    head = head->next;
    delete old_head;
    --number_of_items;
  
    if (is_empty()) {
      tail = nullptr;
    } else {
      head->prev = nullptr;
    }

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

  // Beginning iterator from front to back
  Iterator begin() const {
    return Iterator(head);
  }

  // Ending iterator from front to back
  Iterator end() const {
    return Iterator(nullptr);
  }
};

}
