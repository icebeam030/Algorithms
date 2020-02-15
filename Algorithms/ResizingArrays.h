// This file includes resizing array stack, queue and randomised queue.

#pragma once

#include <stdexcept>
#include <chrono>
#include <random>
#include <vector>

namespace ResizingArrays
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
            number_of_items = other.number_of_items;
            capacity = other.capacity;

            delete[] array;
            array = new T[capacity];
            for (const T& elem : other) {
                array[--number_of_items] = elem;
            }
            number_of_items = other.number_of_items;
        }

        Stack& operator=(const Stack& other)
        {
            if (this == &other) {
                return *this;
            }

            number_of_items = other.number_of_items;
            capacity = other.capacity;

            delete[] array;
            array = new T[capacity];
            for (const T& elem : other) {
                array[--number_of_items] = elem;
            }
            number_of_items = other.number_of_items;

            return *this;
        }

        ~Stack()
        {
            delete[] array;
        }

        // Resize array capacity to new_capacity (will shrink to fit)
        void resize(int new_capacity)
        {
            T* new_array = new T[new_capacity];

            if (new_capacity < number_of_items) {
                number_of_items = new_capacity;
            }
            for (int i = 0; i < number_of_items; ++i) {
                new_array[i] = array[i];
            }

            T* old_array = array;
            array = new_array;
            delete[] old_array;

            capacity = new_capacity;
        }

        void push(const T& data)
        {
            if (number_of_items == capacity) {
                resize(2 * capacity);
            }
            array[number_of_items++] = data;
        }

        T pop()
        {
            if (is_empty()) {
                throw std::logic_error("Error: Poping from empty stack!");
            }

            if (number_of_items == capacity / 4) {
                resize(capacity / 2);
            }
            return array[--number_of_items];
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

        // Maximum number of items the stack can hold
        int max_size() const
        {
            return capacity;
        }

        // Iterator pointing to the top of the stack
        Iterator begin() const
        {
            return Iterator(array, number_of_items - 1);
        }

        // Iterator pointing to the one position below the bottom
        Iterator end() const
        {
            return Iterator(array, -1);
        }

    private:
        int number_of_items = 0;
        int capacity = 1;
        T* array = new T[1];

        class Iterator {
        public:
            Iterator(T* array, int index) : array(array), index(index) {}
            Iterator& operator++()
            {
                --index;
                return *this;
            }
            bool operator!=(const Iterator& other) const { return index != other.index; }
            const T& operator*() const { return array[index]; }
        private:
            T* const array;
            int index;
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
            number_of_items = other.number_of_items;
            capacity = other.capacity;
            head = 0;
            tail = number_of_items - 1;

            delete[] array;
            array = new T[capacity];
            int i = -1;
            for (const T& elem : other) {
                array[++i] = elem;
            }
        }

        Queue& operator=(const Queue& other)
        {
            if (this == &other) {
                return *this;
            }

            number_of_items = other.number_of_items;
            capacity = other.capacity;
            head = 0;
            tail = number_of_items - 1;

            delete[] array;
            array = new T[capacity];
            int i = -1;
            for (const T& elem : other) {
                array[++i] = elem;
            }

            return *this;
        }

        ~Queue()
        {
            delete[] array;
        }

        // Resize array capacity to new_capacity (will shrink to fit)
        void resize(int new_capacity)
        {
            T* new_array = new T[new_capacity];
            if (new_capacity < number_of_items) {
                number_of_items = new_capacity;
            }
            for (int i = 0; i < number_of_items; ++i) {
                new_array[i] = array[(head + i) % capacity];
            }

            T* old_array = array;
            array = new_array;
            delete[] old_array;
            capacity = new_capacity;
            head = 0;
            tail = number_of_items - 1;
        }

        void push(const T& data)
        {
            if (number_of_items == capacity) {
                resize(2 * capacity);
            }

            tail = (tail + 1) % capacity;
            array[tail] = data;
            ++number_of_items;
        }

        T pop()
        {
            if (is_empty()) {
                throw std::logic_error("Error: Poping from empty queue!");
            }

            if (number_of_items == capacity / 4) {
                resize(capacity / 2);
            }
            T data = array[head];
            head = (head + 1) % capacity;
            --number_of_items;

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

        // Maximum number of items the queue can hold
        int max_size() const
        {
            return capacity;
        }

        // Iterator pointing to the front
        Iterator begin() const
        {
            return Iterator(array, head, capacity);
        }

        // Iterator pointing to one position after the back
        Iterator end() const
        {
            return Iterator(array, tail + 1, capacity);
        }

    private:
        int head = 0;
        int tail = 0;
        int number_of_items = 0;
        int capacity = 1;
        T* array = new T[1];

        class Iterator {
        public:
            Iterator(T* array, int index, int capacity)
                : array(array), index(index), capacity(capacity)
            {
            }
            Iterator& operator++()
            {
                index = (index + 1) % capacity;
                return *this;
            }
            bool operator!=(const Iterator& other) const { return index != other.index; }
            const T& operator*() const { return array[index]; }
        private:
            T* const array;
            int index;
            int capacity;
        };
    };

#pragma endregion Queue


#pragma region RandomizedQueue

    template <class T>
    class RandomizedQueue {
    public:
        RandomizedQueue()
        {
        }

        RandomizedQueue(const RandomizedQueue& other)
        {
            number_of_items = other.number_of_items;
            capacity = other.capacity;
            delete[] array;
            array = new T[capacity];
            for (int i = 0; i < number_of_items; ++i) {
                array[i] = other.array[i];
            }
        }

        RandomizedQueue& operator=(const RandomizedQueue& other)
        {
            if (this == &other) {
                return *this;
            }

            number_of_items = other.number_of_items;
            capacity = other.capacity;
            delete[] array;
            array = new T[capacity];
            for (int i = 0; i < number_of_items; ++i) {
                array[i] = other.array[i];
            }

            return *this;
        }

        ~RandomizedQueue()
        {
            delete[] array;
        }

        // Resize array capacity to new_capacity (will shrink to fit)
        void resize(int new_capacity)
        {
            T* new_array = new T[new_capacity];
            if (new_capacity < number_of_items) {
                number_of_items = new_capacity;
            }
            for (int i = 0; i < number_of_items; ++i) {
                new_array[i] = array[i];
            }

            T* old_array = array;
            array = new_array;
            delete[] old_array;
            capacity = new_capacity;
        }

        void push(const T& data)
        {
            if (number_of_items == capacity) {
                resize(2 * capacity);
            }
            array[number_of_items++] = data;
        }

        T sample()
        {
            if (is_empty()) {
                throw std::logic_error("Error: Queue is empty!");
            }

            int i = random_number(number_of_items - 1);
            return array[i];
        }

        T pop()
        {
            if (is_empty()) {
                throw std::logic_error("Error: Poping from empty queue!");
            }

            if (number_of_items == capacity / 4) {
                resize(capacity / 2);
            }
            int i = random_number(number_of_items - 1);
            std::swap(array[i], array[number_of_items - 1]);

            return array[--number_of_items];
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

        // Maximum number of items the queue can hold
        int max_size() const
        {
            return capacity;
        }

        // Beginning iterator, iterates randomly
        Iterator begin() const
        {
            return Iterator(array, 0, number_of_items);
        }

        // Ending iterator, iterates randomly
        Iterator end() const
        {
            return Iterator(array, -1, number_of_items);
        }

    private:
        // Generate a random integer between [0, max]
        static int random_number(int max)
        {
            using namespace std;

            int seed = static_cast<int>(chrono::system_clock::now().time_since_epoch().count());
            mt19937 generator(seed);
            uniform_int_distribution<int> distribution(0, max);
            return distribution(generator);
        }

        int number_of_items = 0;
        int capacity = 1;
        T* array = new T[1];

        class Iterator {
        public:
            Iterator(T* array, int index, int n) : array(array), index(index)
            {
                if (this->index == -1) {
                    return;
                }

                this->index = random_number(n - 1);
                indices.reserve(n - 1);
                for (int i = 0; i < n; ++i) {
                    if (i != this->index) {
                        indices.push_back(i);
                    }
                }
            }
            Iterator& operator++()
            {
                if (indices.empty()) {
                    index = -1;
                }
                else {
                    int i = random_number(indices.size() - 1);
                    index = indices[i];
                    std::swap(indices[i], indices.back());
                    indices.pop_back();
                }
                return *this;
            }
            bool operator!=(const Iterator& other) const { return index != other.index; }
            const T& operator*() const { return array[index]; }
        private:
            T* const array;
            int index;
            std::vector<int> indices;
        };
    };

#pragma endregion RandomizedQueue

}
