/* UVA 13055 "Inception" Solution by Timothy Cook (tcook548)
*/
// BELOW: Stack file included in its entirety for problem submission purposes.
#ifndef STACK_H
#define STACK_H

#include <vector>
template <typename T>
class Stack {
    std::vector<T> vals;
public:
    bool const empty() {return vals.size() == 0;}
    void push(T element) {vals.push_back(element);}
    void toss() {vals.pop_back();}
    T pop() {
        T element = vals.back();
        vals.pop_back();
        return element;
    }
    T top() {
        T element = pop();
        vals.push_back(element);
        return element;
    }

};

#endif
#include <iostream>
#include <string.h>
using namespace std;

int main() {
    int queries;
    string input;
    string name;
    Stack<string> dreams;

    cin >> queries;
    for (int i = 0; i < queries; i++) {
        cin >> input; // get input
        if (input == "Sleep") {
            cin >> name;
            // push the name of the person whose dream we are entering
            dreams.push(name);
        }
        if (input == "Test") {
            // if the stack is empty...
            if (dreams.empty()) {
                // we aren't in a dream
                cout << "Not in a dream\n";
            }
            else {
                // otherwise the top of the stack contains the name of the person dreaming
                cout << dreams.top() << "\n";
            }
        }
        if (input == "Kick") {
            // we can 'kick' by popping a name off of the stack
            if (!dreams.empty()) {
                dreams.pop();
            }
        }
    }
}