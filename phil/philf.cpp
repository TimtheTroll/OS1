#include <iostream>
#include <vector>
#include <string>

int size(int A) {
    int base = 1, count = 1;
    while (A > base) {
        base*=2;
        count ++;
    }
    return count;
}


int r_bit(int n, int index) {
    // 1. Create a mask for the bits below the index
    // If index is 2, mask is 00...011
    int lowMask = (1 << index) - 1;
    
    int lowPart = n & lowMask;              // Keep bits below index
    int highPart = n >> (index + 1);        // Shift everything above index down by 1
    
    return (highPart << index) | lowPart; // Recombine
}

int to_bin(int n) {
    int factor = 1;
    int result = 0;
    while (n > 0) {
        result += (n % 10) * factor; // Take the last digit (0 or 1)
        n /= 10;                     // Remove the last digit
        factor *= 2;                 // Move to next power of 2
    }
    return result;
}

int main() {
    int A = 0, A2;
    int S = 0;
    int examples;
    int len, middle, mid1, mid2, val;

    std::cin >> examples;    
    for (int i = 0; i < examples; i++) {
        S = 0;
        std::cin >> A2;
        A = to_bin(A2);
        std::cout << "A: " << A << "\n";
        len = size(A);
        std::cout << "Size: " << len << "\n";
        while (len > 1) {
            std::cout << "A%2: " << A%2 << "\n";
            if (A % 2 == 1) {
                middle = (len-1)/2;
                val = (A & (1 << middle)) >> middle;
                std::cout << "removing bit #" << middle << " = " << val << " A: " << A << " after removal: ";
                A = r_bit(A, middle);
                std::cout << A << " S: ";
                S = S << 1;
                S += val;
                std::cout << S << "\n";
            }
            else {
                mid1 = (len-1)/2;
                mid2 = mid1 + 1;
                if ((A & (1 << mid1) == 1) && (A & (1 << mid2) == 0)) {
                    val = (A & (1 << mid1)) >> mid1;
                    std::cout << "removing bit #" << mid1 << " = " << val << " A: " << A << " after removal: ";
                    A = r_bit(A, mid1);
                    std::cout << A << " S: ";
                    S = S << 1;
                    S += val;
                    std::cout << S << "\n";
                }
                else if ((A & (1 << mid2) == 1) && (A & (1 << mid1) == 0)) {
                    val = (A & (1 << mid2)) >> mid2;
                    std::cout << "removing bit #" << mid2 << " = " << val << " A: " << A << " after removal: ";
                    A = r_bit(A, mid2);
                    std::cout << A << " S: ";
                    S = S << 1;
                    S += val;
                    std::cout << S << "\n";
                }
                else {
                    val = (A & (1 << mid2)) >> mid2;
                    std::cout << "removing bit #" << mid2 << " = " << val << " A: " << A << " after removal: ";
                    A = r_bit(A, mid2);
                    std::cout << A << " S: ";
                    S = S << 1;
                    S += val;
                    std::cout << S << "\n";
                }
            }
            len = size(A);
            std::cout << "Size: " << len << "\n";
        }
        S = S << 1;
        S += A;
        std::cout << "Case #" << i + 1 << ": " << S << "\n";
    }
}