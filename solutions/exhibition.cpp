/* Exhibition - UVA 11348 - Solution by Timothy Cook
 * CPS210 - 3/8/2026
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    unordered_map<int, vector<int>> stamps;
    vector<double> people;
    int cases, stamp, p_count, s_count;
    double count = 0;

    cin >> cases;
    for (int i = 0; i < cases; i++) {
        cin >> p_count;
        for (int j = 0; j < p_count; j++) {
            people.push_back(0);
            cin >> s_count;
            for (int k = 0; k < s_count; k++) {
                cin >> stamp;
                stamps[stamp].push_back(j);
            }
        }
        for (const auto& [key, vec] : stamps) {
            if (!vec.empty()) {
                if (vec.size()>1) {
                    int last = vec[0];
                    bool uniq;
                    for (int v = 1; v < vec.size(); v++) {
                        if (vec[v] == last) {
                            uniq = true;
                        }
                        else {uniq = false;}
                    }
                    if (uniq) {
                            people[vec[0]]++;
                            count++;
                        }
                }
                else {
                    people[vec[0]]++;
                    count++;
                }
            }          
        }
        cout << "Case " << i+1 << ": ";
        for (int j = 0; j < p_count; j++) {
            double percent = people[j] / count;
            if (!isnan(percent) && j != p_count-1) {
                printf("%.6f%% ", percent * 100);
            }
            else if (!isnan(percent) && j == p_count-1) {
                printf("%.6f%%", percent * 100);
            }
        }
        putchar('\n');
        stamps.clear();
        people.clear();
        count = 0;
    }
}