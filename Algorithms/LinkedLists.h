// This file includes linked list stack, queue and dequeue.
// This file is declaration only. Include BOTH this file and
// LinkedLists.cpp which includes the implementation, in the file
// where you want to instantiate a template class instance.

#pragma once

#include <memory>

using namespace std;

// Linked list stack
template <class T>
class LinkedListStack {
  private:
    struct Node {
      T data;
      Node* next;
    };

    Node* head = nullptr;
    int numberOfItems = 0;

    // Making the stack iterable
    class Iterator {
      private:
        Node* node;
      public:
        Iterator(Node* node) : node(node) {}
        Iterator operator++() {
          node = node->next;
          return *this;
        }
        bool operator==(const Iterator& other) const { return node == other.node; }
        bool operator!=(const Iterator& other) const { return node != other.node; }
        T operator*() const { return node->data; }
    };

  public:
    ~LinkedListStack();

    void push(const T&& data);
    T pop();
    bool isEmpty() const;
    int size() const;

    // For iterating over the stack
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
    int numberOfItems = 0;

    // Making the queue iterable
    class Iterator {
      private:
        Node* node;
      public:
        Iterator(Node* node) : node(node) {}
        Iterator operator++() {
          node = node->next;
          return *this;
        }
        bool operator==(const Iterator& other) const { return node == other.node; }
        bool operator!=(const Iterator& other) const { return node != other.node; }
        T operator*() const { return node->data; }
    };

  public:
    ~LinkedListQueue();

    void enqueue(const T&& data);
    T dequeue();
    bool isEmpty() const;
    int size() const;

    // For iterating over the queue
    Iterator begin() const;
    Iterator end() const;
};
