//#include "queue.h"
#include <iostream>
#include <strings.h>
#include <vector>
#include <algorithm>
#include <sstream>

template <typename T>
class queue {
    private:
    template <typename Iter>

    bool search(Iter &arr, T x) {
        std::cout << "len: " << len << " - ";
        print();
        for (int i = 0; i < used; i++) {
            if (array[(head + i) % len] == x) {
                std::cout << "\n\n HIT \n\n";
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
};

void eat_input (std::string &input) {
    input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) {
        return !std::isdigit(c) && !std::isspace(c) && c != '-';
    }), input.end());
}

int range(queue<int> &q, std::string &numbers) {
    int times = 0, change = 0, num = 0, misses = 0;
    std::stringstream ss(numbers);
    ss >> num >> change >> times;
    for (; times > 0; times--) {
        //std::cout << "range: " << num << " ";
        if (!q.search(num)) {
            misses ++;
            q.push(num);
        }
        num += change;
    }
    return misses;
}

int addr(queue<int> &q, std::string &numbers) {
    std::stringstream ss(numbers);
    int num = 0, misses = 0;
    ss >> num;
    //std::cout << "addr: " << num << "\n";
    if (!q.search(num)) {
        misses ++;
        q.push(num);
    }
    return misses;
}

int main() {
    int cases, size = 0;
    std::vector<int> caches;
    std::vector<queue<int>> cs;
    int *misses;

    std::cin >> cases;
    for (int t = 0; t < cases; t++) {
        std::cin >> size;
        //queue<int> cache(size);
        //cs.push_back(cache);   
        cs.emplace_back(size);     
    }
    misses = new int[cases];
    for (int i = 0; i < cases; i++) {misses[i] = 0;}

    std::string input;
    std::getline(std::cin, input);

    while (input != "END") {
        //std::cout << input << "\n";
        std::string prefix = input.substr(0, 4);
        eat_input(input);

        if (prefix == "RANG") {
            int i = 0;
            for (queue<int>& cache : cs) {
                misses[i] += range(cache, input);
                //cache.print();
                i++;
            }            
        }

        if (prefix == "ADDR") {
            int i = 0;
            for (queue<int>& cache : cs) {
                misses[i] += addr(cache, input);
                //cache.print();
                i++;
            }  
        }

        if (prefix == "STAT") {
            for (int i = 0; i < cases; i++) {
                std::cout << misses[i];
                if (i != cases-1) {std::cout << " ";}
                misses[i] = 0;
            }
            std::cout << "\n";
        }
        std::getline(std::cin, input);
    }
    delete[] misses;
    return 0;
}