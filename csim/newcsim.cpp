/* UVA 11423 "Cache Simulator" (Deceptive name :( ) Solution by Timothy Cook
 * After finding a nice seeming solution to this problem that actually simulates the cache,
 * I discovered that this problem isn't actually asking for that AT ALL. I hate this solution
 * because it is boring, but it does work.
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

// macros for cleaner code
#define GET_PARENT(i) (i -= i & -i) // this function gets the 'parent' node in a fenwick tree
#define GET_NEXT(i)   (i += i & -i) // this function gets the 'child' node in a fenwick tree

#define MAX 31 // maximum number of caches
#define MAX_N 10000100 // maximum size of n
#define MAXARR 20000100 // this is slightly larger than the largest number used

typedef vector<int> v_int;

int N; // global variable for the number of caches
int misses[MAX]; // same as my better solution, misses is an array of integers
int sizes[MAX]; // array of the sizes used
int been_added[MAXARR]; // array with an index for EVERY number that could be queried (~64MB space)
// The been_added array is so that we can know whether a value has ever been encountered in O(1) time
int counter = 0; // counter for counting the number of accesses done

// BELOW: fenwick tree class
class fenwick {
    private:
        v_int data; // data array (in our case, integers)
    public:
    // Constructor functions:
        fenwick() {}
        fenwick(int n) { 
  	        data.assign(n + 1, 0);
        }

        // update just updates the tree by adding a number to an index and all of its relevant parent indexes
        void update(int index, int delta) {
            while (index < data.size()) { // while we are in the indexes allowed...
                data[index] += delta; // add our value to the current index...
                GET_NEXT(index); //... and get the next index (moving up the tree)
            }
        }
        
        // query finds the sum of the first index number of elements
        int query(int index) {
            int sum = 0; // create sum variable
            while (index != 0) { // while we are in the tree data structure...
                sum += data[index]; // add the value at index to sum
                GET_PARENT(index); // get the next relevant index (moving down the tree)
            }
            return sum;
        }

        // range query just queries on a range of indexes
        int rangeQuery(int l_index, int r_index) {
            return query(r_index) - query(l_index - 1);
        }
};

fenwick ft(MAX_N); // create a fenwick tree large enough for all of the unique values we could cache

// this function "accesses" the cache
void access(int value) {
    if (been_added[value]) { // if the value has been accessed before...
        // sum the number of values (accesses) between the time we access the value, and the last time it was accessed
        int addressed_values = ft.rangeQuery(been_added[value], counter);
        int index = N;
        // for every cache...
        for (int i = 0; i < N; i++) {
            if (sizes[i] >= addressed_values) { // if the number of unique values accessed since the value was accessed
                // is greater than the size of the cache, then the value is no longer in the cache and therefore a MISS.
                index = i;
                break; // break since all of the caches are also too small to still contain this value
            }
        }
        // for all of the caches too small to contain this value, increment their misses
        for (int i = 0; i < index; i++) {
            misses[i]++;
        }
        // now we update the tree to remove the last time we accessed this value
        ft.update(been_added[value], -1);
    }
    // The value has never been seen before and is therefore a miss...
    else {
        // increment misses for every cache size
        for (int i = 0; i < N; i++) {
            misses[i]++;
        }
    }
    // increment the count of accesses
    counter ++;
    // set the value to say that we just accessed it
    been_added[value] = counter;
    // update the tree to also say we just accessed this value
    ft.update(been_added[value], 1);
}

int main() {
    ios_base::sync_with_stdio(false); // speed hack for IO
    cin >> N; // get the number of caches and set up their sizes
    for (int i = 0; i < N; i++) {
        cin >> sizes[i];
    }

    string input; // BELOW: get input and repeat until we get "END"
    while ((cin >> input) && (input != "END")) {
        // RANGE: access a range of values (smarter code than the OG solution)
        if (input == "RANGE") {
            int b, y, n;
            cin >> b >> y >> n;
            for (int i = 0; i < n; i++) {
                access(b + y * i);
            }
        }
        // ADDR: address one value
        if (input == "ADDR") {
            int value;
            cin >> value;
            access(value);
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