#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

template <typename T>
class queue {
    private:
    template <typename Iter>
    bool search(Iter &arr, T x) {
        //std::cout << "len: " << len << "\n";
        for (int i = 0; i < len; i++) {
            if (arr[i] == x) {return true;}
            //std::cout << arr[i] << " ";
        }        
        return false;
    }

    public:
        T *array;
        int head;
        int tail;
        int len = 0;

        queue(int size) {
            array = new T[size];
            head, tail;
            len = size - 1;
        }
        queue() {
            array = new T[16];
            head, tail;
            len = 15;
        }
        T pop() {
            T value = array[head];
            if (head++ < len) {
                head++;
            }
            else {head = 0;}
            return value;
        }
        bool push(T value) {
            // 1. Calculate the next position for the tail
            int next_tail = (tail + 1) % len;

            // 2. Check if the queue is full (tail hits head)
            if (next_tail == head) {
                // Option A: Overwrite the oldest data (Standard Circular Buffer)
                // Move head forward to "drop" the old value
                head = (head + 1) % len; 
            }

            // 3. Store the value safely
            array[tail] = value;
    
            // 4. Update the tail
            tail = next_tail;

            return true;
        }
        bool search(T value) {
            return search(array, value);
        }
};

#endif