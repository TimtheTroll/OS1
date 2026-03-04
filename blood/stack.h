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