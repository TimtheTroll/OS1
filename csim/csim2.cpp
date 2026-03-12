#include <iostream>
#include <strings.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>
#include <list>
#include <unordered_map>

typedef std::unordered_map<int, std::list<int>::iterator> itermap;

struct fat_list {
    std::list<int> cache;
    int size;
};

int fat_list_search(fat_list &list, int value) {
    int index = 0;
    for (int n : list.cache) {
        index++;
        if (n == value) {
            return index;
        }
    }
    return -1;
}

void fat_list_print(fat_list &list) {
    std::cout << "{";
    for (int n : list.cache) {
        std::cout << n << " ";
    }
    std::cout << "}\n";
}

void eat_input (std::string &input) {
    input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) {
        return !std::isdigit(c) && !std::isspace(c) && c != '-';
    }), input.end());
}

void add_node(fat_list &list, int value){//, itermap &map) {
    if (list.cache.size() < list.size) {
        list.cache.push_front(value);
        //map[value] = 
        //fat_list_print(list);
    }
    else {
        list.cache.erase(std::prev(list.cache.end()));
        list.cache.push_front(value);
    }
}

int range(fat_list &list, std::string &numbers) {
    int times = 0, change = 0, num = 0, misses = 0;
    std::stringstream ss(numbers);
    ss >> num >> change >> times;
    for (; times > 0; times--) {
        //fat_list_print(list);
        if (int n = fat_list_search(list, num) != -1) {
            auto it = std::next(list.cache.begin(), n);
            list.cache.splice(list.cache.begin(), list.cache, it);
        }
        else {
            add_node(list, num);
            misses++;
        }
        num += change;
    }
    return misses;
}

int addr(fat_list &list, std::string &numbers) {
    std::stringstream ss(numbers);
    int num = 0, misses = 0;
    ss >> num;
    //fat_list_print(list);
    if (int n = fat_list_search(list, num) != -1) {
            auto it = std::next(list.cache.begin(), n);
            list.cache.splice(list.cache.begin(), list.cache, it);
        }
        else {
            add_node(list, num);
            misses++;
        }
    return misses;
}

int main() {
    int cases, size = 0;
    std::vector<fat_list> cs;
    itermap map;
    int *misses;

    std::cin >> cases;
    for (int t = 0; t < cases; t++) {
        std::cin >> size;
        fat_list temp;
        temp.size = size;
        cs.push_back(temp);
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
            for (auto& cache_ptr : cs) {
                misses[i] += range(cache_ptr, input);
                i++;
            }      
        }

        if (prefix == "ADDR") {
            int i = 0;
            for (auto& cache_ptr : cs) {
                misses[i] += addr(cache_ptr, input);
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