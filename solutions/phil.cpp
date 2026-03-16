/* UVA 12720 "Algorithm of Phil" Solution by Timothy Cook
*/

#include <iostream>
#include <string>
#define MOD 1000000007 // number to mod by later (prevents overflow?)

int main() {
    std::string A;
    long long out = 0;
    int right, left, examples;

    std::cin >> examples; // grab the number of examples
    std::getchar(); // throw away extra newline.

    for (int i = 0; i < examples; i++) { // for each example...
        std::getline(std::cin, A); // get the number
        if (A.size() % 2) { // if the number has an odd number of bits...
            right = (A.size() + 1 ) / 2 - 1; // get the exact middle bit
            left = right-1; // set up the left bit for later
            out = out << 1; // shift the output over (currently 0?)
            out += (A[right++] - '0'); // add the number (1 or 0) at the center to the output
            for (int i = right; i < A.size(); i++) { // for half the length of the bit string...
                if (A[right] > A[left]) { // if right bit is larger than left bit...
                    out = (out * 2 + A[right++] - '0') % MOD; // add the right bit
                    out = (out * 2 + A[left--] - '0') % MOD; // and then add the left bit
                }
                else { // otherwise...
                    out = (out * 2 + A[left--] - '0') % MOD; // add the left bit
                    out = (out * 2 + A[right++] - '0') % MOD; // and then the right bit
                } 
            }
        }
        else { // same as code above except we have an even number of bits 
            // and therfore start with slightly different left & right
            right = A.size()/2;
            left = A.size()/2 - 1;
            for (int i = right; i < A.size(); i++) {
                if (A[right] > A[left]) {
                    out = (out * 2 + A[right++] - '0') % MOD;
                    out = (out * 2 + A[left--] - '0') % MOD;
                }
                else {
                    out = (out * 2 + A[left--] - '0') % MOD;
                    out = (out * 2 + A[right++] - '0') % MOD;
                }
            }
        }
        // ouput the final value of output
        std::cout << "Case #" << i+1 << ": " << out << "\n";
        out = 0; // clear output integer for next time
    }
}