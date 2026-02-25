#include "queue.h"
#include <iostream>
#include <strings.h>
#include <vector>
#include <algorithm>
#include <sstream>


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
        queue<int> cache(size);
        cs.push_back(cache);        
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
            for (queue cache : cs) {
                misses[i] += range(cache, input);
                i++;
            }            
        }

        if (prefix == "ADDR") {
            int i = 0;
            for (queue cache : cs) {
                misses[i] += addr(cache, input);
                i++;
            }  
        }

        if (prefix == "STAT") {
            for (int i = 0; i < cases; i++) {
                std::cout << misses[i] << " ";
                misses[i] = 0;
            }
            std::cout << "\n";
        }
        std::getline(std::cin, input);
    }
    return 0;
}