// This file includes linked list stack, queue and dequeue.
// This file is declaration only. Include BOTH this file and
// LinkedLists.cpp which includes the implementation, in the file
// where you want to instantiate a template class instance.

#pragma once

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

  public:
    ~LinkedListStack();

    void push(T data);
    T pop();
    bool isEmpty() const;
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

  public:
    ~LinkedListQueue();

    void enqueue(T data);
    T dequeue();
    bool isEmpty() const;
};
