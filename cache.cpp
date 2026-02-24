#include "queue.h"
#include <iostream>
#include <strings.h>
#include <vector>

int main() {
    int cases, size;
    std::vector<int> caches;
    std::cin >> cases;
    for (; cases > 0; cases --) {
        std::cin >> size;
        caches.push_back(size);
    }
    for (int v : caches) {
        queue<int> cache(v);
    }
}