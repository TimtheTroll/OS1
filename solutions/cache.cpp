/* UVA 11423 "Cache Simulator" (Deceptive name :( ) Solution by Timothy Cook
 * After finding a nice seeming solution to this problem that actually simulates the cache,
 * I discovered that this problem isn't actually asking for that AT ALL. I hate this solution
 * because it is boring, but it does work.
*/

#include <vector>
#include <iostream>
#include <string>

using namespace std;
typedef vector<int> v_int;

int N; // global variable for the number of caches
int sizes[31]; // same as my better solution, misses is an array of integers
int misses[31]; // array of the sizes used
int numbers[20000100]; // array with an index for EVERY number that could be queried (~64MB space)
// The been_added array is so that we can know whether a value has ever been encountered in O(1) time
int counter = 0; // counter for counting the number of accesses done

// BELOW: fenwick tree class
class fenwick_tree {
    private:
        v_int data; 
    public:
        fenwick_tree(int size) {
            data.assign(size + 1, 0);
        }

        void update(int i, int value) {
            for (; i < data.size(); i += i & (-i)) data[i] += value;
        }

        int sum(int i) {
            int sum = 0;
            for (; i > 0; i -= i & (-i)) sum += data[i];
            return sum;
        }

        int sumall(int right, int left) {
            return sum(left) - sum(right-1);
        }
};

fenwick_tree ft(10000100); // fenwick tree large enough for all numbers accessed (~10^7)

// this function "accesses" a value in the cache
void address(int value) {
    if (numbers[value]) { // if the value has been accessed before...        
        // sum the number of values (accesses) between the time we access the value, and the last time it was accessed
        int accesses = ft.sumall(numbers[value], counter);
        // for every cache...
        for (int i = 0; i < N; i++) {
            // if the number of unique accesses is larger than the cache size...
            if (accesses > sizes[i]) {
                misses[i] ++; // count it as a miss for that cache
            }
        }
        // now we update the tree to remove the last time we accessed this value
        ft.update(numbers[value], -1); 
    }
    // The value has never been seen before and is therefore a miss...
    else {
        // increment misses for every cache size
        for (int i = 0; i < N; i++) {
            misses[i]++;
        }
    }
    counter++; // increment the count of accesses
    // set the value to say that we just accessed it
    numbers[value] = counter;
    // update the tree to also say we just accessed this value
    ft.update(numbers[value], 1);
}

int main() {
    string input;
    int value, num, change, times;
    cin >> N; // get the number of caches and set up their sizes
    for (int i = 0; i < N; i++) {
        cin >> sizes[i];
    }

    // BELOW: get input and repeat until we get "END"
    while ((cin >> input) && (input != "END")) {
        // ADDR: address one value
        if (input == "ADDR") {
            cin >> value;
            address(value);
        }
        // RANGE: access a range of values (smarter code than the OG solution)
        if (input == "RANGE") {
            cin >> num >> change >> times;
            for (; times > 0; times--) {
                address(num);
                num += change;
            }
        }
        // STAT: print the current misses stats and reset misses to 0;
        if (input == "STAT") {
            for (int i = 0; i < N; i++) {
                if (i != 0) {
                    cout << " ";
                }
                cout << misses[i];
                misses[i] = 0;
            }
            cout << "\n";
        }
    }
}