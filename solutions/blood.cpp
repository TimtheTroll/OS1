// Last Blood - UVA 12667 - Timothy Cook - CPS210

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>

struct sub {
    int time;
    int team;
    char problem;
    std::string completed;
};

typedef std::vector<sub> v_sub;
typedef std::vector<v_sub> vv_sub;

int main() {
    int problems, teams, subs;
    sub latest[26];
    std::cin >> problems >> teams >> subs;
    sub t_b[teams+1][26];
    
    for (int i = 0; i < problems; i++) {
        sub temp = {0, 0, 'A', "No"};
        latest[i] = temp;
    }
    for (int i = 0; i < teams+1; i++) {
        for (char c = 'A'; c < 'Z'+1; c++) {
            sub temp = {0, 0, 'A', "No"};
            int idx = c-'A';
            t_b[i][idx] = temp;
        }        
    }

    sub submission;
    int idx = 0, idx2 = 0;
    for (int i = 0; i < subs; i++) {
        std::cin >> submission.time;
        std::cin >> submission.team;
        std::cin >> submission.problem;
        std::cin >> submission.completed;
        //std::cout << " {" << submission.problem << " t:" << submission.time << " team:" << submission.team << " " << submission.completed << "}\n";

        if (submission.completed == "Yes") {
            if (t_b[submission.team][submission.problem-'A'].completed == "No") {
                t_b[submission.team][submission.problem-'A'] = submission;
                latest[submission.problem-'A'] = submission;
            }
        }
    }
    for (int i = 0; i < problems; i++) {
        if (latest[i].completed == "No") {
            char temp = 'A' + i;
            std::cout << temp << " - -\n";
        }
        else {
            std::cout << latest[i].problem << " " << latest[i].time << " " << latest[i].team << "\n";
        }
    }

    // for (int i = 0; i < problems; i++) {
    //     if (!probs[i].empty()) {
    //         sub temp = probs[i].front();
    //         probs[i].pop();
    //         while (!probs[i].empty() && temp.completed == "No") {
    //             sub temp = probs[i].front();
    //             probs[i].pop();
    //         } 
    //         std::cout << temp.problem << " " << temp.time << " " << temp.team << "\n";
    //     }
    //     else {
    //         char temp = 'A' + i;
    //         std:: cout << temp << " - -\n";
    //     }
    // }    
}