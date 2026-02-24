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
    int times, change, num, misses = 0;
    std::stringstream ss(numbers);
    ss >> num;
    ss >> change;
    ss >> times;
    for (; times > 0; times--) {
        if (q.search(num)) {
            misses ++;
            q.push(num);
        }
        num += change;
    }
    return misses;
}

int main() {
    int cases, size;
    std::vector<int> caches;
    std::vector<queue<int>> cs;
    std::vector<int> misses;

    std::cin >> cases;
    for (; cases > 0; cases --) {
        std::cin >> size;
        caches.push_back(size);
    }
    for (int v : caches) {
        queue<int> cache(v);
        cs.push_back(cache);
    }

    std::string input;
    std::getline(std::cin, input);

    while (input != "END") {
        std::string prefix = input.substr(0, 4);
        eat_input(input);

        if (prefix == "RANG") {
            for (queue cache : cs) {
                range(cache, prefix);
            }            
        }

        if (prefix == "ADDR") {
            std::cout << "ADDler\n";
        }

        if (prefix == "STAT") {
            std::cout << "STATs\n";
        }
        //std::cout << input << "\n";
        std::getline(std::cin, input);
    }
}