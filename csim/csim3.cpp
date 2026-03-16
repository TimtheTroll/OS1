// Almost set up solution that didn't turn out to be heading the right direction.
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int getSum(int BITtree[], int index) {
    int sum = 0;
    index++;
    while (index > 0) {
        sum += BITtree[index];
        index -= index & (-index);
    }
    return sum;
}

void updateBIT(int BITtree[], int n, int index, int val) {
    index++;
    while (index <= n) {
        BITtree[index] += val;
        index += index & (-index);
    }
}

int *constructBITtree(int arr[], int n) {
    int *BITtree = new int[n+1];
    for (int i = 0; i < n; i++) {
        updateBIT(BITtree, n, i, arr[i]);
    }
    return BITtree;
}

void eat_input (std::string &input) {
    input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) {
        return !std::isdigit(c) && !std::isspace(c) && c != '-';
    }), input.end());
}

int main() {
    int cases, size = 0;
    int *misses;

    std::cin >> cases;
    for (int t = 0; t < cases; t++) {

    }

    misses = new int[cases];
    for (int i = 0; i < cases; i++) {misses[i] = 0;}

    std::string input;
    std::getline(std::cin, input);

    while (input != "END") {
        std::string prefix = input.substr(0, 4);
        eat_input(input);

        if (prefix == "RANG") {
            int i = 0;
                  
        }

        if (prefix == "ADDR") {
            int i = 0;
              
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
