#include <vector>
#include <iostream>

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

// Driver program to test above functions
int main()
{
    int freq[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(freq)/sizeof(freq[0]);
    int *BITree = constructBITtree(freq, n);
    cout << "Sum of elements in arr[0..5] is "
        << getSum(BITree, 5);

    // Let use test the update operation
    freq[3] += 6;
    updateBIT(BITree, n, 3, 6); //Update BIT for above change in arr[]

    cout << "\nSum of elements in arr[0..5] after update is "
        << getSum(BITree, 5) << "\n";

    return 0;
}