// This file is declaration only. Include BOTH this file and
// Queues.cpp which includes the implementation, in the file
// where you want to instantiate a template class instance.

#pragma once

using namespace std;

// Linked list implementation
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


// Resizing array implementation
template <class T>
class ResizingArrayQueue {
  private:
    int head = 0;
    int tail = 0;
    int numberOfItems = 0;
    // Capacity of array initialised to 1
    int capacity = 1;
    T* array = new T[1];

    void resizeArray(int newCapacity);

  public:
    ~ResizingArrayQueue();

    void enqueue(T data);
    T dequeue();
    bool isEmpty() const;
    int size() const;     // Current number of elements in the array
    int maxSize() const;  // Maximum number of elements the array can contain
};
