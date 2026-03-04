// Last Blood - UVA 12667 - Timothy Cook - CPS210

#include <iostream>
#include <vector>
#include <string>
#include "stack.h"
#include <cstring>

struct sub {
    int time;
    int team;
    char problem;
    std::string completed;
};

void print_stuff(std::vector<Stack<sub>> &probs) {
    sub temp;
    for (Stack<sub> v : probs) {
        while (!v.empty()) {
            temp = v.pop();
            std::cout << " (" << temp.time << ", " << temp.team << ", " << temp.problem << ", " << temp.completed << ") ";
        }
        std::cout << "\n";
    }
}

int main() {
    int problems, teams, subs;
    std::vector<Stack<sub>> probs;
    std::cin >> problems >> teams >> subs;
    char key[26];
    key[0] = '0';
    
    for (int i = 0; i < problems; i++) {
        Stack<sub> stack;
        probs.push_back(stack);
    }

    sub submission;
    int idx = 0, idx2 = 0;
    for (int i = 0; i < subs; i++) {
        std::cin >> submission.time;
        std::cin >> submission.team;
        std::cin >> submission.problem;
        std::cin >> submission.completed;

        //std::cout << " (" << submission.time << ", " << submission.team << ", " << submission.problem << ", " << submission.completed << ") ";

        if (key[0] == '0')  {
            key[idx] = submission.problem;
            idx++;
        }
        //std::cout << "key: " << key << "\n";

        char* result = std::strchr(key, submission.problem);

        if (result != nullptr) {
            idx2 = result - key;
            probs[idx2].push(submission);
        }
        else {
            key[idx] = submission.problem;
            probs[idx].push(submission);
            idx++;
        }
    }

    //print_stuff(probs);
    for (int i = 0; i < problems; i++) {
        if (!probs[i].empty()) {
            sub temp = probs[i].pop();
            while (!probs[i].empty() && temp.completed == "No") {
                sub temp = probs[i].pop();
            }            
            std::cout << temp.problem << " " << temp.time << " " << temp.team << "\n";
        }
        else {
            char temp = 'A' + i;
            std:: cout << temp << " - -\n";
        }
    }    
}