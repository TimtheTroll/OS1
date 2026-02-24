#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class queue {
    private:
    template <typename Iter>
    bool search(Iter &arr, T x) {
        int high = arr.size()-1;
        int low = 0;

        while (low <= high) {
            int mid(low + (high - low) / 2);

            if (arr[mid] == x) {
                return true;
            }
            else {
                if (x < arr[mid]) {high = mid - 1;}
                else low = mid + 1;
            }
        }    
        return false;
    }

    public:
        T *array;
        int head;
        int tail;
        int len;

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
            if (tail++ < len && tail != head) {
                array[tail] = value;
                tail++;
                return false;
            }
            else if (tail++ < len && tail == head) {
                array[tail] = value;
                tail++;
                if (head++ < len) {
                    head++;
                }
                else {head = 0;}
                return true;
            }
            else if (tail++ >= len && tail++ != head) {
                array[tail] = value;
                tail = 0;
                return false;
            }
            else if (tail++ >= len && tail == head) {
                array[tail] = value;
                tail = 0;
                if (head++ < len) {
                    head++;
                }
                else {head = 0;}
                return true;
            }
        }
        bool search(T value) {
            return search(array, value);
        }
};

#endif