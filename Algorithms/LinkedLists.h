// This file includes linked list stack, queue and dequeue.
// This file is declaration only. Include BOTH this file and
// LinkedLists.cpp which includes the implementation, in the file
// where you want to instantiate a template class instance.

#pragma once

// Linked list stack
template <class T>
class LinkedListStack {
private:
  struct Node {
    T data;
    Node* next;
  };

  Node* head = nullptr;
  int number_of_items = 0;

  class Iterator {
  public:
    Iterator(Node* node) : node(node) {}
    Iterator& operator++() {
      node = node->next;
      return *this;
    }
    bool operator!=(const Iterator& other) const { return node != other.node; }
    const T& operator*() const { return node->data; }
  private:
    Node* node;
  };

public:
  ~LinkedListStack();

  void push(const T& data);
  T pop();
  bool is_empty() const;
  int size() const;

  Iterator begin() const;
  Iterator end() const;
};


// Linked list queue
template <class T>
class LinkedListQueue {
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
  ~LinkedListQueue();

  void enqueue(const T& data);
  T dequeue();
  bool is_empty() const;
  int size() const;

  Iterator begin() const;
  Iterator end() const;
};
