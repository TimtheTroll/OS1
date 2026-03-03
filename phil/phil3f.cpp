#include <iostream>
#include <string>
#define MOD 1000000007

int main() {
    std::string A;
    long long out = 0;
    int right, left, examples;

    std::cin >> examples;
    std::getchar(); // throw away extra newline.

    for (int i = 0; i < examples; i++) {
        std::getline(std::cin, A);
        if (A.size() % 2) {
            right = (A.size()+1)/2-1;
            left = right-1;
            out = out << 1;
            out += (A[right++] - '0');
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
        else {
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
        std::cout << "Case #" << i+1 << ": " << out << "\n";
        out = 0;
    }
}