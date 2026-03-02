#include <iostream>
#include <vector>
#include <string>


int main() {
    std::string A;
    std::vector<char> S;
    int examples;
    int out = 0;

    std::cin >> examples;
    std::getchar(); // throw away extra newline.

    for (int i = 0; i < examples; i++) {
        std::getline(std::cin, A);
        //std::cout << A << "\n";
        while (A.size() > 0) {
            if ((A.size()+1) % 2 == 0) {
                //std::cout << "A size: " << A.size()+1 << "/2 = " << (A.size()+1) / 2 << "\n";
                int middle = (A.size())/2;
                S.push_back(A[middle]);
                //std::cout << "pushing: " << A[middle] << " from spot " << middle << "\n";
                A.erase(middle, 1);
            }
            else {
                int middle1 = (A.size()-1)/2;
                int middle2 = middle1 + 1;
                if (A[middle1] > A[middle2]) {
                    S.push_back(A[middle1]);
                    //std::cout << "pushing: " << A[middle1] << " from spot " << middle1 << "\n";
                    A.erase(middle1, 1);
                }
                else if (A[middle2] > A[middle1]) {
                    S.push_back(A[middle2]);
                    //std::cout << "pushing: " << A[middle2] << " from spot " << middle2 << "\n";
                    A.erase(middle2, 1);
                }
                else {
                    S.push_back(A[middle1]);
                    //std::cout << "pushing: " << A[middle1] << " from spot " << middle1 << "\n";
                    A.erase(middle1, 1);
                }
            }
        }
        //for (char c : S) {
        //    std::cout << c << " ";
        //}
        //std::cout << "\n";
        for (char c : S) {
            out = out << 1;
            out += (c - '0');
        }
        std::cout << "Case #" << i + 1 << ": " << out << "\n";
        out = 0;
        S.clear();
    }
}