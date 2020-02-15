// This file includes linked list stack, queue and deque.

#pragma once

#include <stdexcept>

namespace LinkedLists
{

#pragma region Stack

    template <class T>
    class Stack {
    public:
        Stack()
        {
        }

        Stack(const Stack& other)
        {
            T* data = new T[other.size()];
            int i = -1;
            for (const T& elem : other) {
                data[++i] = elem;
            }
            for (int i = other.size() - 1; i >= 0; --i) {
                push(data[i]);
            }
            delete[] data;
        }

        Stack& operator=(const Stack& other)
        {
            if (this == &other) {
                return *this;
            }

            while (!is_empty()) {
                pop();
            }

            T* data = new T[other.size()];
            int i = -1;
            for (const T& elem : other) {
                data[++i] = elem;
            }
            for (int i = other.size() - 1; i >= 0; --i) {
                push(data[i]);
            }
            delete[] data;

            return *this;
        }

        ~Stack()
        {
            Node* current = head;
            while (current != nullptr) {
                head = head->next;
                delete current;
                current = head;
            }
        }

        void push(const T& data)
        {
            Node* new_head = new Node;
            new_head->data = data;
            new_head->next = head;
            head = new_head;
            ++number_of_items;
        }

        T pop()
        {
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

        bool is_empty() const
        {
            return number_of_items == 0;
        }

        // Current number of items on the stack
        int size() const
        {
            return number_of_items;
        }

        // Iterator pointing to the top of the stack
        Iterator begin() const
        {
            return Iterator(head);
        }

        // Iterator pointing to one position below the bottom
        Iterator end() const
        {
            return Iterator(nullptr);
        }

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
            Iterator& operator++()
            {
                node = node->next;
                return *this;
            }
            bool operator!=(const Iterator& other) const { return node != other.node; }
            const T& operator*() const { return node->data; }
        private:
            Node* node;
        };
    };

#pragma endregion Stack


#pragma region Queue

    template <class T>
    class Queue {
    public:
        Queue()
        {
        }

        Queue(const Queue& other)
        {
            for (const T& elem : other) {
                push(elem);
            }
        }

        Queue& operator=(const Queue& other)
        {
            if (this == &other) {
                return *this;
            }

            while (!is_empty()) {
                pop();
            }
            for (const T& elem : other) {
                push(elem);
            }

            return *this;
        }

        ~Queue()
        {
            Node* current = head;
            while (current != nullptr) {
                head = head->next;
                delete current;
                current = head;
            }
        }

        void push(const T& data)
        {
            Node* new_tail = new Node;
            new_tail->data = data;
            new_tail->next = nullptr;

            if (is_empty()) {
                head = new_tail;
            }
            else {
                tail->next = new_tail;
            }

            ++number_of_items;
            tail = new_tail;
        }

        T pop()
        {
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

        bool is_empty() const
        {
            return number_of_items == 0;
        }

        // Current number of items on the queue
        int size() const
        {
            return number_of_items;
        }

        // Iterator pointing to the front
        Iterator begin() const
        {
            return Iterator(head);
        }

        // Iterator pointing to one position after the back
        Iterator end() const
        {
            return Iterator(nullptr);
        }

    private:
        struct Node {
            T data;
            Node* next;
        };
        Node* head = nullptr;
        Node* tail = nullptr;
        int number_of_items = 0;

        class Iterator {
        public:
            Iterator(Node* node) : node(node) {}
            Iterator& operator++()
            {
                node = node->next;
                return *this;
            }
            bool operator!=(const Iterator& other) const { return node != other.node; }
            const T& operator*() const { return node->data; }
        private:
            Node* node;
        };
    };

#pragma endregion Queue


#pragma region Deque

    template <class T>
    class Deque {
    public:
        Deque()
        {
        }

        Deque(const Deque& other)
        {
            for (const T& elem : other) {
                push_back(elem);
            }
        }

        Deque& operator=(const Deque& other)
        {
            if (this == &other) {
                return *this;
            }

            while (!is_empty()) {
                pop_back();
            }
            for (const T& elem : other) {
                push_back(elem);
            }
            return *this;
        }

        ~Deque()
        {
            Node* current = head;
            while (current != nullptr) {
                head = head->next;
                delete current;
                current = head;
            }
        }

        void push_back(const T& data)
        {
            Node* new_tail = new Node;
            new_tail->data = data;
            new_tail->next = nullptr;
            new_tail->prev = tail;

            if (is_empty()) {
                head = new_tail;
            }
            else {
                tail->next = new_tail;
            }

            ++number_of_items;
            tail = new_tail;
        }

        void push_front(const T& data)
        {
            Node* new_head = new Node;
            new_head->data = data;
            new_head->next = head;
            new_head->prev = nullptr;

            if (is_empty()) {
                tail = new_head;
            }
            else {
                head->prev = new_head;
            }

            ++number_of_items;
            head = new_head;
        }

        T pop_back()
        {
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
            }
            else {
                tail->next = nullptr;
            }

            return data;
        }

        T pop_front()
        {
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
            }
            else {
                head->prev = nullptr;
            }

            return data;
        }

        bool is_empty() const
        {
            return number_of_items == 0;
        }

        // Current number of items on the queue
        int size() const
        {
            return number_of_items;
        }

        // Iterator pointing to the front
        Iterator begin() const
        {
            return Iterator(head);
        }

        // Iterator pointing to one position after back
        Iterator end() const
        {
            return Iterator(nullptr);
        }

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
        public:
            Iterator(Node* node) : node(node) {}
            Iterator& operator++()
            {
                node = node->next;
                return *this;
            }
            bool operator!=(const Iterator& other) const { return node != other.node; }
            const T& operator*() const { return node->data; }
        private:
            Node* node;
        };
    };

#pragma endregion Deque

}
