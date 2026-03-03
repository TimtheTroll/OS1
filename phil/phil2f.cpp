#include <iostream>
#include <vector>
#include <string>


int main() {
    std::string A;
    int examples;
    long long int out = 0;
    int right, left, len;

    std::cin >> examples;
    std::getchar(); // throw away extra newline.

    for (int i = 0; i < examples; i++) {
        std::getline(std::cin, A);
        if (A.size() % 2 == 1) {
            right = A.size()/2;
            left = A.size()/2 - 1;
        }
        else {
            right = A.size()/2 + 1;
            left = A.size()/2;
        }
        len = (left+1) + (A.size() - right);
        while (left+1 > 0 || (A.size() - right) > 0) {
            //std::cout << "left: " << left << " right: " << right << " rsize: " << (A.size() - right) << "\n";
            len = (left+1) + (A.size() - right);
            //std::cout << "len: " << len << "\n";
            if (len % 2 == 1) {
                //if (left == right) {
                //    out = out << 1;
                //    out += (A[right] - '0');
                //    right++, left--;                    
                //}
                if (left+1 > A.size()-right) {
                    out = out << 1;
                    out += (A[left] - '0');
                    left--;
                }
                else if (A.size()-right > left+1) {
                    out = out << 1;
                    out += (A[right] - '0');
                    right++;
                }
            }
            else {
                if (A[right]-'0' > A[left]-'0') {
                    out = out << 1;
                    out += (A[right] - '0');
                    right++;
                }
                else if (A[right]-'0' < A[left]-'0') {
                    out = out << 1;
                    out += (A[left] - '0');
                    left--;
                }      
                else {
                    out = out << 1;
                    out += (A[right] - '0');
                    right++;
                }              
            }
            std::cout << "l: " << A[left] << " r: " << A[right] << "\n";
            std::cout << "out: " << out << "\n";
        }
        //out = out << 1;
        //out += (A[left] - '0');
        //left--;
        std::cout << "Case #" << i+1 << ": " << out << "\n";
        out = 0;
    }
}