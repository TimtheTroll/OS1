/* Actual LRU Cache simulator - Timothy Cook (tcook548)
 * This solution works very well for UVA 11423 with the exception that it is too slow
 * Since I'm feeling cheated by the actual solution for UVA 11423, I'm still including this solution.
*/

#include <iostream>
#include <strings.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>
#include <list>
#include <unordered_map>

// We are using a hash map of pointers to nodes in the linked list to speed up queries
typedef std::unordered_map<int, std::list<int>::iterator> itermap;

// "fat list" -> list with an included size to tell how big it can be
struct fat_list {
    std::list<int> cache;
    int size;
};

// searching function, no longer used
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

// printing function for debugging
void fat_list_print(fat_list &list) {
    std::cout << "{";
    for (int n : list.cache) {
        std::cout << n << " ";
    }
    std::cout << "}\n";
}

// map printing function for debugging
void map_print(itermap &map) {
    std::cout << "[[";
    for (auto &it : map) {
        std::cout << *it.second << " ";
    }
    std::cout << "]]\n";
}

// this function just cleans up input
void eat_input (std::string &input) {
    input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) {
        return !std::isdigit(c) && !std::isspace(c) && c != '-';
    }), input.end());
}

// add_node adds a node to a list and the map
void add_node(fat_list &list, int value, itermap &map) {
    if (list.cache.size() >= list.size) { // if we are over the max size or equal to it...
        int lru_val = list.cache.back(); // find the last used value (the end of the list)
        map.erase(lru_val); // remove it from the map first to prevent dangliing pointers
        list.cache.pop_back(); // then remove it from the list
    }
    list.cache.push_front(value); // now we can add another node knowing that there is room
    map[value] = list.cache.begin(); // also add it to the map
}

// range queries a range of values on the list
int range(fat_list &list, std::string &numbers, itermap &map) {
    int times = 0, change = 0, num = 0, misses = 0;
    std::stringstream ss(numbers);
    ss >> num >> change >> times;
    // for the number of times...
    for (; times > 0; times--) {
        // search the map to see if the value is in there
        auto it = map.find(num);
        if (it != map.end()) {
            // HIT: splice the node to the front of the list to indicate that it was just used
            list.cache.splice(list.cache.begin(), list.cache, it->second);
        }
        else {
            // MISS: add the value to the list and increment misses
            add_node(list, num, map);
            misses++;
        }
        // update the number we're querying
        num += change;
    }
    return misses;
}

// addr queries one number. It's the same code as range minus a for loop
int addr(fat_list &list, std::string &numbers, itermap &map) {
    std::stringstream ss(numbers);
    int num = 0, misses = 0;
    ss >> num;
    auto it = map.find(num);
    if (it != map.end()) {
            list.cache.splice(list.cache.begin(), list.cache, it->second);
        }
        else {
            add_node(list, num, map);
            misses++;
        }
    return misses;
}

int main() {
    int cases, size = 0;
    std::vector<fat_list> cs;
    std::vector<itermap> cs2;
    int *misses;

    // get input and set up the vector of lists
    std::cin >> cases;
    for (int t = 0; t < cases; t++) {
        std::cin >> size;
        fat_list temp;
        temp.size = size;
        cs.push_back(temp);
        itermap map;
        cs2.push_back(map);
    }

    misses = new int[cases]; // misses is stored as an array
    for (int i = 0; i < cases; i++) {misses[i] = 0;} // make sure to clear misses

    std::string input;
    std::getline(std::cin, input); // get a line of input

    while (input != "END") { // while we aren't at the end...
        std::string prefix = input.substr(0, 4); // grab the first four letters of the input
        eat_input(input); // clean up input so that it's a list of numbers

        if (prefix == "RANG") { // do a range of queries on the caches
            int i = 0;
            for (int j = 0; j < cs.size(); j++) {
                misses[i] += range(cs[j], input, cs2[j]);
                i++;
            }      
        }

        if (prefix == "ADDR") { // address a value on every cache
            int i = 0;
            for (int j = 0; j < cs.size(); j++) {
                misses[i] += addr(cs[j], input, cs2[j]);
                i++;
            }  
        }
 
        if (prefix == "STAT") { // print the current stats and reset misses
            for (int i = 0; i < cases; i++) {
                std::cout << misses[i];
                if (i != cases-1) {std::cout << " ";}
                misses[i] = 0;
            }
            std::cout << "\n";
        }
        std::getline(std::cin, input); // get another line of input
    }
    delete[] misses; // "clean up"
    return 0;
}