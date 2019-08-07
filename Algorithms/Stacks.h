// This file is declaration only. Include BOTH this file and
// Stacks.cpp which includes the implementation, in the file
// where you want to instantiate a template class instance.

#pragma once

using namespace std;

template <class T>
// Linked list implementation
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


template <class T>
// Resizing array implementation
class ResizingArrayStack {
  private:
    int numberOfItems = 0;
    // Capacity of array initialised to 1
    int capacity = 1;
    T* array = new T[1];

    void resizeArray(int newCapacity);

  public:
    ~ResizingArrayStack();

    void push(T data);
    T pop();
    bool isEmpty() const;
    int size() const;     // Current number of elements in the array
    int maxSize() const;  // Maximum number of elements the array can contain
};
