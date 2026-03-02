#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

template <typename T>
class queue {
    private:
    template <typename Iter>
    bool search(Iter &arr, T x) {
        std::cout << "len: " << len << " - ";
        print();
        for (int i = 0; i < used; i++) {
            if (array[(head + i) % len] == x) {
                return true;
            }
        }
        std::cout << " MISS\n";
        return false;
    }

    public:
        T *array;
        int head = 0;
        int tail = 0;
        int len = 0;
        int used = 0;

        queue(int size) {
            array = new T[size];
            head = 0, tail = 0;
            len = size;
        }
        queue() {
            array = new T[16];
            head = 0, tail = 0;
            len = 16;
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
            int next_tail = (tail + 1) % len;

            if (next_tail == head) {
                head = (head + 1) % len; 
            }

            array[tail] = value;
            tail = next_tail;

            if (used != len) {used ++;}

            return true;
        }
        bool search(T value) {
            return search(array, value);
        }

        void print() {
            for (int i = 0; i < len; i++) {
                std::cout << array[i] << " ";
            }
            std::cout << "\n";
        }

        ~queue() {
            delete[] array;
        }
};

#endif